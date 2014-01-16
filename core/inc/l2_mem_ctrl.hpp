#ifndef CORE_L2_MEM_CTRL_HPP
#define CORE_L2_MEM_CTRL_HPP

#include "common/inc/def.hpp"
#include "core/inc/mem_block.hpp"

BEGIN_NS

class MemRange
{
  ATTR_RW(md_addr_t, start)
  ATTR_RW(md_addr_t, len)

public:
  inline bool include(md_addr_t addr)
  {
    return ((addr >= start) && (addr < (start + len)));
  }

  MemRange(word_t start_,word_t len_):
    start(start_),len(len_)
  {}
};

class L2MemCtroller
{
public:
  // memory callback
  typedef word_t (* __fastcall mem_cb_t)(byte_t type,md_addr_t addr,word_t val);

  static const word_t ptbl_size = 16 * 1024; // 16K table entry
  static const word_t l2_ram_size = 1024 * 1024; // 1024K
  static const word_t page_size = 256 * 1024; // 256K

  static void init()
  {
    if(NULL == instance)
    {
      instance = new L2MemCtroller();
    }
  }

  static L2MemCtroller* get()
  {
    return instance;
  }

private:
  // reserved page
  static byte_t *reserved;

  word_t code[8];

  static L2MemCtroller *instance;
  L2MemCtroller();

  ATTR_RW(md_addr_t, write_check_addr)

public:
  // 256K page table
  static byte_t *ptable[ptbl_size]; // 16K 256K pages 

  static inline word_t page_tag(md_addr_t addr)
  {
    return (addr >> 18);
  }

  static inline word_t page_offset(md_addr_t addr)
  {
    return (addr & (page_size - 1));
  }

  static inline phy_addr_t get_phy_addr(md_addr_t addr)
  {
    return (phy_addr_t)(ptable[page_tag(addr)] + page_offset(addr));
  }

public:
  void status();

public:
  

  virtual ~L2MemCtroller();

  static void mem_write_ciprl(word_t val);

  template<class T>
  static inline T mem_read(md_addr_t addr)
  {
    word_t tag = page_tag(addr);
    word_t offset = page_offset(addr);
    byte_t *page = ptable[tag];
    return *(T*)(page + offset);
  }

  static inline byte_t mem_read_byte(md_addr_t addr)
  {
    return mem_read<byte_t>(addr);
  }

  static inline half_t mem_read_half(md_addr_t addr)
  {
    return MD_SWAPH(mem_read<half_t>(addr));
  }

  static inline word_t mem_read_word(md_addr_t addr)
  {
    return MD_SWAPW(mem_read<word_t>(addr));
  }

#ifdef HOST_HAS_QWORD
  static inline qword_t mem_read_qword(md_addr_t addr)
  {
    return MD_SWAPQ(mem_read<qword_t>(addr));
  }
#endif /* HOST_HAS_QWORD */

  template<class T>
  inline void mem_load(md_addr_t addr,T val)
  {
    word_t tag = page_tag(addr);
    byte_t *page = ptable[tag];
    T* addr_to_write =  (T*)(page + page_offset(addr));
    *addr_to_write = val;
  }

  template<class T>
  void mem_write(md_addr_t addr,T val)
  {
    // some special case
    if(addr == 0x01A0FFE4) // CIPRL
    { // write to CIPRL == clear the bit
      word_t old_ciprl = mem_read_word(addr);
      val = MD_SWAPW(val);
      old_ciprl &= ~val;
      mem_load_word_xendian(addr,old_ciprl);
      return;
    }

    mem_load(addr,val);
  }

  inline void mem_write_byte(md_addr_t addr, byte_t val)
  {
    mem_write<byte_t>(addr,val);
  }

  inline void mem_write_half(md_addr_t addr, half_t val)
  {
    mem_write<half_t>(addr,(val));
  }

  inline void mem_write_half_xendian(md_addr_t addr, half_t val)
  {
    mem_write<half_t>(addr,MD_SWAPH(val));
  }

  inline void mem_load_word(md_addr_t addr, word_t val)
  {
    mem_load<word_t>(addr,val);
  }

  inline void mem_write_word(md_addr_t addr, word_t val)
  {
    mem_write<word_t>(addr,val);
  }

  inline void mem_write_word_xendian(md_addr_t addr, word_t val)
  {
    mem_write<word_t>(addr,MD_SWAPW(val));
  }

  inline void mem_load_word_xendian(md_addr_t addr, word_t val)
  {
    mem_load<word_t>(addr,MD_SWAPW(val));
  }

#ifdef HOST_HAS_QWORD
  inline void mem_write_qword_xendian(md_addr_t addr, qword_t val){
    mem_write<qword_t>(addr,MD_SWAPQ(val));
    //mem_write<word_t>(addr+4,MD_SWAPW((word_t)(val & 0xFFFFFFFF)));
    //mem_write<word_t>(addr,MD_SWAPW((word_t)(val >> 32)));
  }
#endif /* HOST_HAS_QWORD */
};
END_NS

#endif //CORE_L2_MEM_CTRL_HPP