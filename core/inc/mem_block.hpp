#ifndef CORE_MEM_BLOCK_HPP
#define CORE_MEM_BLOCK_HPP

#include "common/inc/def.hpp"

BEGIN_NS

  // special memory block
class MemBlock 
{
protected:
  md_addr_t _start;
  word_t _len_in_byte;
  word_t _len_in_word;
  word_t *buf;

  inline word_t *get_buf()
  {
    return buf;
  }

public:
  MemBlock(md_addr_t start,word_t len):_start(start),_len_in_byte(len)
  {
    if(len == 0)
    {
      return;
    }
    if(len % 4 == 0)
    {
      _len_in_word = len / 4;
    }
    else
    {
      _len_in_word= (len / 4) + 1;
    }
    buf = (word_t*)calloc(1, _len_in_word * 4);
    memset(buf,0,_len_in_word*4);
  }

  inline bool include(md_addr_t addr)
  {
    return ((addr <= (_start + _len_in_byte)) && (addr >= _start));
  }

  template<class T>
  inline T read(md_addr_t addr)
  {
    return *(T*)((char*)buf + addr - _start);
  }

  template<class T>
  inline void write(md_addr_t addr, T val)
  {
    T *p = (T*)((char*)buf + addr - _start);
    *p = val;
  }

  inline word_t read_word(md_addr_t addr)
  {
    return read<word_t>(addr);
  }

  inline void write_word(md_addr_t addr, word_t val)
  {
    write(addr,val);
  }

  inline half_t read_half(md_addr_t addr)
  {
    return read<half_t>(addr);
  }

  inline void write_half(md_addr_t addr, half_t val)
  {
    write(addr,val);
  }
};



END_NS

#endif // CORE_MEM_BLOCK_HPP