#ifndef CORE_CORE_HPP
#define CORE_CORE_HPP

#include <fstream>
#include <map>
#include <string>
#include <queue>
#include <list>

#include "common/inc/def.hpp"
#include "core/inc/l2_mem_ctrl.hpp"
#include "core/inc/unit.hpp"
#include "core/inc/n_unit.hpp"
#include "core/inc/l_unit.hpp"
#include "core/inc/s_unit.hpp"
#include "core/inc/m_unit.hpp"
#include "core/inc/d_unit.hpp"
#include "core/inc/dbg.hpp"
#include "decode/inc/fp.hpp"
#include "decode/inc/inst.hpp"
#include "core/inc/ctrl_register.hpp"

#include "profiler/inc/exe_path_profiler.hpp"

#include "p3/readline/include/readline/readline.h"

#ifdef _WIN32
#include <Windows.h>
#endif

BEGIN_NS

class DbgBaseCmd;
class DbgDummy;
class DbgHelp;
class DbgShowGenRegs;
class DbgShowContext;
class EDMA;

enum core_mode_t
{
  BK_AT_MAIN = 0,
  DIRECT_RUN,
  FIRST_16777215_CYCLES_PROFILE,
  UNIT_VERIF
};

// A,B register file
typedef enum reg_side_t
{
  A_SIDE = 0,
  B_SIDE = 1
}reg_side_t;

struct reg_change_req_t
{
  word_t side;
  word_t reg;
  word_t val;
};

struct reg_wb_t
{
  word_t *reg_phy_addr;
  word_t val;
};

struct reg_delay_change_req_t
{
  word_t side;
  word_t reg;
  word_t val;
  word_t delay_cycles;
};

struct jmp_req_t
{
  md_addr_t addr;
  word_t delay_cycles;
  bool dummy; // TODO remove?

  jmp_req_t():dummy(false){}
};

struct stw_req_t
{
  md_addr_t addr;
  mem_type_t type;
  word_t val;
  qword_t qval; //TODO use union
};

#define TIMER_CTL 0
#define TIMER_PRD 1
#define TIMER_CNT 2
struct timer32_t
{
  //word_t ctl_val;
  //word_t prd_val;
  //word_t cnt_val;
  phy_addr_t ctl;
  phy_addr_t prd;
  phy_addr_t cnt;
  bool next_clock_go;
  word_t event_id;
  word_t real_count; // no need to use qword_t
  word_t reg[3];
};

extern "C" {
  void bb_prolog_proc(); // prolog_proc for Basic Block
  void bb_prolog_and_epilog_proc(); // prolog_proc for Basic Block
  void bb_stw_proc();
  void bb_prolog_proc_multi_cycles(word_t nops);
}

class FP;
class L2MemCtroller;
class MemRange;

#define INST_CACHE_SIZE 0x200000  // cache 4M code
#ifdef C64X_PLUS
  #define INST_CACHE_MASK ((INST_CACHE_SIZE - 1) << 1)
  #define GET_INST_FLAG(code) ((code & INST_CACHE_MASK) >> 1)
#else
  #define INST_CACHE_MASK ((INST_CACHE_SIZE - 1) << 2)
  #define GET_INST_FLAG(code) ((code & INST_CACHE_MASK) >> 2)
#endif

#define GET_INST_HIGH_TAG(code) (code >> 31)

#ifdef CORE_ALL_SPEED
  typedef word_t cycle_t; // %5~10% SPEED gain use word_t
#else
  typedef qword_t cycle_t;
#endif

