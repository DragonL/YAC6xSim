#include "decode/inc/fp.hpp"
#include <stdio.h>

BEGIN_NS

FP::FP(code_t* pc){
  for(int i = 0;i < 8;i++){
    _code[i] = *pc++;
  }
}

void FP::form_ep_list(Core *pCore, std::list<EP*>& ep_list, md_addr_t pc){
  bool isNextParalell = false;
  int used = 0;
  EP *pCurEP = NULL;
  code_t curCode;
  while (used < 8){
    curCode = _code[used++];

    // printf("%#x\n",_code[used_code++]);
    if (!isNextParalell){
      if(!ep_list.empty())
      {
        break; // have 1 EP
      }
      pCurEP = new EP(pc);  //TODO use EP heap
      ep_list.push_back(pCurEP);
    }

    // check if next code parallel
    isNextParalell = next_parallel_p(curCode);

    // add this code to EP
    pCurEP->add(curCode);
    pc += 4;
  }
}

END_NS