#ifndef PROFILE_BASIC_BLOCK_HPP
#define PROFILE_BASIC_BLOCK_HPP

#include "common/inc/def.hpp"

BEGIN_NS

class BasicBlock
{
public:
  md_addr_t start;
  md_addr_t end;
  word_t bytes_len;
  word_t call_times;
  byte_t jit_sended;

  BasicBlock()
  {
  }

  BasicBlock(md_addr_t addr):
    start(addr),
    end(addr),
    call_times(1),
    bytes_len(0),
    jit_sended(0)
  {
  }

  static BasicBlock* alloc(md_addr_t addr);
};

END_NS

#endif