class Core
{
public:
  // typedefs/const/friend class:
  typedef std::map<md_addr_t, std::string> sym_tbl_t;
  typedef std::vector<MemRange*> mem_prot_list_t;
  typedef std::map<half_t,HFILE> f_entry_t;
  typedef word_t reg_file_t[64]; // A: 0~31 B: 32~63
  typedef reg_wb_t reg_wb_list_t[8];
  typedef std::map<std::string,DbgBaseCmd*> help_map_t;
  typedef std::map<md_addr_t,jit_func_t> tlb_map_t;
  typedef enum
  {
    C64 = 0,
    C64_PLUS,
    C66
  }core_type_t;
  typedef enum
  {
    CTL_AMR = 0x0,
    CTL_CSR = 0x1,
    CTL_IFR = 0x02,
    CTL_ICR = 0x03,
    CTL_IER = 0x04,
    CTL_ISTP = 0x05,
    CTL_IRP = 0x06,
    CTL_NRP = 0x07,
    CTL_TSCL = 0x0A,
    CTL_TSCH = 0x0B,
    CTL_ILC  = 0x0D,
    CTL_RILC = 0x0E,
    CTL_REP = 0x0F,
    CTL_PCE1 = 0x10,
    CTL_DNUM = 0x11,
    CTL_SSR = 0x15,
    CTL_GPLYA = 0x16,
    CTL_GPLYB = 0x17,
    CTL_GFPGFR = 0x18,
    CTL_DIER = 0x19,
    CTL_TSR = 0x1A,
    CTL_ITSR = 0x1B,
    CTL_NTSR = 0x1C,
    CTL_ECR = 0x1D, // ECR/EFR
    CTL_IERR = 0x1F,
  }ctrl_reg_t;
  typedef struct
  {
    md_addr_t cio_hook_addr;
    md_addr_t ciobuf;
  }cio_t;
  typedef struct
  {
    md_addr_t memcpy_addr;
    md_addr_t divu_addr;
  }func_hook_t;

  friend class DbgHelp;
  friend class DbgShowGenRegs;
  friend class DbgShowContext;
  friend class DbgStep;
  friend class DbgGo;
  friend class DbgSetBreakPoint;
  friend class DbgListBreakPoint;
  friend class DbgRemoveBreakPoint;
  friend class DbgSetCycleBreak;

  static const word_t NO_JMP = 1;

  // bit - 0 | 0x1: trace ctl register change
  // bit - 1 | 0x2: trace execute path
  // bit - 2 | 0x4: trace ISR
  // bit - 3 | 0x8: trace Instruction Cache evict
  // bit - 4 | 0x10 : trace call stack each jmp_proc
  static const word_t tflag_ctl_reg = 0x1;
  static const word_t tflag_exec_path = 0x2;
  static const word_t tflag_isr = 0x4;
  static const word_t tflag_inst_cache_evict = 0x8;
  static const word_t tflag_call_stack = 0x10;

#define TRACE_ENABLED(flag) ((get_trace_flag() & flag) != 0)

private:
  //cycls
  //entry point | normally -> _c_int00
  md_addr_t entry_point;

  //ctrl registers
  word_t ctrl_regs[32];

  //break point list
  std::vector<md_addr_t> bp_list;

  //cycle break point list
  std::vector<qword_t> bp_cycle_list;

  //jmp skip addr list
  std::vector<md_addr_t> skip_jmp_list;

  //trace usage
  std::ofstream ofs;

  //performance counter for simulator itself
  DWORD tick_count;

  //profiler
  ExePathProfiler *prof;

  //CEXIT
  md_addr_t cexit_hook_addr;

  // single instance
  static Core* instance;

  static md_addr_t fp_decoded;

// ATTRs
private:
  //CIO
  ATTR_RW(f_entry_t,fentry)

  //used to update PC for c64x TODO:remove this one
  ATTR_RW(word_t,inst_num) 

  //used to update PC for c64x+
  ATTR_RW(word_t,pc_diff)

  // fast interrupt process
  ATTR_RW(bool,int_pending)
  ATTR_RW(bool,icr_pending)

  // current jmp position
  ATTR_RW(word_t,jmp_point)

  // NOPs remain to run
  ATTR_RW(word_t,nop_remains)

  ATTR_RW(md_addr_t,main)

  // symbol table
  ATTR_RW(sym_tbl_t,sym_tbl)

  ATTR_RW(mem_prot_list_t, mem_prot_list)

  // verif/debug 
  ATTR_RW(bool,debug)
  ATTR_RW(core_mode_t,mode)
  ATTR_RW(word_t,trace_flag)

private:
  Core();
  ~Core();

  void pre_decode_16bit(word_t hi_tag,
                        word_t expasion,
                        bool is_next_p,
                        code_t code,
                        md_addr_t code_addr);
  void decode_fp(md_addr_t fp_head_addr);
  void decode_c64xplus();

  // hard-code gel support TODO:support gel script
  void emif_A_commonInit();
  void emif_A_128MbBoardInit();
  
  help_map_t helper;
  void debug_proc();
  void reset_address(md_addr_t addr);
  void add_pc_e1(word_t diff_in_u32);
  void patch();
  void patch_eul_entry_main();

