#ifndef DECODE_INST_FETCH_CTRL_HPP
#define DECODE_INST_FETCH_CTRL_HPP

#include "decode/inc/fp.hpp"
#include "decode/inc/ep.hpp"
#include "decode/inc/inst.hpp"

BEGIN_NS

#define INST_CACHE_SIZE 4096
#define INST_CACHE_MASK 0x3FFC
#define GET_INST_FLAG(code) ((code & INST_CACHE_MASK) >> 2)

class InstFetchController
{

private:
  static Instruction instCache[INST_CACHE_SIZE];
};

END_NS

#endif // DECODE_INST_FETCH_CTRL_HPP