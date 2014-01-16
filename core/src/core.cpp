
#include <sstream>
#include <math.h>
#include "common/inc/hw_timer.hpp"
#include "jit/inc/jit.hpp"
#include "jit/inc/jit_support.hpp"
#include "core/inc/core.hpp"
#include "profiler/inc/common_profiler.hpp"
#include "core/inc/edma.hpp"

#include <Windows.h>

BEGIN_NS

//TMP
static DWORD bb_tick_total = 0;
static word_t bb_cycle_total = 0;
static word_t bb_inst_total = 0;

LARGE_INTEGER litmp;
LONGLONG QPart1,QPart2;
LONGLONG QPart1_BB,QPart2_BB;
double dfMinus, dfFreq, dfTim, dfAll;

static DWORD total_tick; // TMP
static word_t inst_cache_evit = 0;

Core::tlb_map_t Core::tlb_map;

Core *Core::instance = NULL;

Core::reg_file_t Core::reg;

//cycle_t Core::bb_start_cycle = 0;

//New Inst Cache
#ifdef CORE_CIRCULAR_N_WAY_CACHE
Instruction *Core::instCache[circular_inst_cache_size];
#else
Instruction *Core::instCache0[_1M/4];// L2 SRAM 1M
Instruction *Core::instCache1[inst_ext_mem_size/4];// EXT max 128M
#endif

std::list<Instruction*> Core::inst_heap_list;
Instruction Core::instHeap0[Core::inst_heap_size]; // default 4M inst size
uint Core::inst_heap_pos = 0;
uint Core::inst_heap_num = 1;//default instHeap0
Instruction *Core::inst_current_heap;

cycle_t Core::cycles = 0;
qword_t Core::total_cycle = 0;
qword_t Core::total_inst = 0;

Core::func_hook_t Core::func_hook;

typedef void (*unit_decode_func_t)(Core*,Instruction*);
static unit_decode_func_t unit_decode_tbl[9] = 
{
  NoneUnit::decode,
  LUnit::decode,
  SUnit::decode,
  MUnit::decode,
  DUnit::decode,
  LUnit::decode,
  SUnit::decode,
  MUnit::decode,
  DUnit::decode
};

Instruction *Core::alloc_inst(md_addr_t addr)
{
  if(inst_heap_pos >= inst_heap_size)
  {
    //alloc new heap
    inst_heap_list.push_back(inst_current_heap);
    inst_current_heap = new Instruction[inst_heap_size];
    inst_heap_pos = 0;
    ++inst_heap_num;
  }
  Instruction *inst = inst_current_heap + inst_heap_pos;
  ++inst_heap_pos;
  new (inst) Instruction(get_l2()->mem_read_word(addr),addr);
  unit_decode_func_t unit_de_func = unit_decode_tbl[inst->get_unit_type()];
  unit_de_func(Core::get(),inst);

#ifdef CORE_CIRCULAR_N_WAY_CACHE
  // nothing
#else
  const word_t idx = get_inst_cache_idx(addr);
  if(addr & 0x80000000)
  {
    instCache1[idx] = inst;
  }
  else
  {
    instCache0[idx] = inst;
  }
#endif
  return inst;
}

Core* Core::start()
{
  if(NULL == instance)
  {
    instance = new Core();
  }
  return instance;
}

Core* Core::get()
{
  //if(NULL == instance)
  //{
  //  instance = new Core();
  //}
  return instance;
}

void Core::init()
{
  // init L2 Mem ctroller here
  L2MemCtroller::init();

  HwTimer::init();

  // init register
  for(int i = 0; i < 64; ++i)
  {
    reg[i] = 0;
  }

  // clear old bps
  bp_list.clear();
  if(get_mode() == BK_AT_MAIN)
  {
    add_bp(get_main());
  }

  //init Timer
  timer[0].ctl = L2MemCtroller::get_phy_addr(0x01940000);
  timer[0].prd = L2MemCtroller::get_phy_addr(0x01940004);
  timer[0].cnt = L2MemCtroller::get_phy_addr(0x01940008);
  timer[0].next_clock_go = false;
  timer[0].event_id = 1;
  timer[0].real_count = 0;

  timer[1].ctl = L2MemCtroller::get_phy_addr(0x01980000);
  timer[1].prd = L2MemCtroller::get_phy_addr(0x01980004);
  timer[1].cnt = L2MemCtroller::get_phy_addr(0x01980008);
  timer[1].next_clock_go = false;
  timer[1].event_id = 2;
  timer[1].real_count = 0;

  timer[2].ctl = L2MemCtroller::get_phy_addr(0x01AC0000);
  timer[2].prd = L2MemCtroller::get_phy_addr(0x01AC0004);
  timer[2].cnt = L2MemCtroller::get_phy_addr(0x01AC0008);
  timer[2].next_clock_go = false;
  timer[2].event_id = 19;
  timer[2].real_count = 0;

  // init EDMA registers
  get_l2()->mem_write_word_xendian(0x01A0FFE0,0xF); // PQSR
  get_l2()->mem_write_word_xendian(0x01A0FFC0,0x2); // PQAR0
  get_l2()->mem_write_word_xendian(0x01A0FFC4,0x6); // PQAR0
  get_l2()->mem_write_word_xendian(0x01A0FFC8,0x2); // PQAR0
  get_l2()->mem_write_word_xendian(0x01A0FFCC,0x6); // PQAR0

  // init Instruction cache
  /*
  for(word_t i = 0; i < INST_CACHE_SIZE; ++i)
  {
    instCache[0][i].set_code_addr(0x1); // cache miss for the first time
    instCache[1][i].set_code_addr(0x1); // cache miss for the first time
  }
  */

  // init Instruction Cache 2
#ifdef CORE_CIRCULAR_N_WAY_CACHE
  memset(instCache,NULL,sizeof(instCache));
#else
  memset(instCache0,NULL,sizeof(instCache0));
  memset(instCache1,NULL,sizeof(instCache1));
#endif

  inst_heap_pos = 0;
  inst_current_heap = &instHeap0[0];

  //init MUXH/MUXL
  get_l2()->mem_write_word_xendian(0x19C0000,0x08202D43);
  get_l2()->mem_write_word_xendian(0x19C0004,0x250718A4);
  get_l2()->mem_write_word_xendian(0x19C0008,0x00000000);

  // init jmp_req_list
  for(word_t i = 0; i < 6; ++i)
  {
    jmp_req_list[i] = NO_JMP;
  }
  set_jmp_point(0);

  //TMP
  emif_A_commonInit();
  emif_A_128MbBoardInit();

  total_inst = 0;

  //TMP
  patch();

  Profiler::init();
#ifdef USE_LIBJIT
  JIT2::init(this);
#endif

#ifdef CORE_USE_LLVM
  JIT::init();
#endif

#ifdef _WIN32
  tick_count = GetTickCount();
  total_tick = tick_count;
  //QueryPerformanceCounter(&litmp);
  //QPart1 = litmp.QuadPart;
  HwTimer::start(0);
#endif
}

md_addr_t Core::fp_decoded = 0x1;
timer32_t Core::timer[3];

word_t Core::jmp_req_num = 0;
md_addr_t Core::jmp_req_list[6];
word_t Core::dummy_or_real_jmp_delay_cycles = 0;

reg_wb_t Core::reg_wb_list[8]; // max 8 in one cycle
word_t Core::reg_ch_num = 0;

stw_req_t Core::stw_req_list[2];
word_t Core::stw_req_num = 0;

Core::reg_wb_list_t Core::reg_delay_ch_tbl[5]; // max 5 cycle delay
word_t Core::rdc_num[5] = {0,0,0,0,0};
word_t Core::rdc_point = 0; // 0,1,2,3,4

#define ELE_NUM(ary) (sizeof(ary)/sizeof(0[ary]))

void Core::step()
{
  cycle();
}

//  20   19  18 16  15  14
//  PROT RS  DSZ    BR  SAT
// bits for expasion
void Core::pre_decode_16bit(word_t hi_tag,
                            word_t expansion,
                            bool is_next_p,
                            code_t code, // 16-bits code
                            md_addr_t code_addr)
{
#if 0
  const word_t code16bit_flag = GET_INST_FLAG(code_addr);
  Instruction *inst16bit = &instCache[hi_tag][code16bit_flag];
  new (inst16bit) Instruction(code,code_addr,is_next_p,true);

  //TODO pre-decode inst16bit
#endif
}