  void cycle();
  void profile(cycle_t cycle);
  void prolog_proc();
  inline static void epilog_proc();
  void jmp_proc();
  void int_proc(); // interrupt logic
  void l2_cache_proc();
  void qdma_proc();
  void cio_proc();
  void cexit_proc();

  ExePathProfiler *get_profiler();
  void init_reg();
  word_t get_evt_for_vector(word_t vector);
  void init_ctrl_regs(core_type_t core_type);
  void init_c64ctrl_regs(void);

  void inc_jmp_point();

public:
  // singleton
  static Core* get();
  static Core* start();

  void code_modify_detect(md_addr_t start_addr,word_t word_len);
  Instruction* pre_decode_32bit(md_addr_t code_addr);
  void re_pre_decode_32bit(md_addr_t code_addr);

  inline static word_t* get_reg_a();
  inline static word_t* get_reg_b();
  inline static word_t* get_reg_addr(word_t side,word_t idx);
  inline static word_t* get_reg_addr_abs_idx(word_t idx);

  inline cycle_t get_cycle();

  inline void set_pc_e1(md_addr_t addr);

  inline static void stw_proc();

  void cycle_mod_256_proc();

  void icr_proc();
  inline static void reg_ch_proc();
  inline static word_t get_rdc_insert_point(word_t delay);
  static void reg_delay_change_proc();
  inline static void inc_rdc_point();
  inline static void bb_epilog_proc();
  inline static void inc_cycle();
  inline static void inc_inst_num();
  inline static void timer0_write(md_addr_t addr,word_t val);
  inline static word_t timer0_read(md_addr_t addr);
  static void timer0_cycle(Core *core);
  static void timer_cycle(Core *core, timer32_t* timer);
  static void timer_proc();
  void signal_evt(word_t evt);

  inline std::ofstream& get_ofs();

  // read register pair
  inline qword_t reg_read_long(code_t side, code_t reg_even);

  // read 32-bit register
  inline static word_t reg_read(word_t side, word_t idx);

  // read 32-bit register by absolute index 0~63
  inline static word_t reg_read_abs_idx(word_t idx);

  // write 32-bit register
  inline static void reg_write(word_t side, word_t idx, word_t val);

  inline md_addr_t get_pc_e1();

  inline void set_entry_point(md_addr_t ep);

  // get L2 Memory Controller
  inline static L2MemCtroller *get_l2();

  // add break point
  void add_bp(md_addr_t bp);

  void add_mem_trace_range(md_addr_t start, md_addr_t len);

  void add_cycle_bp(qword_t cycle_bp);

  void add_skip_jmp(md_addr_t addr);

  void rmv_bp(md_addr_t bp);

  void rmv_bp_by_index(word_t idx);

  void step();

  void init();

  void run();

  void mem_dump(md_addr_t start, int len);

  void panic(const char*);

  inline void set_cio_hook(md_addr_t addr);

  inline void set_ciobuf(md_addr_t addr);

  static void push_reg_delay_ch(const word_t side,
    const word_t idx,
    const word_t val,
    const word_t delay_cycles);

  static void  push_reg_delay_ch_1c_delay(const word_t side,
    const word_t idx,
    const word_t val);

  inline static void push_reg_delay_ch_4c_delay(const word_t side,
    const word_t idx,
    const word_t val);

  static inline void push_reg_ch(const word_t side,
    const word_t idx,
    const word_t val);

  static inline void push_reg_ch_abs_idx(const word_t idx,const word_t val);

  inline void set_cexit_hook(md_addr_t addr);

  inline void add_jmp_req(md_addr_t jmp_addr);
  static inline void push_stw_req(const stw_req_t& req);

  word_t read_ctrl_reg(const char *name);
  void write_ctrl_reg(const char *name,word_t value);

  word_t read_ctrl_reg(word_t crlo);
  void write_ctrl_reg(word_t crlo,word_t value);

  // direct fetch cached instruction in instCache
  static Instruction *fetch_cached_inst(md_addr_t code_addr);

public:
  // register files | A,B side | make static
  static reg_file_t reg;
  static cycle_t cycles;
  static qword_t total_cycle;
  static qword_t total_inst;

  // register change related
  static reg_wb_t reg_wb_list[8]; // max 8 in one cycle
  static word_t reg_ch_num;

