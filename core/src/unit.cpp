
#include "core/inc/unit.hpp"
#include "core/inc/core.hpp"

BEGIN_NS

/*
Specified creg z
Conditional
Register Bit: 31 30 29 28
Unconditional 0 0 0 0
Reserved      0 0 0 1
B0            0 0 1 z
B1            0 1 0 z
B2            0 1 1 z
A1            1 0 0 z
A2            1 0 1 z
A0            1 1 0 z
Reserved 1 1 1 x(1)
*/
struct reg_idx_t
{
  word_t side;
  word_t idx;
};

reg_idx_t reg_cond_tbl[16] = 
{
  {3,0}, // not use
  {3,0}, // not use
  {1,0}, // B0
  {1,0}, // B0
  {1,1}, // B1
  {1,1}, // B1
  {1,2}, // B2
  {1,2}, // B2
  {0,1}, // A1
  {0,1}, // A1
  {0,2}, // A2
  {0,2}, // A2
  {0,0}, // A0
  {0,0}, // A0
  {3,0}, // not use
  {3,0}, // not use
};

word_t* Unit::get_cond_reg_addr(Core *core, word_t creg_z)
{
  reg_idx_t *reg_idx;

  reg_idx = &reg_cond_tbl[creg_z];

  // get reg value
  return core->get_reg_addr(reg_idx->side,reg_idx->idx);
}

/*
bool Unit::cond(Core *core, word_t creg_z)
{
  if (creg_z == 0)
  {
    return true;
  }

  reg_idx_t *reg_idx;

  reg_idx = &reg_cond_tbl[creg_z];

  // get reg value
  word_t reg_val = core->reg_read(reg_idx->side,reg_idx->idx);

  //return !((creg_z & 0x1) ^ (reg_val == 0));
  return (creg_z & 0x1) == (reg_val == 0);
}
*/


/*
bool Unit::cond2(Core *core_p, word_t creg_z)
{
  reg_idx_t *reg_idx;

  reg_idx = &reg_cond_tbl[creg_z];

  // get reg value
  word_t reg_val = core_p->reg_read(reg_idx->side,reg_idx->idx);

  //return !((creg_z & 0x1) ^ (reg_val == 0));
  return (creg_z & 0x1) == (reg_val == 0);
}
*/


END_NS