void Core::re_pre_decode_32bit(md_addr_t code_addr)
{
#ifdef CORE_CIRCULAR_N_WAY_CACHE
  Instruction *inst32bit = fetch_inst_n_way_cache_mode(code_addr);
#else
  Instruction *inst32bit = fetch_inst(code_addr);
  if(NULL == inst32bit)
  {
    inst32bit = alloc_inst(code_addr);
  }
  else
  {
    if(inst32bit->get_bb())
    {//remove basic block
      delete inst32bit->get_bb();
      inst32bit->set_bb(NULL);
    }
    new (inst32bit) Instruction(get_l2()->mem_read_word(code_addr),code_addr);
    unit_decode_func_t unit_de_func = unit_decode_tbl[inst32bit->get_unit_type()];
    unit_de_func(Core::get(),inst32bit);
  }
#endif

#ifdef CORE_USE_LLVM
  {
    if(inst32bit->get_jit_func())
    {
      llvm::Twine &func_name = "FUNC_" + llvm::Twine(code_addr);
      llvm::Function *func = JIT::module().getFunction(func_name.str());
      if(NULL != func)
      {
        func->eraseFromParent();
        get_ofs() << "Free " << func_name.str() << "\n";
        get_ofs().flush();
      }
      inst32bit->set_jit_func(NULL);
    }
  }
#endif

}

Instruction* Core::pre_decode_32bit(md_addr_t code_addr)
{
  Instruction *inst32bit;
#ifdef CORE_CIRCULAR_N_WAY_CACHE
  inst32bit = fetch_inst_n_way_cache_mode(code_addr);
#else
  inst32bit = alloc_inst(code_addr);
#endif
  return inst32bit;
}

inline void Core::decode_fp(md_addr_t fp_head_addr)
{
  if(fp_decoded == fp_head_addr)
  {
    return;
  }

  Instruction *inst = fetch_inst(fp_head_addr);
  code_t code = get_l2()->mem_read_word(fp_head_addr);
#ifdef CORE_USE_INST_CACHE
  if(NULL != inst && inst->get_code() == code)
  {// decoded
    return;
  }
#endif

  md_addr_t code_base = fp_head_addr - 0x1C; // first word in FP
  for(uint i = 0; i < 8; ++i)
  {
    const md_addr_t code32bit_addr = code_base + i * 4;
    pre_decode_32bit(code32bit_addr);
  }

  fp_decoded = fp_head_addr;
}

void Core::decode_c64xplus()
{
  pc_diff = 0;
  md_addr_t code_addr = get_pc_e1();
  md_addr_t fp_head_addr = (code_addr & 0xFFFFFFE0) + 0x1C;
  decode_fp(fp_head_addr);

  // code in code_addr already in instCache
  while(true)
  {
    if(code_addr == fp_head_addr + 0x4) // cross fp
    {
      decode_fp(fp_head_addr + 0x20); // decode next fp
    }

    Instruction *inst = fetch_cached_inst(code_addr);
    pc_diff += 4;
    code_addr += 4;

#ifndef CORE_ALL_SPEED
    // step debug support
    if( bp_list.end() != std::find(bp_list.begin(),bp_list.end(),inst->get_code_addr() ) )
    {
      // set debug mode
      set_debug(true);
      get_ofs() << "BP:" << inst->get_code_addr() << "\n";
      get_ofs().flush();
    }

    if(get_debug())
    {
      debug_proc();
    }
#endif

    //decode
    inst->get_de_func()(this,inst);
    inc_inst_num();

    if(!inst->is_next_p())
    {
      return;
    }
  }
}

inline void Core::reg_delay_change_proc()
{
  const reg_wb_list_t &reg_wb_list = reg_delay_ch_tbl[rdc_point];

  for(word_t i = 0; i < rdc_num[rdc_point]; ++i)
  {
    const reg_wb_t &req = reg_wb_list[i];

    //reg_write(req.side,req.reg,req.val);
    *req.reg_phy_addr = req.val;
  }

  rdc_num[rdc_point] = 0;
}

void Core::cexit_proc()
{
  HwTimer::end(0);
  inst_heap_list.push_back(inst_current_heap);

  DWORD diff = GetTickCount() - total_tick;
  DWORD all_running_cylc = get_cycle() + total_cycle;
  get_l2()->status();
  std::stringstream ss;
  ss << "\n*********************************************************\n"
     <<   "************  exit simulator  ***************************\n"
     <<   "*********************************************************\n";

  ss << "inst_cache_heap_num:" << inst_heap_num << "\n";
  ss << "inst_heap_size:" << to_hex_str(inst_heap_size) << "\n";
  ss << "inst_cache_total_size:" << to_hex_str(inst_heap_size*(inst_heap_num-1) + inst_heap_pos) << "\n";
  ss << "MIPS: " << ((double)total_inst/HwTimer::get_diff_us(0)) << "MHz\n";
  ss << "MCPS: " << ((double)all_running_cylc/HwTimer::get_diff_us(0)) << "MHz\n";
  //ss << "MIPS(use tick): " << ((double)total_inst/diff/1000) << "MHz\n";
  //ss << "MCPS(use tick): " << ((double)all_running_cylc/diff/1000) << "MHz\n";
  //ss << "BB MIPS: " << ((double)bb_cycle_total/1000/bb_tick_total) << "MHz\n";
#ifdef CORE_PROF_BB
  ss << "BB MIPS:" << to_hex_str(bb_inst_total) << ", " << 
    dfAll << "\n";
  ss << "BB MIPS:" << (double)bb_inst_total/dfAll/1000000 << "MHz\n";
#endif
  ss << "CYCLES:" << all_running_cylc << "\n";
  ss << "INST:" << total_inst << "\n";
  ss << "Ticks:" << diff << "\n";
  ss << "Elapsed:" << HwTimer::get_diff_seconds(0) << "s\n";
  ss << "JIT compile time:" << HwTimer::get_diff_seconds(1) << "s\n";
  ss << "JITed run time:" << HwTimer::get_diff_seconds(2) << "s\n";
  std::cout << ss.str();
  get_ofs() << ss.str();
  Profiler::dump_hot_bb_info();
  system("pause");
  exit(0);
}

//TODO vfd  virtual file driver
/*
#define  O_RDONLY    (0x0000) 
#define  O_WRONLY    (0x0001) 
#define  O_RDWR      (0x0002) 
#define  O_APPEND    (0x0008) 
#define  O_CREAT     (0x0200)
#define  O_TRUNC     (0x0400) 
#define  O_BINARY    (0x8000)

#define FLAG_TEST(flag,attr) ((flag & attr) != 0)

static const char *get_mode(word_t flag)
{
  const char* mode;

  if(FLAG_TEST(flag,O_TRUNC))
  {
    if(FLAG_TEST(flag,O_RDWR))
    {
      mode = FLAG_TEST(flag,O_BINARY) ? "w+b" : "w+";
    }
    else
    {
      mode = FLAG_TEST(flag,O_BINARY) ? "wb" : "w";
    }
  }
  else if(FLAG_TEST(flag,O_APPEND))
  {
    if(FLAG_TEST(flag,O_RDWR))
    {
      mode = FLAG_TEST(flag,O_BINARY) ? "a+b" : "a+";
    }
    else
    {
      mode = FLAG_TEST(flag,O_BINARY) ? "ab" : "a";
    }
  }
  else
  {
    if(FLAG_TEST(flag,O_RDWR))
    {
      mode = FLAG_TEST(flag,O_BINARY) ? "r+b" : "r+";
    }
    else
    {
      mode = FLAG_TEST(flag,O_BINARY) ? "rb" : "r";
    }
  }

  return mode;
}
*/

static HFILE get_file(Core *core,half_t dev_fd)
{
  HFILE file;
  if(dev_fd <= 2)
  {
    DWORD nStdHandle;
    switch(dev_fd)
    {
    case 0:
      nStdHandle = STD_INPUT_HANDLE;
      break;
      
    case 1:
      nStdHandle = STD_OUTPUT_HANDLE;
      break;

    case 2:
      nStdHandle = STD_ERROR_HANDLE;
      break;
    }
    //file = &__iob_func()[dev_fd];
    file = (HFILE)GetStdHandle(nStdHandle);
  }
  else
  {
    file = core->get_fentry()[dev_fd];
  }
  return file;
}