  // register delay change related
  static reg_wb_list_t reg_delay_ch_tbl[5]; // max 5 cycle delay
  static word_t rdc_num[5];
  static word_t rdc_point; // 0,1,2,3,4

  // jump related
  static word_t jmp_req_num;
  static md_addr_t jmp_req_list[6];
  static word_t dummy_or_real_jmp_delay_cycles;//left delay cycles for a dummy/real jmp

  // store related
  static stw_req_t stw_req_list[2]; // max 2?
  static word_t stw_req_num;

  //Translated lookup BasicBlock
  static tlb_map_t tlb_map;
  //PC counter in current E1 stage
  md_addr_t pce1;

  static std::list<Instruction*> inst_heap_list;

  //CIO
  cio_t cio;
  static func_hook_t func_hook;

  inline static Instruction *fetch_inst(md_addr_t addr);
#ifdef CORE_CIRCULAR_N_WAY_CACHE
  static Instruction *fetch_inst_n_way_cache_mode(md_addr_t addr);
#endif
  inline static word_t get_inst_cache_idx(md_addr_t addr);
  static Instruction *alloc_inst(md_addr_t addr);

  static const uint inst_heap_size = 96 * _1K;
  static const uint inst_ext_mem_size = _128M;
  static uint inst_heap_num;
  static Instruction instHeap0[inst_heap_size];
  static uint inst_heap_pos;
  static Instruction *inst_current_heap;

  static const uint circular_inst_cache_bit_size = 20; // 4M
  static const uint circular_inst_cache_size = 1 << circular_inst_cache_bit_size;
  static const uint circular_inst_cache_mask = circular_inst_cache_size - 1;

#ifdef CORE_CIRCULAR_N_WAY_CACHE
  static Instruction* instCache[circular_inst_cache_size]; 
#else
  static Instruction *instCache0[_1M/4];// L2 SRAM 1M
  static Instruction *instCache1[inst_ext_mem_size/4];// EXT max 128M
#endif

  //32bit timers
  static timer32_t timer[3];
};

//public inline functions
L2MemCtroller *Core::get_l2() 
{
  return L2MemCtroller::get();
}

cycle_t Core::get_cycle()
{
  return cycles;
}

void Core::reg_write(word_t side, word_t idx, word_t val)
{
  reg[(side << 5) + idx] = val;
}

void Core::set_pc_e1(md_addr_t addr)
{
  pce1 = addr;
}

std::ofstream& Core::get_ofs()
{
  return ofs;
}

qword_t Core::reg_read_long(code_t side, code_t reg_even)
{
  word_t hi,lo;
  qword_t re;
  lo = this->reg_read(side,reg_even);
  hi = this->reg_read(side,reg_even + 1);
  re = ((qword_t)hi << 32) | lo;
  return re;
}

md_addr_t Core::get_pc_e1()
{
  return pce1;
}

void Core::set_entry_point(md_addr_t ep)
{
  entry_point = ep;
  pce1 = ep; //TODO
}

word_t Core::reg_read(word_t side, word_t idx)
{
  return reg[(side << 5) + idx];
}

word_t Core::reg_read_abs_idx(word_t idx)
{
  return reg[idx];
}

void Core::set_cio_hook(md_addr_t addr)
{
  cio.cio_hook_addr = addr;
}

void Core::set_ciobuf(md_addr_t addr)
{
  cio.ciobuf = addr;
}

void Core::push_reg_delay_ch_4c_delay(const word_t side,
  const word_t idx,
  const word_t val)
{
  reg_wb_t &reg_ch = reg_delay_ch_tbl[rdc_point][rdc_num[rdc_point]++];
  reg_ch.val = val;
  reg_ch.reg_phy_addr = get_reg_addr(side,idx);
}

void Core::push_reg_ch(const word_t side,
  const word_t idx,
  const word_t val)
{
  reg_wb_t &reg_ch = reg_wb_list[reg_ch_num++];
  reg_ch.val = val;
  reg_ch.reg_phy_addr = get_reg_addr(side,idx);
}

void Core::push_reg_ch_abs_idx(const word_t idx,const word_t val)
{
  reg_wb_t &reg_ch = reg_wb_list[reg_ch_num++];
  reg_ch.val = val;
  reg_ch.reg_phy_addr = get_reg_addr_abs_idx(idx);
}

