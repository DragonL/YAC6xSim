#ifndef CORE_N_UNIT_HPP
#define CORE_N_UNIT_HPP

#include "common/inc/def.hpp"
#include "core/inc/unit.hpp"

BEGIN_NS
class Core;
class NoneUnit : public Unit
{
public:
  NoneUnit(int id):Unit(id){}
  static void decode(Core*,Instruction*);     //v
  inline static void send(Core*,Instruction*); //v

  DEF_DE_FUNC(de_32bit,nop);
};
END_NS

#endif // CORE_N_UNIT_HPP