#include <fcntl.h>
// AA AA AA AA | BB CC1 CC2 CC3 | CC4 CC5 CC6 CC7 | CC8 DD ....
// AA-> length
// BB-> command
// CC->param
// DD->real data
// CC1 : dev_fd_lo, CC2 : dev_fd_hi
void Core::cio_proc()
{
  byte_t *buf = (byte_t*)cio.ciobuf;
  word_t length = get_l2()->mem_read_word((md_addr_t)buf);
  byte_t command = get_l2()->mem_read_byte((md_addr_t)(buf+4));
  byte_t *param = (buf + 5);
  half_t dev_fd,count;
  byte_t dev_fd_byte_lo, dev_fd_byte_hi;
  byte_t *data = buf + 13;
  count = length;
  word_t param1 = get_l2()->mem_read_word((md_addr_t)param);
  dev_fd_byte_lo = param1 >> 24;
  dev_fd_byte_hi = (param1 >> 16) & 0xFF;
  dev_fd = dev_fd_byte_lo | (dev_fd_byte_hi << 8);

  //FILE *file;
  HFILE file;

  switch(command)
  {
    case 0xF0: // open a file
      {
        int flags = BYTE_MASK(param1 >> 8);
        flags |= BYTE_MASK(param1) << 7;

        //translate the flags to win32 platf
        char name[256];
        memset(name,0,256);
        for(int i = 0; i < length; ++i)
        {
          char c = name[i] = get_l2()->mem_read_byte((md_addr_t)data++);
          if(c == 0)
          {
            break;
          }
        }
        //FILE *file = fopen(name,get_mode(flags));
        file = _lopen(name,flags);
        //assert(file);

        // xxx write back file handle
        get_l2()->mem_write_byte((md_addr_t)buf+4,BYTE_MASK(file >> 0));
        get_l2()->mem_write_byte((md_addr_t)buf+5,BYTE_MASK(file >> 8));
        get_l2()->mem_write_byte((md_addr_t)buf+6,BYTE_MASK(file >> 16));
        get_l2()->mem_write_byte((md_addr_t)buf+7,BYTE_MASK(file >> 24));

        //map it
        if(file != 0xFFFFFFFF)
        {
          get_fentry().insert(std::make_pair(dev_fd,file));
        }

        get_ofs() << "try to open file:" << name << "\n";
        get_ofs() << "open file:" << file <<",dev_fd:" << dev_fd << "\n";
        get_ofs().flush();
      }
      break;

    case 0xF1: // close
      {
        int ret = 0;
        if(dev_fd > 2)
        { //FIXME? do not close stdin,stdout,stderr
          file = get_file(this,dev_fd);
          ret = _lclose(file);
          //fflush(file); // flush before close?
          //ret = fclose(file);
          get_fentry().erase(dev_fd);
        }

        // write back param
        get_l2()->mem_write_byte((md_addr_t)buf+4,BYTE_MASK(ret));
        get_l2()->mem_write_byte((md_addr_t)buf+5,0);
      }
      break;

    case 0xF2: // read
      {
        byte_t *data_write = buf + 12;
        word_t count = BYTE_MASK(param1 >> 8) | (BYTE_MASK(param1) << 8);
        word_t fread_count = 0;
        file = get_file(this,dev_fd);

        char buf_read[256];
        memset(buf_read,0,256);
        fread_count = _lread(file,buf_read,count);

        if(fread_count > 256)
        {
          char buf[256];
          sprintf(buf,"failed to read file:%d,dev_fd:%d,read_cout:%u\n",
            file,dev_fd,fread_count);
          panic(buf);
        }
        
        for(int i = 0; i < fread_count; ++i)
        {
          get_l2()->mem_write_byte((md_addr_t)data_write++,buf_read[i]);
#ifndef CORE_ALL_SPEED
          get_ofs() << buf_read[i];
#endif
        }

#ifndef CORE_ALL_SPEED
        get_ofs() << "read " << fread_count << "\n";
        get_ofs() << "=== read end ===\n";
        get_ofs().flush();
#endif

        // write back length
        get_l2()->mem_write_byte((md_addr_t)buf,BYTE_MASK(fread_count >> 24));
        get_l2()->mem_write_byte((md_addr_t)buf+1,BYTE_MASK(fread_count >> 16));
        get_l2()->mem_write_byte((md_addr_t)buf+2,BYTE_MASK(fread_count >> 8));
        get_l2()->mem_write_byte((md_addr_t)buf+3,BYTE_MASK(fread_count >> 0));

        // write back param
        get_l2()->mem_write_byte((md_addr_t)buf+4,BYTE_MASK(fread_count));
        get_l2()->mem_write_byte((md_addr_t)buf+5,BYTE_MASK(fread_count >> 8));
      }
      break;

    case 0xF3: // write
      {
        file = get_file(this,dev_fd);
        static char buf[_1K]; //fixme? fixed CIO output buffer
        char *in = &buf[0];
        if(count > 0)
        {
          word_t print_cnt = count;
          for(int i = 0; i < count; ++i)
          {
            char c = get_l2()->mem_read_byte((md_addr_t)data);
            *in++ = c;
            if(c == '\0')
              break;
            data++;
          }
          _lwrite(file,buf,print_cnt);
          get_ofs() << buf; // NEED?
          if(count >= _1K)
          {
            panic("CIO output buffer overflow!(1024 bytes)");
          }
        }

      }
      break;

/*
lseek cmd:
  CC3 : offset_0
  CC4 : offset_1
  CC5 : offset_2
  CC6 : offset_3
  offset :  offset_3 offset_2 offset_1 offset_0

  CC7 : origin_lo
  CC8 : origin_hi
  origin : origin_hi origin_lo
*/
    case 0xF4:
      {
        file = get_file(this,dev_fd);
        word_t offset,origin;
        md_addr_t write_back_param = (md_addr_t)buf + 4;
        byte_t b;
        b = get_l2()->mem_read_byte((md_addr_t)param + 2);
        offset = b;
        b = get_l2()->mem_read_byte((md_addr_t)param + 3);
        offset |= b << 8;
        b = get_l2()->mem_read_byte((md_addr_t)param + 4);
        offset |= b << 16;
        b = get_l2()->mem_read_byte((md_addr_t)param + 5);
        offset |= b << 24;

        b = get_l2()->mem_read_byte((md_addr_t)param + 6);
        origin = b;
        b = get_l2()->mem_read_byte((md_addr_t)param + 7);
        origin |= b << 8;

        //int ret = fseek(file,offset,origin);
        int ret = _llseek(file,offset,origin);
        b = BYTE_MASK(ret);
        get_l2()->mem_write_byte(write_back_param,b);
        b = BYTE_MASK(ret >> 8);
        get_l2()->mem_write_byte(write_back_param+1,b);
        b = BYTE_MASK(ret >> 16);
        get_l2()->mem_write_byte(write_back_param+2,b);
        b = BYTE_MASK(ret >> 24);
        get_l2()->mem_write_byte(write_back_param+3,b);

      }
      break;

    default:
      break;
  }
}

void Core::icr_proc(void)
{
  word_t icr = this->read_ctrl_reg(CTL_ICR);
  word_t ifr = this->read_ctrl_reg(CTL_IFR);
  word_t ifr_old = ifr;

  word_t mask = 1 << 4;

  // xxx ICR process
  if(icr & 0xFFF0)
  {
    for(word_t i = 4; i <= 15; ++i)
    {
      if(icr & mask)
      {// clear the interrupt
        ifr &= ~mask;
      }
      mask <<= 1;
    }
  }

  write_ctrl_reg(CTL_ICR,0);// clear ICR
  set_icr_pending(false);

  if(ifr != ifr_old)
  {
    write_ctrl_reg(CTL_IFR,ifr);
  }

  word_t ier = read_ctrl_reg(CTL_IER);

  if(ifr & ier)
  {
    set_int_pending(true);
  }
}

void Core::int_proc(void)
{
  word_t ifr = this->read_ctrl_reg(CTL_IFR);
  word_t ier = this->read_ctrl_reg(CTL_IER);

  // xxx mask ifr
  ifr &= ier;
  word_t vector = rmbd(ifr,1);
  if(vector > 15)
  { // NO interrupt
    return;
  }

  if(vector == 0) // RESET vecotr0
  {
    for(word_t i = 0; i < 6; ++i)
    {
      jmp_req_list[i] = NO_JMP;
    }
    jmp_req_num  = 0;
    set_pc_e1(0x0); // goto .vector0
    return;
  }

  if(vector == 1)
  {
    //TODO NMI interrupt
    return;
  }
  
  bool vector_enabled = (ier & (1 << vector)) != 0;
  if(!vector_enabled)
  {
    return; // do not clear IFR
  }

  word_t csr = this->read_ctrl_reg(CTL_CSR);
  word_t gie = csr & 0x1;
  if(gie == 0)
  {//global interrupt disabled
    return;
  }

  word_t nmie = (ier & 0x2) >> 1;
  if(nmie == 0)
  {//NMI disabled
    return;
  }

  //there is no branch
  for(word_t i = 0; i < 6; ++i)
  {
    if(jmp_req_list[i] != NO_JMP)
    {
      return;
    }
  }

  //there is no register delay change
  for(word_t i =0; i < 5; ++i)
  {
    if(rdc_num[i] != 0)
    {
      return;
    }
  }

  //TODO
  //Processing of subsequent nonreset interrupts is disabled.

  //set PGIE, GIE
  csr &= 0xFFFFFFFC; // clear PGIE,GIE
  csr |= (gie << 1); // PGIE = GIE;
  this->write_ctrl_reg(CTL_CSR,csr);

  // set IRP
  this->write_ctrl_reg(CTL_IRP,this->get_pc_e1());

  // set ISTP
  word_t istp = this->read_ctrl_reg(CTL_ISTP);
  md_addr_t isrv_addr = istp + vector * 0x20;

  // end current bb
  Profiler::log_event(mk_evt(PROF_EVENT_BR_DELAY_CYCLES,VIRTUAL_INT_DELAY_CYCLES),
    get_pc_e1());

  // set interrupt pce1
  this->set_pc_e1(isrv_addr);

  //FIXME?  clear this IFR
  ifr &= ~(1 << vector);
  this->write_ctrl_reg(CTL_IFR,ifr);

  if(ifr & ier)
  {
    set_int_pending(true);
  }
  else
  {
    set_int_pending(false);
  }

  if(get_trace_flag() & tflag_isr)
  {
    get_ofs() << "Cycle " << get_cycle() << " Interrupt service : " << "<" << vector << ">\n";
    get_ofs().flush();
    get_profiler()->dump_call_stack();
  }
}

