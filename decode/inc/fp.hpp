#ifndef DECODE_FP_HPP
#define DECODE_FP_HPP

#include <list>
#include "common/inc/def.hpp"
#include "decode/inc/ep.hpp"
#include "core/inc/core.hpp"

BEGIN_NS

class Core;

class FP{
private:
  code_t _code[8];
  
public:
  FP(code_t* pc);
  void form_ep_list(Core *pCore, std::list<EP*>&,md_addr_t pc);

  // form only one ep
  inline void form_ep(Core *pCore,EP *ep,md_addr_t pc)
  {
    bool isNextParalell = false;
    int used = 0;
    EP *pCurEP = NULL;
    code_t curCode;
    word_t ep_num = 0;
    while (used < 8)
    {
      curCode = _code[used++];

      // printf("%#x\n",_code[used_code++]);
      if (!isNextParalell)
      {
        if(ep_num == 1)
        {
          break; // have 1 EP
        }
        pCurEP = new(ep) EP(pc);
        ep_num = 1;
      }

      // check if next code parallel
      isNextParalell = next_parallel_p(curCode);

      // add this code to EP
      pCurEP->add(curCode);
      pc += 4;
    }
  }
};

END_NS




















#endif