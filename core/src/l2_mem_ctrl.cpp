#include "core/inc/l2_mem_ctrl.hpp"
#include "core/inc/core.hpp"

BEGIN_NS

// 256K page table
byte_t *L2MemCtroller::ptable[ptbl_size]; 

// reserved page
byte_t *L2MemCtroller::reserved;

L2MemCtroller *L2MemCtroller::instance = NULL;

#define EMIFA_REGS 0x1800000
#define L2_REGS    0x1840000
#define HPI_REGS   0x1880000
#define MC_BSP0_REGS 0x18C0000
#define MC_BSP1_REGS 0x1900000
#define TIMER0_REGS  0x1940000
#define TIMER1_REGS  0x1980000
#define INT_SELECT_REGS 0x19C0000
#define EDMA_REGS       0x1A00000
#define MC_BSP2_REGS    0x1A40000
#define EMIFB_REGS      0x1A80000
#define TIMER2_REGS     0x1AC0000
#define GPIO_REGS       0x1B00000
#define UTOPIA_REGS     0x1B40000
#define TCP_VCP_REGS    0x1B80000
#define PCI_REGS        0x1C00000
#define QDMA_REGS       0x2000000

#define EMIFA_CE0       0x80000000  // 256M
#define EMIFA_CE1       0x90000000

#ifdef _WIN32
#define PAGE_ALLOC(size) (byte_t*)VirtualAlloc(NULL,size,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE)
#else
#define PAGE_ALLOC(size) (byte_t*)calloc(1,size)
#endif

#define DEFINE_PAGE(addr) ptable[page_tag(addr)] = PAGE_ALLOC(page_size)

#define DEF_CB_PAGE(addr,cb) ptable[page_tag(addr)] = (byte_t*)((word_t)cb + 1)

static word_t timer0_cb(byte_t type,md_addr_t addr,word_t val)
{
  if(type == 0)
  {
    Core::timer0_write(addr,MD_SWAPW(val));
    return val;
  }
  else
  {
    return MD_SWAPW(Core::timer0_read(addr));
  }
}

#define CIPRL_ADDR 0x01A0FFE4
static const word_t ciprl_relative_addr = (CIPRL_ADDR - EDMA_REGS) >> 2;
static word_t edma_page[L2MemCtroller::page_size >> 2];

// FIXME? ERROR?
static word_t edma_reg_cb(byte_t type,md_addr_t addr,word_t val)
{
  if(type == 0)
  {// write
    if(addr == 0x01A0FFE4) // CIPRL
    { // write to CIPRL == clear the bit
      word_t ciprl = MD_SWAPW(edma_page[ciprl_relative_addr]);//mem_read_word(addr)
      ciprl &= ~val;
      edma_page[ciprl_relative_addr] = MD_SWAPW(ciprl);
      return 0;
    }
    edma_page[(addr - EDMA_REGS) >> 2] = val;
    return 0;
  }
  else if (type == 1)
  {// read
    return edma_page[(addr - EDMA_REGS) >> 2];
  }
  else
  {//direct write
    edma_page[(addr - EDMA_REGS) >> 2] = val;
  }
}

/*
void L2MemCtroller::mem_write_ciprl(word_t val)
{
  word_t old_ciprl = mem_read_word(CIPRL_ADDR);
  old_ciprl &= ~val;
  mem_load_word_xendian(CIPRL_ADDR,old_ciprl);
}
*/

L2MemCtroller::L2MemCtroller()
{
  int i;

  reserved = PAGE_ALLOC(page_size);
  byte_t *page;

  for(i=0;i < ptbl_size;++i)
  {
    ptable[i] = reserved;
  }

  // L2 RAM
  page = PAGE_ALLOC(page_size * 4);
  ptable[0] = page;
  ptable[1] = page + page_size;
  ptable[2] = page + page_size*2;
  ptable[3] = page + page_size*3;

  DEFINE_PAGE(MC_BSP0_REGS); // 0x18C0000
  DEFINE_PAGE(MC_BSP1_REGS);
  DEFINE_PAGE(MC_BSP2_REGS);
  DEFINE_PAGE(EMIFA_REGS);
  DEFINE_PAGE(L2_REGS);
  DEFINE_PAGE(HPI_REGS);

  DEFINE_PAGE(TIMER0_REGS);
  //DEF_CB_PAGE(TIMER0_REGS,timer0_cb);
  DEFINE_PAGE(TIMER1_REGS);

  DEFINE_PAGE(INT_SELECT_REGS);
  DEFINE_PAGE(EDMA_REGS);
  //DEF_CB_PAGE(EDMA_REGS,edma_reg_cb);
  DEFINE_PAGE(TIMER2_REGS);
  DEFINE_PAGE(QDMA_REGS);


  DEFINE_PAGE(TIMER2_REGS);

  //EMIFA CE0   use 128M
  page = PAGE_ALLOC(128 * 4 * page_size);
  for(i=0; i < (128*4); ++i)
  {
    ptable[page_tag(EMIFA_CE0)+i] = page + i * page_size;
  }
}

L2MemCtroller::~L2MemCtroller()
{
}

void L2MemCtroller::status()
{
  //TODO
}

END_NS