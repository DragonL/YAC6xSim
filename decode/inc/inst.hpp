#ifndef DECODE_INST_HPP
#define DECODE_INST_HPP

#include "common/inc/def.hpp"
#include "profiler/inc/basic_block.hpp"

BEGIN_NS

class Instruction;
class Instruction
{
private:
  code_t _code;
  md_addr_t _code_addr;

  // use for decode
  ATTR_RW(de_func_t,de_func)
  ATTR_RW(jit_func_t,jit_func)
  ATTR_RW(BasicBlock*,bb)
  ATTR_RW(byte_t,cregz)
  ATTR_RW(byte_t,side)
  ATTR_RW(byte_t,xside)
  ATTR_RW(byte_t,dst)
  ATTR_RW(word_t,src1) // src1 extended to word_t
  ATTR_RW(word_t,src2)
  ATTR_RW(word_t*,cond_reg_phy_addr)
  ATTR_RW(Instruction*,next)
  ATTR_RW(byte_t,next_p)
  ATTR_RW(byte_t,unit_type)
  ATTR_RW(byte_t,op_type)
  ATTR_RW(byte_t,nop_count)
  //ATTR_RW(half_t,dc_type)

public:
  Instruction():_code_addr(1){} // default an invalid addr

  // used for 32-bit code
  Instruction(code_t c, md_addr_t code_addr);

  inline md_addr_t get_base_addr()
  {
    return _code_addr & 0xFFFFFFE0;
  }
  inline md_addr_t get_code_addr()
  {
    return _code_addr;
  }
  inline void set_code_addr(md_addr_t addr)
  {
    _code_addr = addr;
  }
  inline code_t get_code()
  {
    return _code;
  }
  inline std::string to_s()
  {
    std::stringstream ss;
    ss << "op code:" << to_hex_str(_code) << "\n"; 
    ss << "op code:" << to_bin_str(_code) << "\n"; 
    ss << "op code type:" << op_type_name_map[(int)get_op_type()] << "\n";
    ss << "unit:" << unit_type_name_map[(int)get_unit_type()] << "\n";
    return ss.str();
  }

  inline bool is_next_p()
  {
    return next_p;
  }

  inline static bool is_compact_fp_header(code_t code)
  {
    return (code >> 28) == 0xE;
  }

  static unit_t get_unit_type(op_code_t op_type, code_t code);
  static op_code_t get_op_type_from_code(code_t code);
  static void pre_decode_16bit(word_t expansion,code_t code,Instruction *inst16bit);
};


END_NS

#endif