void Core::jmp_proc(void)
{
  md_addr_t jmp_addr = jmp_req_list[jmp_point];
  jmp_req_list[jmp_point] = NO_JMP;
  --jmp_req_num;

  // end current bb
  //Profiler::log_event(mk_evt(PROF_EVENT_BR_DELAY_CYCLES,1),get_pc_e1());

  // reset jmp delay factor
  // 5% performance down?
  /* 
  if(jmp_req_num == 0)
  {
    dummy_or_real_jmp_delay_cycles = 0;
  }
  */

  // skip jmp proc
  for(word_t i = 0; i < skip_jmp_list.size(); ++i)
  {
    if(skip_jmp_list[i] == jmp_addr)
    {
      set_pc_e1(reg_read(B_SIDE,3)); // ret to B3 after 5 cycles
      //set_nop_remains(5);
      //total_inst += 5;
      return;
    }
  }

  // func_hook proc
  if(jmp_addr == func_hook.memcpy_addr)
  {//A4:dst,B4:src,A6:cnt
    md_addr_t dst = reg_read(A_SIDE,4);
    md_addr_t src = reg_read(B_SIDE,4);
    md_addr_t cnt = reg_read(A_SIDE,6);
    phy_addr_t phy_dst = get_l2()->get_phy_addr(dst);
    phy_addr_t phy_src = get_l2()->get_phy_addr(src);
    memcpy(phy_dst,phy_src,cnt);
    code_modify_detect(dst,cnt >> 2);
    md_addr_t ret_addr = reg_read(B_SIDE,3);
    set_pc_e1(ret_addr);
    for(int i = 0; i < 5; ++i)
    {
      prolog_proc(); // NOP 5
    }

    //estimate 20 instructions each call
    total_inst += 20;
    return;
  }
#ifdef CORE_HOOK_DIVU
  if(jmp_addr == func_hook.divu_addr)
  {
    word_t a4 = reg_read(A_SIDE,4);
    word_t b4 = reg_read(B_SIDE,4);
    word_t result = b4 == 0 ? a4 : a4/b4;
    reg_write(A_SIDE,4,result);
    set_pc_e1(reg_read(B_SIDE,3));
    return;
  }
#endif

  set_pc_e1(jmp_addr);

  // patch EUL
  if(jmp_addr == get_main())
  {
    patch_eul_entry_main();
  }

  if(get_profiler() && TRACE_ENABLED(tflag_call_stack))
  {// 10% CPU load
    get_profiler()->exec_jmp(this,jmp_addr);
  }

  if(get_pc_e1() == cexit_hook_addr)
  {
    cexit_proc();
  }
}

void Core::patch()
{
  sym_tbl_t::iterator it = sym_tbl.begin();
  for(; it != sym_tbl.end(); ++it)
  {
    if(it->second.compare("_calcMemCRC16") == 0)
    {
      std::cout << "skip function calcMemCRC16 \n"; 
      skip_jmp_list.push_back(it->first);
    }
    
    if(it->second.compare("_printTTBMode") == 0)
    {
      std::cout << "skip function printTTBMode \n"; 
      skip_jmp_list.push_back(it->first);
    }
    if(it->second.compare("_odo_panic") == 0)
    {
      std::cout << "break point _odo_panic \n"; 
      bp_list.push_back(it->first);
    }
    if(it->second.compare("_memcpy") == 0)
    {
      std::cout << "find memcpy\n";
      func_hook.memcpy_addr = it->first;
    }
    if(it->second.compare("__divu") == 0)
    {
      std::cout << "find __divu\n";
      func_hook.divu_addr = it->first;
    }
  }
}

void Core::add_bp(md_addr_t bp)
{
  bp_list.push_back(bp);
}

void Core::add_mem_trace_range(md_addr_t start, md_addr_t len)
{
  //get_mem_trace_list().push_back(MemRange(start,len));
}

void Core::add_cycle_bp(qword_t cycle_bp)
{
  bp_cycle_list.push_back(cycle_bp);
}

void Core::add_skip_jmp(md_addr_t addr)
{
  skip_jmp_list.push_back(addr);
}

void Core::rmv_bp(md_addr_t bp)
{
  std::vector<md_addr_t>::iterator it = bp_list.begin();
  for(; bp_list.end() != it; ++it)
  {
    if(*it == bp)
    {
      bp_list.erase(it);
      return;
    }
  }
}

void Core::rmv_bp_by_index(word_t idx)
{
  if(idx >= bp_list.size())
  {
    return;
  }
  std::vector<md_addr_t>::iterator it = bp_list.begin();
  word_t count = 0;
  for(; it != bp_list.end(); ++it)
  {
    if(count == idx)
    {
      bp_list.erase(it);
      return;
    }
    count++;
  }
}

void Core::l2_cache_proc()
{
// 0x01844004 L2 writeback word count register
    reset_address(0x01844004);

//0x0184 4014  L2 writeback invalidate word count register
    reset_address(0x01844014);

//0x0184 401C  L2 invalidate word count register
    reset_address(0x0184401C);

//0x0184 4024  L1P invalidate word count register
    reset_address(0x01844024);

//0x0184 4034  L1D writeback invalidate word count register
    reset_address(0x01844034);

// 0x0184404C L1DIWC L1D invalidate word count register
    reset_address(0x0184404C);

//0x01845004 L2 writeback invalidate all register
    reset_address(0x01845004);

//0x01840000 CCFG Cache configuration register
    reset_address(0x01840000);
}

#define QOPT  0x02000000
#define QSRC  0x02000004
#define QCNT  0x02000008
#define QDST  0x0200000C
#define QIDX  0x02000010

#define QSOPT  0x02000020
#define QSSRC  0x02000024
#define QSCNT  0x02000028
#define QSDST  0x0200002C
#define QSIDX  0x02000030


static word_t esize_tbl[4] = 
{
  4,
  2,
  1,
  4 // reserved
};

void Core::code_modify_detect(md_addr_t start_addr,word_t word_len)
{
  MemRange *mr;
  Core::mem_prot_list_t::iterator it = this->get_mem_prot_list().begin();
  for(; it != this->get_mem_prot_list().end();++it)
  {
    mr = *it;
    if(mr->include(start_addr))
    {
      //TODO invalidate jit compile request if addr EQ
      this->get_ofs() << "CODE MODIFY by QDMA:" << to_hex_str(start_addr) <<
        ",Len:" << to_hex_str(word_len * 4) << "\n";
      this->get_ofs().flush();
      for(int i = 0; i < word_len; ++i)
      {
        re_pre_decode_32bit(start_addr + i * 4);
      }
      break;
    }
  }
}

