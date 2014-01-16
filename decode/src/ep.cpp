#include "decode/inc/ep.hpp"
#include "decode/inc/inst_fetch_ctrl.hpp"

BEGIN_NS

void EP::add(code_t c){
  _code[_code_num++] = c;
}

//TODO remove it
void EP::gen_inst(std::vector<Instruction*>& inst_vec,bool use_cache)
{
  uint pc = get_addr();
  for (size_t i = 0;i < _code_num;i++)
  {
    code_t code = _code[i];

    //Instruction *pInst = new Instruction(code, pc & 0xFFFFFFE0,pc);
    // Instruction *inst = 
    //  InstFetchController::fetch_inst(code,pc & 0xFFFFFFE0,pc,use_cache);
                        
    //inst_vec.push_back(inst);
    pc += 4;
  }
}


END_NS