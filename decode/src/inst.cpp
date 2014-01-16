#include "decode/inc/inst.hpp"
#include "core/inc/m_unit.hpp"

BEGIN_NS

Instruction::Instruction(code_t c,md_addr_t code_addr):
  _code(c),_code_addr(code_addr),de_func(NULL),nop_count(0),bb(NULL),jit_func(NULL),
  next(NULL)
{
  op_type = Instruction::get_op_type_from_code(_code);
  unit_type = (byte_t)Instruction::get_unit_type((op_code_t)op_type,_code);
  next_p = c & 0x01;
}

unit_t Instruction::get_unit_type(op_code_t op_type, code_t code)
{
  bool is_side_a = side_a_p(code);
  if (op_type >= OP_N_UNIT_32BIT_DINT_RINT_SWE_SWENR && op_type <= OP_N_UNIT_16BIT_Unop)
  {
    return UNIT_None;
  }

  if (op_type >= OP_L_UNIT_32BIT_1_OR_2_SRC && op_type <= OP_L_UNIT_16BIT_Lx1)
  {
    if (is_side_a)
    {
      return UNIT_L1;
    }
    else
    {
      return UNIT_L2;
    }
  }

  if (op_type >= OP_M_UNIT_32BIT_EXT_COMPOUND && op_type <= OP_M_UNIT_16BIT_M3)
  {
    if (is_side_a)
    {
      return UNIT_M1;
    }
    else
    {
      return UNIT_M2;
    }
  }

  if (op_type >= OP_D_UNIT_32BIT_1_OR_2_SRC && op_type <= OP_D_UNIT_32BIT_LK_WD){
    if (is_side_a)
    {
      return UNIT_D1;
    }
    else
    {
      return UNIT_D2;
    }
  }

  if(op_type == OP_D_UNIT_32BIT_LD_ST_LONG_IMMED)
  {
    return UNIT_D2; // only exe on D2
  }

  if (op_type >= OP_D_UNIT_32BIT_LD_ST_BASIC && op_type <= OP_D_UNIT_32BIT_LD_ST_DW)
  {
    uint y = get_uint(code,7,1);
    if (y == 0)
    {
      return UNIT_D1;
    }
    else
    {
      return UNIT_D2;
    }
  }

  if (op_type >= OP_S_UNIT_32BIT_1_OR_2_SRC && op_type <= OP_S_UNIT_16BIT_Sx1b)
  {
    if (is_side_a)
    {
      return UNIT_S1;
    }else
    {
      return UNIT_S2;
    }
  }

  return UNIT_None;
}