// 1. only detect QSOPT(0x20000020) to active a qdma TR
// 2. copy QSOPT to QOPT; zero QSOPT
// 3. start transfer
void Core::qdma_proc()
{
  word_t qsopt = get_l2()->mem_read_word(QSOPT);
  if(0 == qsopt)
  {
    return;
  }

  // copy QSOPT to QOPT
  get_l2()->mem_write_word_xendian(QOPT,qsopt);

  // clear QSOPT
  get_l2()->mem_write_word(QSOPT,0);

  word_t qdma_src = get_l2()->mem_read_word(QSRC);
  word_t qdma_dst = get_l2()->mem_read_word(QDST);
  word_t qdma_cnt = get_l2()->mem_read_word(QCNT);

  word_t ESIZE = get_uint(qsopt,27,2);

  phy_addr_t phy_src = get_l2()->get_phy_addr(qdma_src);
  phy_addr_t phy_dst = get_l2()->get_phy_addr(qdma_dst);
  word_t FRMCNT = qdma_cnt >> 16;
  word_t ELECNT = qdma_cnt & 0xFFFF; // U32 count

  word_t byte_size = esize_tbl[ESIZE] * ELECNT;

#ifndef CORE_ALL_SPEED
  get_ofs() << "QDMA, src:" << to_hex_str(qdma_src) <<
    ",dst:" << to_hex_str(qdma_dst) << ",FRMCNT:" << FRMCNT <<
    ",ELECNT:" << ELECNT << "\n";
  get_ofs().flush();
#endif

  // do not use QIDX...
  memcpy(phy_dst,phy_src, byte_size);
  code_modify_detect(qdma_dst,byte_size >> 2);

#define CIERL 0x01A0FFE8
#define CIPRL 0x01A0FFE4

  // TCC process
  if(get_uint(qsopt,20,1))
  {
    word_t tcc = get_uint(qsopt,16,4);
    word_t tccm = get_uint(qsopt,13,2);
    tcc |= tccm << 4;
    word_t ciprl = 1 << tcc;
    word_t old_ciprl = get_l2()->mem_read_word(CIPRL);
    word_t cierl = get_l2()->mem_read_word(CIERL);
    // xxx write CIPRL
    get_l2()->mem_load_word_xendian(CIPRL,ciprl | old_ciprl);
    if(ciprl & cierl) // OK generate EDMA_INT event
    { // EDMA_INT to cpu
      signal_evt(8);  
    }
  }
}

#define GET_EVT(evt) (evt & 0x1F)  // 5 bits
static word_t evt_shift_table[16] = 
{
  0,0,0,0,0,5,10,16,21,26,0,5,10,16,21,26
};

word_t Core::get_evt_for_vector(word_t vector)
{
  if(vector < 4 || vector > 15)
  {
    return 0x20; // invalid evt id
  }

  word_t mux,r_shift;
  if(vector <= 9) // MUXL
  {
    mux = get_l2()->mem_read_word(0x19C0004);
  }
  else  // MUXH
  {
    mux = get_l2()->mem_read_word(0x19C0000);
  }

  r_shift = evt_shift_table[vector];
  return GET_EVT(mux >> r_shift);
}

void Core::timer_proc()
{
  Core *core = Core::get();
  //timer0_cycle(core);
  for(int i = 0; i < 3; ++i)
  {
    timer32_t *timer = &Core::timer[i];
    //xxx direct use little edian to check ctl
    word_t ctl_le = *timer->ctl;
    word_t cnt_le,cnt_be,prd_le;
    if((ctl_le & 0x80000000) != 0)
    { // Counter is disabled and held in the current state.
      if(timer->next_clock_go)
      {// reset and start to count
        timer->real_count = 0;
        *timer->cnt = 0;
        timer->next_clock_go = false;
      }

      if(ctl_le & 0x40000000)
      {//If HLD = 1, the counter register is zeroed and begins counting on the next clock.
        timer->next_clock_go = true;

        //clr go
        ctl_le &= ~0x40000000;
        *timer->ctl = ctl_le;
      }
      else
      {
        cnt_le = *timer->cnt;
        prd_le = *timer->prd;
        if(cnt_le == prd_le) // reach period
        {
          *timer->cnt = 0;

          // signal event
          int int_vector = 4;
          word_t evt;
          for(; int_vector < 16; ++int_vector)
          {// get_event_map
            evt = core->get_evt_for_vector(int_vector);
            if(evt == timer->event_id)
            {
              break;
            }
          }

          if(int_vector < 16) // timer 1 -> INT 15
          {
            word_t ifr = core->read_ctrl_reg(CTL_IFR);
            ifr |= (1 << int_vector);
            core->write_ctrl_reg(CTL_IFR,ifr);
            word_t ier = core->read_ctrl_reg(CTL_IER);

            if(ifr & ier)
            {
              core->set_int_pending(true);
            }

            if(core->get_trace_flag() & tflag_isr)
            {
              core->get_ofs() << "CYCLE:" << core->get_cycle()
                << ",CTL:" << to_hex_str(MD_SWAPW(*timer->ctl))
                << ",CNT:" << to_hex_str(MD_SWAPW(*timer->cnt))
                << ",PRD:" << to_hex_str(MD_SWAPW(*timer->prd))
                << ",REAL:" << to_hex_str(timer->real_count) 
                << ",VECTOR:" << int_vector
                << "\n";
            }
          }
        }
        else
        {
          cnt_be = MD_SWAPW(cnt_le);
          cnt_be++;
          *timer->cnt = MD_SWAPW(cnt_be);
        }
      }
    }
  }
}

/*
void Core::timer0_cycle(Core* core)
{
  timer32_t* t = &Core::timer[0];
  if((t->reg[TIMER_CTL] & 0x80000000) == 0)
  { // Counter is disabled and held in the current state.
    return;
  }

  if(t->next_clock_go)
  {// reset and start to count
    t->reg[TIMER_CNT] = 0;
    t->next_clock_go = false;
  }

  if(t->reg[TIMER_CTL] & 0x40000000)
  {//If HLD = 1, the counter register is zeroed and begins counting on the next clock.
    timer->next_clock_go = true;

    //clr go
    t->reg[TIMER_CTL] &= ~0x40000000;
    return;
  }

  if(t->reg[TIMER_CNT] == t->reg[TIMER_PRD]) // reach period
  {
    t->reg[TIMER_CNT] = 0;

    // signal event
    int int_vector = 4;
    word_t evt;
    for(; int_vector < 16; ++int_vector)
    {// get_event_map
      evt = core->get_evt_for_vector(int_vector);
      if(evt == timer->event_id)
      {
        break;
      }
    }

    if(int_vector < 16) // timer 1 -> INT 15
    {
      word_t ifr = core->read_ctrl_reg(CTL_IFR);
      ifr |= (1 << int_vector);
      core->write_ctrl_reg(CTL_IFR,ifr);
      word_t ier = core->read_ctrl_reg(CTL_IER);

      if(ifr & ier)
      {
        core->set_int_pending(true);
      }

      if(core->get_trace_flag() & tflag_isr)
      {
        core->get_ofs() << "CYCLE:" << core->get_cycle()
          << ",CTL:" << to_hex_str(MD_SWAPW(*timer->ctl))
          << ",CNT:" << to_hex_str(MD_SWAPW(*timer->cnt))
          << ",PRD:" << to_hex_str(MD_SWAPW(*timer->prd))
          << ",REAL:" << to_hex_str(timer->real_count) 
          << ",VECTOR:" << int_vector
          << "\n";
      }
    }
  }
  else
  {
    word_t cnt_be = MD_SWAPW(t->reg[TIMER_CNT]);
    ++cnt_be;
    t->reg[TIMER_CNT] = MD_SWAPW(cnt_be);
  }
}
*/

void Core::timer0_cycle(Core* core)
{
  timer32_t* t = &Core::timer[0];
  if((t->reg[TIMER_CTL] & 0x80) == 0)
  { // Counter is disabled and held in the current state.
    return;
  }

  if(t->next_clock_go)
  {// reset and start to count
    t->reg[TIMER_CNT] = 0;
    t->next_clock_go = false;
  }

  if(t->reg[TIMER_CTL] & 0x40)
  {//If HLD = 1, the counter register is zeroed and begins counting on the next clock.
    timer->next_clock_go = true;

    //clr go
    t->reg[TIMER_CTL] &= ~0x40;
    return;
  }

  if(t->reg[TIMER_CNT] == t->reg[TIMER_PRD]) // reach period
  {
    t->reg[TIMER_CNT] = 0;

    // signal event
    int int_vector = 4;
    word_t evt;
    for(; int_vector < 16; ++int_vector)
    {// get_event_map
      evt = core->get_evt_for_vector(int_vector);
      if(evt == timer->event_id)
      {
        break;
      }
    }

    if(int_vector < 16) // timer 1 -> INT 15
    {
      word_t ifr = core->read_ctrl_reg(CTL_IFR);
      ifr |= (1 << int_vector);
      core->write_ctrl_reg(CTL_IFR,ifr);
      word_t ier = core->read_ctrl_reg(CTL_IER);

      if(ifr & ier)
      {
        core->set_int_pending(true);
      }

      if(core->get_trace_flag() & tflag_isr)
      {
        core->get_ofs() << "CYCLE:" << core->get_cycle()
          << ",CTL:" << to_hex_str(MD_SWAPW(*timer->ctl))
          << ",CNT:" << to_hex_str(MD_SWAPW(*timer->cnt))
          << ",PRD:" << to_hex_str(MD_SWAPW(*timer->prd))
          << ",REAL:" << to_hex_str(timer->real_count) 
          << ",VECTOR:" << int_vector
          << "\n";
      }
    }
  }
  else
  {
    t->reg[TIMER_CNT]++;
  }
}

