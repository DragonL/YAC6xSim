#ifndef DECODE_EP_HPP
#define DECODE_EP_HPP

#include "common/inc/def.hpp"
#include "decode/inc/inst.hpp"

BEGIN_NS

class EP
{
private:
  code_t _code[8];
  size_t _code_num;  // valide number of codes in this EP.   1 ~ 8
  md_addr_t _start_addr;
  
public:
  EP(md_addr_t addr):_code_num(0),_start_addr(addr) {}
  void add(code_t);
  void gen_inst(std::vector<Instruction*>&, bool use_cache = true); // dispatch instructions to each unit

  inline word_t get_code(int num)
  {
    return _code[num];
  }

  //return instruction number
  inline word_t gen_inst(Instruction *buf)
  {
    uint pc = get_addr();
    Instruction *instBuf = buf;
    for (size_t i = 0;i < _code_num;i++)
    {
      code_t code = _code[i];
      Instruction *pInst = new(instBuf) Instruction(code,pc);
      pc += 4;
      instBuf++;
    }
    return _code_num;
  }

  inline size_t code_num(){
    return _code_num;
  }

  inline md_addr_t get_addr()
  {
    return _start_addr;
  }
};

END_NS

#endif