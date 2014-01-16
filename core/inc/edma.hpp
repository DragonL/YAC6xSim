#ifndef CORE_EDMA_HPP
#define CORE_EDMA_HPP

#include "common/inc/def.hpp"
#include "core/inc/core.hpp"

BEGIN_NS

class EDMA // CC and TC
{
private:
  struct edma_tr_t
  {
    word_t opt;
    word_t src;
    word_t cnt;
    word_t dst;
  };

  typedef edma_tr_t *edma_tr_t_p;

public:
  static void cc_proc(Core *core);
};

END_NS

#endif