void Core::timer_cycle(Core *core, timer32_t* timer)
{
  //xxx direct use little edian to check ctl
  word_t ctl_le = *timer->ctl;
  word_t cnt_le,cnt_be,prd_le;
  if((ctl_le & 0x80000000) == 0)
  { // Counter is disabled and held in the current state.
    return;
  }

  if(timer->next_clock_go)
  {// reset and start to count
    timer->real_count = 0;
    *timer->cnt = 0;
    timer->next_clock_go = false;
  }

  if(ctl_le & 0x40000000)
  {//If HLD = 1, the counter register is zeroed and begins counting on the next clock.
    timer->next_clock_go = true;

    //clr go
    ctl_le &= ~0x40000000;
    *timer->ctl = ctl_le;
    return;
  }

  cnt_le = *timer->cnt;
  prd_le = *timer->prd;
  if(cnt_le == prd_le) // reach period
  {
    *timer->cnt = 0;

    // signal event
    int int_vector = 4;
    word_t evt;
    for(; int_vector < 16; ++int_vector)
    {// get_event_map
      evt = core->get_evt_for_vector(int_vector);
      if(evt == timer->event_id)
      {
        break;
      }
    }

    if(int_vector < 16) // timer 1 -> INT 15
    {
      word_t ifr = core->read_ctrl_reg(CTL_IFR);
      ifr |= (1 << int_vector);
      core->write_ctrl_reg(CTL_IFR,ifr);
      word_t ier = core->read_ctrl_reg(CTL_IER);

      if(ifr & ier)
      {
        core->set_int_pending(true);
      }

      if(core->get_trace_flag() & tflag_isr)
      {
        core->get_ofs() << "CYCLE:" << core->get_cycle()
          << ",CTL:" << to_hex_str(MD_SWAPW(*timer->ctl))
          << ",CNT:" << to_hex_str(MD_SWAPW(*timer->cnt))
          << ",PRD:" << to_hex_str(MD_SWAPW(*timer->prd))
          << ",REAL:" << to_hex_str(timer->real_count) 
          << ",VECTOR:" << int_vector
          << "\n";
      }
    }
  }
  else
  {
    cnt_be = MD_SWAPW(cnt_le);
    cnt_be++;
    *timer->cnt = MD_SWAPW(cnt_be);
  }
}

extern "C" {
  void bb_prolog_proc()
  {
    Core *core = Core::get();
    core->inc_rdc_point();
    if(core->rdc_num[core->rdc_point] != 0)
    {
      core->reg_delay_change_proc();
    }

    core->inc_cycle();
  #ifndef CORE_ISS_ONLY
    // every 8 cycles
    if((core->get_cycle() & 0x7) == 0)
    {
      Core::timer_proc();

      // every 256 cycles
      if((core->get_cycle() & 0xFF) == 0)
      { 
        core->cycle_mod_256_proc();
      }
    }

    if(core->get_icr_pending())
    {
      core->icr_proc();
    }
  #endif
  }

  void bb_prolog_proc_multi_cycles(word_t nops)
  {
    Core *core = Core::get();
    for(int i = 0; i < nops;++i)
    {
      core->inc_rdc_point();
      if(core->rdc_num[core->rdc_point] != 0)
      {
        core->reg_delay_change_proc();
      }

      core->inc_cycle();
    #ifndef CORE_ISS_ONLY
      // every 8 cycles
      if((core->get_cycle() & 0x7) == 0)
      {
        Core::timer_proc();

        // every 256 cycles
        if((core->get_cycle() & 0xFF) == 0)
        { 
          core->cycle_mod_256_proc();
        }
      }
    #endif
    }

    if(core->get_icr_pending())
    {
      core->icr_proc();
    }
  }

  void bb_stw_proc()
  {
    Core::stw_proc();
  }

  void bb_prolog_and_epilog_proc()
  {
    Core *core = Core::get();
    if(core->reg_ch_num != 0)
    {
      core->reg_ch_proc();
    }
    if(core->stw_req_num != 0)
    {
      core->stw_proc();
    }
    core->inc_rdc_point();
    if(core->rdc_num[core->rdc_point] != 0)
    {
      core->reg_delay_change_proc();
    }

    core->inc_cycle();
  #ifndef CORE_ISS_ONLY
    // every 8 cycles
    if((core->get_cycle() & 0x7) == 0)
    {
      Core::timer_proc();

      // every 256 cycles
      if((core->get_cycle() & 0xFF) == 0)
      { 
        core->cycle_mod_256_proc();
      }
    }

    if(core->get_icr_pending())
    {
      core->icr_proc();
    }
  #endif
  }
}

void Core::prolog_proc()
{
  inc_cycle();
  if(dummy_or_real_jmp_delay_cycles > 0)
  {
    --dummy_or_real_jmp_delay_cycles;
  }

  inc_rdc_point();
  if(rdc_num[rdc_point] != 0)
  {
    reg_delay_change_proc();
  }
  
  if(jmp_req_num != 0)
  {
    inc_jmp_point();
    if(NO_JMP != jmp_req_list[get_jmp_point()])
    {
      jmp_proc();
    }
  }

#ifndef CORE_ISS_ONLY
  if(get_pc_e1() == cio.cio_hook_addr)
  {
    cio_proc();
  }

  // every 8 cycles
  if((get_cycle() & 0x7) == 0)
  {
    /*
    timer_cycle(this,&timer[0]);
    timer_cycle(this,&timer[1]);
    timer_cycle(this,&timer[2]);
    */
    timer_proc();

    // every 256 cycles
    if((get_cycle() & 0xFF) == 0)
    { 
      cycle_mod_256_proc();
    }
  }

  if(get_icr_pending())
  {
    icr_proc();
  }
  if(get_int_pending())
  {
    int_proc();
  }
#endif
}

void Core::cycle_mod_256_proc()
{
  l2_cache_proc();
  qdma_proc();
  EDMA::cc_proc(this);
}

void Core::cycle()
{
BEGIN_CYCLE:
  prolog_proc();
  
  Instruction* inst = fetch_inst(get_pc_e1());
  if(NULL != inst && NULL != inst->get_jit_func())
  {
    if(jmp_req_num > 0)
    {
      Core::get()->get_ofs() << "BB " << to_hex_str(get_pc_e1()) <<
        "skipped by jmp request\n";
      goto INTERPRE_CYCLE;
    }
    //HwTimer::start(2);
    inst->get_bb()->call_times++;
    inst->jit_func();
    //HwTimer::end(2);
    goto BEGIN_CYCLE;
  }

INTERPRE_CYCLE:
  pc_diff = 4;
  md_addr_t addr = get_pc_e1();
  while(true)
  {
    if(inst == NULL)
    {
      inst = pre_decode_32bit(addr);
    }
#ifndef CORE_USE_INST_CACHE
    else
    {//do not use cached inst
      new (inst) Instruction(get_l2()->mem_read_word(addr),addr);
      unit_decode_func_t unit_de_func = unit_decode_tbl[inst->get_unit_type()];
      unit_de_func(Core::get(),inst);
    }
#endif
    inst->get_de_func()(this,inst);
    inc_inst_num();
    if(!inst->is_next_p())
    {
      break;
    }
    addr += 4;
    pc_diff += 4;
    inst = fetch_inst(addr);
  }

  epilog_proc();

  //Test
  Profiler::log_event(mk_evt(PROF_EVENT_BR_DELAY_CYCLES,dummy_or_real_jmp_delay_cycles),
    get_pc_e1());

  pce1 += pc_diff;

  while (get_nop_remains() > 0)
  {
    nop_remains--;
    inc_inst_num();
    prolog_proc();
  }

  goto BEGIN_CYCLE;
}

void Core::profile(cycle_t cycle)
{
  if(( cycle & 0xFFFFFF) == 0)
  {
    DWORD current_tick = GetTickCount();
    static md_addr_t last_pc = 0;
    DWORD diff = current_tick - tick_count;
    DWORD diff_inst = total_cycle - current_tick;
    tick_count = current_tick;
    //get_ofs() << "Use " << diff << " Ticks to run 16777215 cycles\n";
    get_ofs() << "MCPS: " << ((double)0xFFFFFF/1000/diff) << "MHz | " <<
      "ID:" << get_cycle()/0xFFFFFF << "\n";
    
    //get_ofs() << "PC: " << to_hex_str(get_pc_e1()) << "\n";
    get_ofs().flush();

    if(last_pc == get_pc_e1())
    {
#ifndef CORE_ALL_SPEED
      set_debug(true);
#endif
    }
    last_pc = get_pc_e1();

    if(get_mode() == FIRST_16777215_CYCLES_PROFILE)
    {
      std::cout << "Use " << diff << " Ticks to run 16777215 cycles\n";
      std::cout << "MIPS: " << ((double)0xFFFFFF/1000/diff) << "MHz\n";
      get_l2()->status();
      system("pause");
      exit(0);
    }
  }
}