// get code type of 32-bit code
op_code_t Instruction::get_op_type_from_code(code_t code)
{
  
  code_t bit_2_5 = get_uint(code,2,4);
  code_t s_bit_1 = get_uint(code,1,1);

  if (bit_2_5 == 0x8)
  {  // 0b 1000sp  base .S unit
    code_t op_bit_6_11 = get_uint(code,6,6);
    code_t x_bit_12 = get_uint(code,12,1);
    if (x_bit_12 == 0x0 && op_bit_6_11 == 0x5)
    { // ob 0 000101 1000sp
      return OP_S_UNIT_32BIT_ADDKPC; // S3
    }
    if (op_bit_6_11 == 0xD)
    { // 0b 001101 1000sp
      code_t bit_23_27 = get_uint(code,23,5);
      if (bit_23_27 == 0x0)
      {
        return OP_S_UNIT_32BIT_B_REG; // S6
      }
      else if (bit_23_27 == 0x1)
      {
        return OP_S_UNIT_32BIT_BNOP_REG; // S10
      }
      else
      {
        return OP_UNDEF; // error
      }
    }
    if (op_bit_6_11 == 0x0)
    {
      return OP_S_UNIT_32BIT_BDEC_OR_BPOS; // S8
    }
    if (op_bit_6_11 == 0x4 && x_bit_12 == 0x0)
    {
      return OP_S_UNIT_32BIT_BNOP_DISP; // S9
    }
    if (op_bit_6_11 == 0x3A)
    {  // 0b x 111100 1000sp
      return OP_S_UNIT_32BIT_UNARY;  // S14
    }
    if ((get_uint(code,21,7) == 0x0) && (get_uint(code,6,12) == 0x3) && (s_bit_1 == 0x1))
    {
      return OP_S_UNIT_32BIT_B_PTR; // S7
    }
    return OP_S_UNIT_32BIT_1_OR_2_SRC; // S1
  }

  // NOP
  if (get_uint(code,1,12) == 0 &&
    get_uint(code,17,15) ==0)
  {
      return OP_N_UNIT_32BIT_IDLE_NOP;
  }

  code_t bit_2_6 = get_uint(code,2,5);
  code_t creg_z = get_uint(code,28,4);

  if (get_mask_code(bit_2_6,3) == 0x6)
  { //    0b 110sp    .L unit
    if (get_uint(code,5,7) == 0x1A)
    { //    0b 0011010 110sp
      return OP_L_UNIT_32BIT_UNARY;
    }
    if (creg_z == 0x1)
    {
      return OP_L_UNIT_32BIT_1_OR_2_SRC_NON_COND;
    }
    return OP_L_UNIT_32BIT_1_OR_2_SRC;
  }

  if (bit_2_6 == 0)
  {
    return OP_M_UNIT_32BIT_MPY;
  }

  if (bit_2_6 == 0x10)
  { // 0b 10000sp  (s == 1)
    if (s_bit_1 == 0x1 && get_uint(code,10,8) == 0x1)
    {
      return OP_D_UNIT_32BIT_LK_WD; // D4
    }

    return OP_D_UNIT_32BIT_1_OR_2_SRC; // D1
  }

  code_t bit_2_3 = get_uint(code,2,2);
  if (bit_2_3 == 0x3)
  {
    if (creg_z == 0x1)
    {
      return OP_D_UNIT_32BIT_ADDAX_LONG_IMMED; // D3
    }
    return OP_D_UNIT_32BIT_LD_ST_LONG_IMMED; // D6
  }

  if (bit_2_3 == 0x1)
  {
    //if(get_uint(code,8,1) == 0x1){
    //  return OP_D_UNIT_32BIT_LD_ST_DW; // D7,D8
    //}
    return OP_D_UNIT_32BIT_LD_ST_BASIC; // D5 + D7 + D8
  }

  if (bit_2_5 == 0xC)
  { // EXT code : 0b 1100sp
    code_t bit_10_11 = get_uint(code,10,2);
    code_t ext_op = get_uint(code,6,5);
    if (bit_10_11 <= 0x1 )
    {  // EXT .M
      if (ext_op == 0x3)
      { // ob 00011
        return OP_M_UNIT_32BIT_EXT_UNARY;
      }
      if (creg_z == 0x1)
      {
        return OP_M_UNIT_32BIT_EXT_1_OR_2_SRC_NON_COND;
      }
      return OP_M_UNIT_32BIT_EXT_COMPOUND;
    }
    else if (bit_10_11 == 0x3)
    { // EXT .S
      if (creg_z == 0x1)
      {
        return OP_S_UNIT_32BIT_EXT_1_OR_2_SRC_NON_COND; // S13
      }
      return OP_S_UNIT_32BIT_EXT_1_OR_2_SRC; // S4
    }
    else 
    { // 0x2
      return OP_D_UNIT_32BIT_EXT_1_OR_2_SRC; // D2
    }
  }

  if (bit_2_5 == 0x2)
  { // 0b 0010sp
    return OP_S_UNIT_32BIT_FIELD_OP; // S15
  }

  if (bit_2_5 == 0xA)
  { // 0b 1010sp
    return OP_S_UNIT_32BIT_MVK_MVKH;  // S12
  }

  if (bit_2_6 == 0x14)
  { // 0b 10100sp
    return OP_S_UNIT_32BIT_ADDK; // S2
  }

  if (bit_2_6 == 0x4)
  { // 0b 00100sp
    if (creg_z == 0x1)
    {
      return OP_S_UNIT_32BIT_CALL_NON_COND_IMMED_NOP5; // S11
    }
    return OP_S_UNIT_32BIT_B_DISP; // S5
  }

  return OP_UNDEF;
}

#define OP_16BIT_XPATH_MASK 0x1000

#define IS_XPATH(code) ((code & OP_16BIT_XPATH_MASK) != 0)
#define IS_SAT(expasion) ((expasion & 0x01) != 0)
#define IS_HIGH_RS(expasion) ((expasion & 0x10) != 0)

/*
SAT op Mnemonic
0 0 0 MPY (.unit) src1, src2, dst
0 0 1 MPYH (.unit) src1, src2, dst
0 1 0 MPYLH (.unit) src1, src2, dst
0 1 1 MPYHL (.unit) src1, src2, dst
1 0 0 SMPY (.unit) src1, src2, dst
1 0 1 SMPYH (.unit) src1, src2, dst
1 1 0 SMPYLH (.unit) src1, src2, dst
1 1 1 SMPYHL (.unit) src1, src2, dst
*/

END_NS