void Core::set_cexit_hook(md_addr_t addr)
{
  cexit_hook_addr = addr;
}

void Core::push_stw_req(const stw_req_t& req)
{
  stw_req_list[stw_req_num++] = req;
}

word_t* Core::get_reg_a()
{
  return static_cast<word_t*>(&reg[0]);
}

word_t* Core::get_reg_b()
{
  return static_cast<word_t*>(&reg[(1 << 5) + 0]);
}

word_t* Core::get_reg_addr(word_t side,word_t idx)
{
  return static_cast<word_t*>(&reg[(side << 5) + idx]);
}

word_t* Core::get_reg_addr_abs_idx(word_t idx)
{
  return static_cast<word_t*>(&reg[idx]);
}

inline Instruction *Core::fetch_cached_inst(md_addr_t code_addr)
{
  return fetch_inst(code_addr);
}

void Core::reg_ch_proc()
{
  while(reg_ch_num > 0)
  {
    reg_wb_t& req = reg_wb_list[--reg_ch_num];
    *req.reg_phy_addr = req.val;
  }
}

void Core::stw_proc()
{
  while(stw_req_num > 0)
  {
    stw_req_t& req = stw_req_list[--stw_req_num];
    switch (req.type)
    {
    case TYPE_U32:
      get_l2()->mem_write_word_xendian(req.addr,req.val);
      break;
    
    case TYPE_U16:
      get_l2()->mem_write_half_xendian(req.addr,req.val);
      break;
    
    case TYPE_U8:
      get_l2()->mem_write_byte(req.addr,req.val);
      break;

    case TYPE_U64:
      get_l2()->mem_write_qword_xendian(req.addr,req.qval);
      break;

    default:
      break;
    }
  }
}

void Core::epilog_proc()
{
  if(reg_ch_num != 0)
  {
    reg_ch_proc();
  }
  if(stw_req_num != 0)
  {
    stw_proc();
  }
}

void Core::bb_epilog_proc()
{
  if(reg_ch_num != 0)
  {
    reg_ch_proc();
  }
  if(stw_req_num != 0)
  {
    stw_proc();
  }
}

word_t Core::get_rdc_insert_point(word_t delay)
{
  word_t point = rdc_point + delay + 1;
  if(point >= 5)
  {
    point -= 5;
  }
  return point;
}

void Core::inc_rdc_point()
{
  ++rdc_point;
  if(rdc_point >= 5)
  {
    rdc_point = 0;
  }
}

/*
void Core::bb_prolog_proc()
{
  inc_rdc_point();
  if(rdc_num[rdc_point] != 0)
  {
    reg_delay_change_proc();
  }

  inc_cycle();
#ifndef CORE_ISS_ONLY
  // every 8 cycles
  if((get_cycle() & 0x7) == 0)
  {
    timer_cycle(this,&timer[0]);
    timer_cycle(this,&timer[1]);
    timer_cycle(this,&timer[2]);

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
#endif
}
*/

void Core::inc_cycle()
{
  ++cycles;
}

void Core::inc_inst_num()
{
  ++total_inst;
}

void Core::add_jmp_req(md_addr_t jmp_addr)
{
  jmp_req_list[jmp_point] = jmp_addr;
  ++jmp_req_num;
}

word_t Core::timer0_read(md_addr_t addr)
{
  word_t idx = (addr - 0x1940000) >> 2;
  return Core::timer[0].reg[idx];
}

void Core::timer0_write(md_addr_t addr,word_t val)
{
  word_t idx = (addr - 0x1940000) >> 2;
  if(idx > 2)
  {
    Core::get()->panic("TIMER0 ERROR");
  }
  Core::timer[0].reg[idx] = val;
}

Instruction *Core::fetch_inst(md_addr_t addr)
{
#ifdef CORE_CIRCULAR_N_WAY_CACHE
  return fetch_inst_n_way_cache_mode(addr);
#else
  const word_t idx = get_inst_cache_idx(addr);
  Instruction *inst = ((addr & 0x80000000) != 0) ?
    instCache1[idx] : instCache0[idx];
  return inst;
#endif

}

word_t Core::get_inst_cache_idx(md_addr_t addr)
{
#ifdef CORE_CIRCULAR_N_WAY_CACHE
  return (addr & circular_inst_cache_mask) >> 2;
#else
  return (addr & 0xFFFFFFF) >> 2;
#endif
}

END_NS

#endif