void Core::init_c64ctrl_regs(void)
{
  memset(ctrl_regs,0,sizeof(ctrl_regs));

  //init csr
  csr_data_t csr_val;
  csr_val.u32_value = 0;
  csr_val.csr_value.CPUID = 0xC;
  csr_val.csr_value.REVISION_ID = 0x2;
  csr_val.csr_value.EN = 0; // FIXME ; endian

  write_ctrl_reg(CTL_CSR,(word_t)csr_val.u32_value);

  /*
  CtrlRegister *pReg;
#define NEW_CTRL_REG(name,crlo,type) \
  pReg = new CtrlRegister(name,crlo,0x0,CtrlRegister::access_enum_t::##type);\
  ctrl_regs.insert(std::make_pair(name,pReg));

  //AMR
  NEW_CTRL_REG("AMR",0x0,R_W);

  //CSR
  NEW_CTRL_REG("CSR",0x1,R_W_P);

  //init csr
  csr_data_t csr_val;
  csr_val.u32_value = 0;
  csr_val.csr_value.CPUID = 0xC;
  csr_val.csr_value.REVISION_ID = 0x2;
  csr_val.csr_value.EN = 0; // FIXME ; endian
  write_ctrl_reg_no_check("CSR",(word_t)csr_val.u32_value);

  //DEIR
  NEW_CTRL_REG("DEIR",0x19,R_W);

  //DNUM
  NEW_CTRL_REG("DNUM",0x11,R);

  //ECR //EFR  // FIXME seperate?
  NEW_CTRL_REG("ECR/EFR",0x1D,R_W);

  //GFPGFR
  NEW_CTRL_REG("GFPGFR",0x18,R_W);

  //GPLYA
  NEW_CTRL_REG("GPLYA",0x16,R_W);

  //GPLYB
  NEW_CTRL_REG("GPLYB",0x17,R_W);

  //ICR
  NEW_CTRL_REG("ICR",0x03,W);

  //IER
  NEW_CTRL_REG("IER",0x04,R_W);

  // xxx init IER
  write_ctrl_reg_no_check("IER",(word_t)0x1);

  //IERR
  NEW_CTRL_REG("IERR",0x1F,R_W);

  //IFR
  NEW_CTRL_REG("IFR",0x02,R);

  //ILC
  NEW_CTRL_REG("ILC",0x0D,R_W);

  //IRP
  NEW_CTRL_REG("IRP",0x06,R_W);

  //ISR FIXME isr shadow ifr?
  NEW_CTRL_REG("ISR",0x02,W);

  //ISTP
  NEW_CTRL_REG("ISTP",0x05,R_W);

  //ITSR
  NEW_CTRL_REG("ITSR",0x1B,R_W);

  //NRP
  NEW_CTRL_REG("NRP",0x07,R_W);

  //NTSR
  NEW_CTRL_REG("NTSR",0x1C,R_W);

  //PCE1
  NEW_CTRL_REG("PCE1",0x10,R);

  //REP
  NEW_CTRL_REG("REP",0x0F,R_W);

  //RILC
  NEW_CTRL_REG("RILC",0x0E,R_W);

  //SSR
  NEW_CTRL_REG("SSR",0x15,R_W);

  //TSCH
  NEW_CTRL_REG("TSCH",0x0B,R);

  //TSCL
  NEW_CTRL_REG("TSCL",0x0A,R);

  //TSR
  NEW_CTRL_REG("TSR",0x1A,R_W_P);
  */
}

void Core::init_ctrl_regs(core_type_t core_type)
{
  switch(core_type)
  {
  case C64:
    init_c64ctrl_regs();
    break;

  default: // TODO support other types
    assert(false);
    break;
  }
  return;
}

/*
word_t Core::read_ctrl_reg(const char *name)
{
  //CtrlRegister* pReg = ctrl_regs[name];
  //assert(NULL != pReg);
  //assert(pReg->read_ok());
  //return (pReg->get_val());
}
*/

/*
void Core::write_ctrl_reg(const char *name,word_t value)
{
  CtrlRegister* pReg = ctrl_regs[name];
  assert(NULL != pReg);
  assert(pReg->write_ok());

  //special process for IER:nmie
  if(strcmp(name,"IER"))
  {
    word_t nmie = (pReg->get_val() >> 1) & 0x1;
    if(nmie)
    {
      value |= 0x2; // if set, never clear
    }
    pReg->set_val(value);
  }
  else
  {
    pReg->set_val(value);
  }
}
*/

word_t Core::read_ctrl_reg(word_t crlo)
{
  if(crlo > 0x1F)
  {
    return 0;
  }
  return ctrl_regs[crlo];
}

void Core::write_ctrl_reg(word_t crlo,word_t value)
{
  if(crlo > 0x1F)
  {
    return;
  }
  word_t old_val = ctrl_regs[crlo];
  word_t new_val = value;

  if(crlo == CTL_IER)
  {
    word_t nmie = (old_val >> 1) & 0x1;
    if(nmie)
    {
      new_val |= 0x2; // if set, never clear
    }
  }
  if(crlo == CTL_IFR && (new_val != 0))
  {
    word_t ier = read_ctrl_reg(CTL_IER);
    new_val = old_val | new_val;
    if(new_val * ier)
    {
      set_int_pending(true);
    }
  }
  if(crlo == CTL_ICR && (new_val != 0))
  {
    set_icr_pending(true);
  }
  ctrl_regs[crlo] = new_val;

  //debug mode
  if(get_debug())
  {
    std::cout << "CTL reg " << to_hex_str(crlo) << ":";
    std::cout << to_hex_str(old_val) << " -> ";
    std::cout << to_hex_str(new_val) << "\n";
  }

  if(get_trace_flag() & tflag_ctl_reg)
  {
    get_ofs() << "CYCLE[" << get_cycle() << "]:\n";
    get_ofs() << "CTL reg " << to_hex_str(crlo) << ":";
    get_ofs() << to_hex_str(old_val) << " -> ";
    get_ofs() << to_hex_str(new_val) << "\n";
    get_ofs().flush();
  }
}

void Core::mem_dump(md_addr_t start, int len)
{
  for(int i = 0; i < len; ++i)
  {
    get_ofs() << to_hex_str(start) << ":" << to_hex_str(get_l2()->mem_read_word(start)) << "\n";
    start += 4;
  }
  get_ofs().flush();
}

void Core::debug_proc()
{
  dbg_cont_t ret = DBG_HOLD;
  if(get_profiler())
  {
    get_profiler()->dump_call_stack();
  }
  for (int i=0;i<32;++i)
  {
    std::cout << "A" << i << ":" << to_hex_str(reg[i]) << " ";
    if ((i+1)% 5 == 0)
    {
      std::cout << "\n";
    }
  }
  std::cout << "\n";
  for (int i=0;i<32;++i)
  {
    std::cout << "B" << i << ":" << to_hex_str(reg[32+i]) << " ";
    if ((i+1)% 5 == 0)
    {
      std::cout << "\n";
    }
  }
  std::cout << "\n";
  while(ret == DBG_HOLD)
  {
    std::stringstream prompt;
    prompt << "[Cycle " << get_cycle() << "] ";
    prompt << to_hex_str(get_pc_e1()) << " >";
    std::string line = readline(prompt.str().c_str());
    std::vector<std::string> tokens;

    // split it
    std::istringstream iss(line);
    std::copy(std::istream_iterator<std::string>(iss),
      std::istream_iterator<std::string>(),
      std::back_inserter<std::vector<std::string>>(tokens));

    if(!tokens.empty())
    {
      std::string& cmd_str = tokens[0];
      DbgBaseCmd *cmd = DbgDummy::get_instance();
      help_map_t::iterator it = helper.begin();
      for(; helper.end() != it; ++it)
      {
        if(it->first.compare(cmd_str) == 0)
        {
          cmd = helper[cmd_str];
        }
      }

      ret = (*cmd)(this,tokens);
    }
  }
  
  //reset proflie timer
  tick_count = GetTickCount();
}

void Core::emif_A_commonInit()
{
#define _EMIFA_BASE_GLOBAL   0x01800000u
#define _EMIFA_GBLCTL_OFFSET          0
#define _EMIFA_CECTL0_OFFSET          2*4
#define _EMIFA_CECTL1_OFFSET          1*4
#define _EMIFA_CECTL2_OFFSET          4*4
#define _EMIFA_CECTL3_OFFSET          5*4
#define _EMIFA_SDCTL_OFFSET           6*4
#define _EMIFA_SDTIM_OFFSET           7*4
#define _EMIFA_SDEXT_OFFSET           8*4
#define _EMIFA_CESEC0_OFFSET          18*4
#define _EMIFA_CESEC1_OFFSET          17*4
#define _EMIFA_CESEC2_OFFSET          20*4
#define _EMIFA_CESEC3_OFFSET          21*4

  md_addr_t base_a = (md_addr_t)_EMIFA_BASE_GLOBAL;

  get_l2()->mem_write_word_xendian(base_a + _EMIFA_GBLCTL_OFFSET,0x000120a0);//gblctl
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_CECTL0_OFFSET,0xffffff33);//cectl0;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_CECTL1_OFFSET,0xffffff03);//cectl1;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_CECTL2_OFFSET,0xffffff03);//cectl2;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_CECTL3_OFFSET,0xffffff03);//cectl3;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_SDTIM_OFFSET, 0x000003aa);//sdtim;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_SDEXT_OFFSET, 0x0005452b);//sdext;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_CESEC0_OFFSET,0x00000002);//cesec0;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_CESEC1_OFFSET,0x00000002);//cesec1;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_CESEC2_OFFSET,0x00000002);//cesec2;
  get_l2()->mem_write_word_xendian(base_a + _EMIFA_CESEC3_OFFSET,0x00000002);//cesec3;
}

void Core::emif_A_128MbBoardInit()
{
#define _EMIFA_BASE_GLOBAL   0x01800000u
#define _EMIFA_SDCTL_OFFSET           6*4

  md_addr_t base_a = (md_addr_t)_EMIFA_BASE_GLOBAL;

  get_l2()->mem_write_word_xendian(base_a + _EMIFA_SDCTL_OFFSET, 0x6B227000);//sdctl;
}

void Core::panic(const char* msg)
{
  std::cout << msg << "\n";
  get_ofs() << msg << "\n";
  get_ofs() << "CYCLE:" << get_cycle() << "\n";
  get_ofs() << "PC" << to_hex_str(get_pc_e1()) << "\n";
  get_profiler()->dump_call_stack();
  get_ofs().flush();
  abort();
}

Core::Core():entry_point(NULL),
  pce1(NULL),nop_remains(0),ofs("out"),
  int_pending(false),debug(false),trace_flag(0)
{
  //l2_mem_ctrl = NULL;

  init_reg();

  //profiler
  prof = new ExePathProfiler(&ofs,false);

  // register debug helper FO
  helper.insert(std::make_pair("h",new DbgHelp));
  helper.insert(std::make_pair("help",new DbgHelp));
  helper.insert(std::make_pair("r",new DbgShowGenRegs));
  helper.insert(std::make_pair("c",new DbgShowContext));

  helper.insert(std::make_pair("s",new DbgStep));
  helper.insert(std::make_pair("step",new DbgStep));

  helper.insert(std::make_pair("g",new DbgGo));
  helper.insert(std::make_pair("go",new DbgGo));

  helper.insert(std::make_pair("sb",new DbgSetBreakPoint));
  helper.insert(std::make_pair("rb",new DbgRemoveBreakPoint));
  helper.insert(std::make_pair("lb",new DbgListBreakPoint));
  helper.insert(std::make_pair("scb",new DbgSetCycleBreak));
  helper.insert(std::make_pair("ssj",new DbgSetSkipJmp));

  helper.insert(std::make_pair("dw",new DbgDumpWord));
  helper.insert(std::make_pair("ds",new DbgDumpString));
  helper.insert(std::make_pair("sw",new DbgSetWord));

  helper.insert(std::make_pair("smt",new DbgSetMemTrace));

  helper.insert(std::make_pair("ls",new DbgListSymbol));

  helper.insert(std::make_pair("st",new DbgSetTraceFlag));
  helper.insert(std::make_pair("swc",new DbgSetWriteCheck));

  // Debug info
  mode = BK_AT_MAIN;
}

void Core::patch_eul_entry_main()
{
  sym_tbl_t::iterator it = sym_tbl.begin();
  for(; it != sym_tbl.end(); ++it)
  {
    if(it->second.compare("_TTB_CONF_Mode") == 0)
    {
      std::cout << "TTB_CONF_Mode:\n";
      word_t val = get_l2()->mem_read_word(it->first);
      std::cout << to_hex_str(val) << " -> 10\n";
      get_l2()->mem_write_word_xendian(it->first,10);
    }
    if(it->second.compare("_TTB_CONF_transparantMode") == 0)
    {
      std::cout << "TTB_CONF_transparantMode:\n";
      word_t val = get_l2()->mem_read_word(it->first);
      std::cout << to_hex_str(val) << " -> 1\n";
      get_l2()->mem_write_word_xendian(it->first,1);
    }
    
    if(it->second.compare("_overrideTestSuiteWithFile") == 0)
    {
      std::cout << "overrideTestSuiteWithFile:\n";
      word_t val = get_l2()->mem_read_word(it->first);
      std::cout << to_hex_str(val) << " -> 1\n";
      get_l2()->mem_write_word_xendian(it->first,1);
    }
  }
}

void Core::signal_evt(word_t evt)
{
  word_t int_vector = 4;
  word_t evt_find;
  for(; int_vector < 16; ++int_vector)
  {// get_event_map
    evt_find = get_evt_for_vector(int_vector);
    if(evt == evt_find)
    {
      break;
    }
  }

  if(int_vector < 16) // timer 1 -> INT 15
  {
    word_t ifr = read_ctrl_reg(CTL_IFR);
    word_t ier = read_ctrl_reg(CTL_IER);
    if(TRACE_ENABLED(tflag_ctl_reg))
    {
      get_ofs() << "IFR before evt:" << to_hex_str(ifr) << "\n";
    }
    ifr |= (1 << int_vector);
    if(TRACE_ENABLED(tflag_ctl_reg))
    {
      get_ofs() << "IFR after evt:" << to_hex_str(ifr) << "\n";
    }
    write_ctrl_reg(CTL_IFR,ifr);
    if(ier & ifr)
    {
      set_int_pending(true);
    }
  }
}

inline void Core::reset_address(md_addr_t addr)
{
  get_l2()->mem_write_word(addr,0);
}

inline void Core::add_pc_e1(word_t diff_in_u32)
{
  pce1 += diff_in_u32 << 2;
}

void Core::run()
{
  cycle();
}

inline ExePathProfiler *Core::get_profiler()
{
  return prof;
}

inline void Core::init_reg()
{
  memset(reg,0,sizeof(reg));
  init_ctrl_regs(core_type_t::C64); // TODO
}

inline void Core::inc_jmp_point()
{
  ++jmp_point;
  if(jmp_point >= 6)
  {
    jmp_point = 0;
  }
}

void Core::push_reg_delay_ch(const word_t side,
  const word_t idx,
  const word_t val,
  const word_t delay_cycles)
{
  word_t insert_point = get_rdc_insert_point(delay_cycles);
  reg_wb_t &reg_ch = reg_delay_ch_tbl[insert_point][rdc_num[insert_point]++];
  reg_ch.val = val;
  reg_ch.reg_phy_addr = get_reg_addr(side,idx);
}

void Core::push_reg_delay_ch_1c_delay(const word_t side,
  const word_t idx,
  const word_t val)
{
  word_t insert_point = get_rdc_insert_point(1);
  reg_wb_t &reg_ch = reg_delay_ch_tbl[insert_point][rdc_num[insert_point]++];
  reg_ch.val = val;
  reg_ch.reg_phy_addr = get_reg_addr(side,idx);
}

#ifdef CORE_CIRCULAR_N_WAY_CACHE
Instruction *Core::fetch_inst_n_way_cache_mode(md_addr_t addr)
{
  const word_t idx = get_inst_cache_idx(addr);
  Instruction *cur_inst = instCache[idx];
  if(NULL == cur_inst)
  {// new cache line
    cur_inst = alloc_inst(addr);
    instCache[idx] = cur_inst;
    cur_inst->set_next(cur_inst);
    return cur_inst;
  }
  else
  {
    // find addr in cache line
    if(cur_inst->get_code_addr() == addr)
    {// cache hit
      return cur_inst;
    }
    Instruction *head_inst = cur_inst;
    //bool cache_hit = false;
    while(cur_inst->next != head_inst)
    {
      cur_inst = cur_inst->next;
      if(cur_inst->get_code_addr() == addr)
      {
        instCache[idx] = cur_inst;
        return cur_inst;
      }
    }

    // cache miss; alloc new one
    Instruction *new_inst = alloc_inst(addr);
    cur_inst->next = new_inst;
    new_inst->next = head_inst;
    instCache[idx] = new_inst; // move new_inst head of this cache line
    return new_inst;
  }
}
#endif

END_NS