#include "core/inc/m_unit.hpp"
#include "core/inc/core.hpp"

BEGIN_NS

//    31 29 28|27  23|22  18|17  13|12|11|10  6| 5 4 3 2 1 0
//    creg  z | dst  |src2  | src1 |x |0 | op  | 1 1 0 0 s p
//      3   1 | 5    | 5    | 5    |1 |  | 5   |         1 1
void MUnit::decode_32bit_ext_compound(Core *core,code_t code,Instruction *inst)
{
  word_t creg_z = code >> 28;
  word_t dst = get_uint(code,23,5);
  word_t src2 = get_uint(code,18,5);
  word_t src1 = get_uint(code,13,5);
  word_t x = get_uint(code,12,1); // cross_path for src2
  word_t op = get_uint(code,6,5);
  word_t side = get_uint(code,1,1);
  
  word_t xside = (x == 1) ? (side ^ 0x1) : side;
  de_func_t de_func;
  switch(op)
  {
    case 0x13: // 0b : 1 0011 AVG2
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,avg2);
      break;

    case 0x12: // 0b 1 0010  AVGU4
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,avgu4);
      break;

    case 0x0C: // 0b 0 1100  DOTP2
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,dotp2_f1);
      break;
  
    case 0x0B:// 0b 0 1011 DOTP2 sllong
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,dotp2_f2);
      break;

    case 0x09: // 0b 0 1001 DOTPN2
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,dotpn2);
      break;

    case 0x07: // 0b 0 0111 DOTPNRSU2
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,dotpnrsu2);
      break;

    case 0x0D: // 0b 0 1101 DOTPRSU2
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,dotprsu2);
      break;

    case 0x02: // 0b 0 0010 DOTPSU4
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,dotpsu4);
      break;

    case 0x06: // 0b 0 0110 DOTPU4
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,dotpu4);
      break;

    case 0x11: // 0b 1 0001 GMPY4
      core->panic("MUnit:GMPY4");
      break;

    case 0x14: // 0b 1 0100 MPYHI
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,mpyhi);
      break;

    case 0x10: // 0b 1 0000 MPYHIR
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,mpyhir);
      break;

    case 0x15: // 0b 1 0101 MPYLI
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,mpyli);
      break;

    case 0x0E: // 0b 0 1110 MPYLIR
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,mpylir);
      break;

    case 0x05: // 0b 0 0101 MPYSU4
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,mpysu4);
      break;

    case 0x04: // 0b 0 0100 MPYU4
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,mpyu4);
      break;

    case 0x00: // 0b 0 0000 MPY2
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,mpy2);
      break;

    case 0x1D: // 0b 1 1101 ROTL (shift by register)
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,rotl_f1);
      break;

    case 0x1E:  // 0b 1 1110 ROTL (shift by ucst5)
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,rotl_f2);
      break;

    case 0x01: // 0b 0 0001 SMPY2
      core->panic("MUnit:SMPY2");
      break;

    case 0x1A: // 0b 1 1010 SSHVR
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_compound,sshvr);
      break;

    case 0x1C: // 0b 1 1100 SSHVL
      core->panic("MUnit:SSHVL");
      break;

    default:
      core->panic("MUnit:EXT_COMPOUND");
      break;
  }

  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_xside(xside);
  inst->set_src1(src1);
  inst->set_src2(src2);
  inst->set_dst(dst);
}

// 31 29 28|27  23|22  18|17  13|12| 11|  10 9 8 7 6 5 4 3 2 1 0
// creg  z |dst   |src2  |op    |x | 0 |   0 0 0 1 1 1 1 0 0 s p
// 3     1 |5     |5     |5     |1     |                     1 1
void MUnit::decode_32bit_ext_unary(Core *core,code_t code,Instruction *inst)
{
  word_t creg_z = get_uint(code,28,4);
  word_t dst = get_uint(code,23,5);
  word_t src2 = get_uint(code,18,5);
  word_t op = get_uint(code,13,5);
  word_t side = get_uint(code,1,1);
  word_t x = get_uint(code,12,1); // cross_path for src2
  word_t xside = (x == 1) ? (side ^ 0x1) : side;

  de_func_t de_func;
  switch(op)
  {
    case 0x1E: // 0b 1 1110 BITC4
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_unary,bitc4);
      break;

    case 0x1F: // 0b 1 1111 BITR
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_unary,bitr);
      break;

    case 0x1D: // 0b 1 1101 DEAL
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_unary,deal);
      break;

    case 0x1C: // SHFL
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_unary,shfl);
      break;

    case 0x1A: // 0b 1 1010 MVD
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_unary,mvd);
      break;

    case 0x19: // 0b 1 1001 XPND2
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_unary,xpnd2);
      break;

    case 0x18: // 0b 1 1000 XPND4
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_ext_unary,xpnd4);
      break;

    default:
      core->panic("MUnit:EXT_UNARY");
      break;
  }

  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_xside(xside);
  inst->set_src1(0);
  inst->set_src2(src2);
  inst->set_dst(dst);

  return;
}

// 31 29 28|27 23|22 18|17 13|12|11 7|6 5 4 3 2 1 0
// creg z  |dst  |src2 |src1 |x |op  |0 0 0 0 0 s p
// 3    1  |5    |5    |5    |1 |5   |          1 1
void MUnit::decode_32bit_mpy(Core *core,code_t code,Instruction *inst)
{
  word_t creg_z = get_uint(code,28,4);
  word_t dst = get_uint(code,23,5);
  word_t src2 = get_uint(code,18,5);
  word_t src1 = get_uint(code,13,5);
  word_t side = get_uint(code,1,1);
  word_t op = get_uint(code,7,5);
  word_t x = get_uint(code,12,1); // cross_path for src2
  word_t xside = (x == 1) ? (side ^ 0x1) : side;

  de_func_t de_func;
  switch(op)
  {
    case 0x19: // 11001 MPY
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpy_f1);
      break;

    case 0x18: // 11000 MPY cst5
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpy_f2);
      break;

    case 0x01: // 00001 MPYH
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyh);
      break;

    case 0x09: // 01001 MPYHL
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyhl);
      break;

    case 0x0F: // 01111 MPYHLU
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyhlu);
      break;

    case 0x0B: // 01011 MPYHSLU
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyhslu);
      break;

    case 0x03: // 00011 MPYHSU
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyhsu);
      break;

    case 0x07: // 00111 MPYHU
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyhu);
      break;

    case 0x0D: // 01101 MPYHULS
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyhuls);
      break;

    case 0x05: // 00101 MPYHUS
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyhus);
      break;

    case 0x11: // 10001 MPYLH
      //de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpylh);
      SET_DE_FUNC_NC_Z0_Z1(creg_z,MUnit,de_32bit_mpy,mpylh);
      break;

    case 0x13: // 10011 MPYLSHU
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpylshu);
      break;

    case 0x15: // 10101 MPYLUHS
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyluhs);
      break;

    case 0x17: // 10111 MPYLHU
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpylhu);
      break;

    case 0x1B: // 11011 MPYSU
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpysu_f1);
      break;

    case 0x1D: // 11101 MPYUS
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyus);
      break;

    case 0x1E: // 11110 MPYSU + scst5
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpysu_f2);
      break;

    case 0x1F: // 11111 MPYU
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyu);
      break;

    case 0x02: // 0 0010 SMPYH
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,smpyh);
      break;

    case 0x1A: // 1 1010 SMPY
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,smpy);
      break;

    case 0x12: // 1 0010 SMPYLH
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,smpylh);
      break;

    case 0x0A: // 1 0010 SMPYHL
      de_func = DE_FUNC_ADDR(MUnit,de_32bit_mpy,smpyhl);
      break;

    default:
      core->panic("MUnit:MPY");
      break;
  }

  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_xside(xside);
  inst->set_src1(src1);
  inst->set_src2(src2);
  inst->set_dst(dst);

  return;
}

void MUnit::decode(Core* pCore, Instruction* inst)
{
  op_code_t type = (op_code_t)inst->get_op_type();
  word_t code = inst->get_code();

  switch(type)
  {
//    31 29 28|27  23|22  18|17  13|12|11|10  6| 5 4 3 2 1 0
//    creg  z | dst  |src2  | src1 |x |0 | op  | 1 1 0 0 s p
//      3   1 | 5    | 5    | 5    |1 |  | 5   |         1 1
  case OP_M_UNIT_32BIT_EXT_COMPOUND:
    decode_32bit_ext_compound(pCore,code,inst);
    break;

// 31 29 28|27  23|22  18|17  13|12| 11|  10 9 8 7 6 5 4 3 2 1 0
// creg  z |dst   |src2  |op    |x | 0 |   0 0 0 1 1 1 1 0 0 s p
// 3     1 |5     |5     |5     |1     |                     1 1
  case OP_M_UNIT_32BIT_EXT_UNARY:
    decode_32bit_ext_unary(pCore,code,inst);
    break;

// 31 29 28|27 23|22 18|17 13|12|11 7|6 5 4 3 2 1 0
// creg z  |dst  |src2 |src1 |x |op  |0 0 0 0 0 s p
// 3    1  |5    |5    |5    |1 |5   |          1 1
  case OP_M_UNIT_32BIT_MPY:
    decode_32bit_mpy(pCore,code,inst);
    break;

  default:
    break;
  }
}

// s2,xs2,s2
DE_FUNC(MUnit,de_32bit_ext_compound,avg2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t sa_1,sa_0,sb_1,sb_0,dst_1,dst_0;
  word_t dst_val;

  sa_1 = get_sign_ext_msb16(src1_val);
  sa_0 = get_sign_ext_lsb16(src1_val);
  sb_1 = get_sign_ext_msb16(src2_val);
  sb_0 = get_sign_ext_lsb16(src2_val);

  dst_1 = (sa_1 + sb_1 + 1) >> 1;
  dst_0 = (sa_0 + sb_0 + 1) >> 1;
  dst_1 = dst_1 & 0xFFFF;
  dst_0 = dst_0 & 0xFFFF;

  dst_val = (dst_1 << 16) | dst_0;

  core->push_reg_delay_ch(side,dst,dst_val,1);
}

// u4,xu4,u4
DE_FUNC(MUnit,de_32bit_ext_compound,avgu4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);

  word_t ua_3,ua_2,ua_1,ua_0;
  word_t ub_3,ub_2,ub_1,ub_0;
  word_t dst_3,dst_2,dst_1,dst_0;
  word_t dst_val;

  ua_3 = get_uint(src1_val,24,8);
  ua_2 = get_uint(src1_val,16,8);
  ua_1 = get_uint(src1_val,8,8);
  ua_0 = get_uint(src1_val,0,8);
  ub_3 = get_uint(src2_val,24,8);
  ub_2 = get_uint(src2_val,16,8);
  ub_1 = get_uint(src2_val,8,8);
  ub_0 = get_uint(src2_val,0,8);

  dst_3 = (ua_3 + ub_3 + 1) >> 1;
  dst_2 = (ua_2 + ub_2 + 1) >> 1;
  dst_1 = (ua_1 + ub_1 + 1) >> 1;
  dst_0 = (ua_0 + ub_0 + 1) >> 1;

  dst_val = (dst_3 << 24) | (dst_2 << 16) |
    (dst_1 << 8) | dst_0;

  core->push_reg_delay_ch(side,dst,dst_val,1);
}

// s2,xs2,int
DE_FUNC(MUnit,de_32bit_ext_compound,dotp2_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_hi,a_lo,b_hi,b_lo,dst_val;
  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_val = (long)a_hi * (long)b_hi + 
    (long)a_lo * (long)b_lo;

  core->push_reg_delay_ch(side,dst,dst_val,3);
}

// s2,xs2,sllong
DE_FUNC(MUnit,de_32bit_ext_compound,dotp2_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_hi, a_lo, b_hi, b_lo;
  sqword_t dst_qval;

  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_qval = (long)a_hi * (long)b_hi + 
    (long)a_lo * (long)b_lo;

  DE_UPDATE_DELAY_REG2(side,dst,dst_qval,3);
}

// s2,xs2,int
DE_FUNC(MUnit,de_32bit_ext_compound,dotpn2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_hi,a_lo,b_hi,b_lo;
  word_t dst_val;

  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);
  dst_val = (long)a_hi * (long)b_hi - 
    (long)a_lo * (long)b_lo;

  core->push_reg_delay_ch(side,dst,dst_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,dotpnrsu2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t sa_hi, sa_lo, ub_hi, ub_lo;
  word_t dst_val;

  sa_hi = get_sign_ext_msb16(src1_val);
  sa_lo = get_sign_ext_lsb16(src1_val);
  ub_hi = get_uint(src2_val,16,16);
  ub_lo = get_uint(src2_val,0,16);

  dst_val = (((long)sa_hi * (long)ub_hi - 
    (long)sa_lo * (long)ub_lo) + 0x8000) >> 16;

  core->push_reg_delay_ch(side,dst,dst_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,dotprsu2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t sa_hi, sa_lo, ub_hi, ub_lo;
  word_t dst_val;

  sa_hi = get_sign_ext_msb16(src1_val);
  sa_lo = get_sign_ext_lsb16(src1_val);
  ub_hi = get_uint(src2_val,16,16);
  ub_lo = get_uint(src2_val,0,16);

  dst_val = (((long)sa_hi * (long)ub_hi + 
    (long)sa_lo * (long)ub_lo) + 0x8000) >> 16;

  core->push_reg_delay_ch(side,dst,dst_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,dotpsu4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa_3,sa_2,sa_1,sa_0;
  word_t ub_3,ub_2,ub_1,ub_0;
  word_t dst_val;

  sa_3 = get_sign_ext(src1_val,24,8);
  sa_2 = get_sign_ext(src1_val,16,8);
  sa_1 = get_sign_ext(src1_val,8,8);
  sa_0 = get_sign_ext(src1_val,0,8);
  ub_3 = get_uint(src2_val,24,8);
  ub_2 = get_uint(src2_val,16,8);
  ub_1 = get_uint(src2_val,8,8);
  ub_0 = get_uint(src2_val,0,8);

  dst_val = sa_3 * ub_3 + sa_2 * ub_2 +
    sa_1 * ub_1 + sa_0 * ub_0;

  core->push_reg_delay_ch(side,dst,dst_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,dotpu4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t ua_3,ua_2,ua_1,ua_0;
  word_t ub_3,ub_2,ub_1,ub_0;
  word_t dst_3,dst_2,dst_1,dst_0;
  word_t dst_val;

  ua_3 = get_uint(src1_val,24,8);
  ua_2 = get_uint(src1_val,16,8);
  ua_1 = get_uint(src1_val,8,8);
  ua_0 = get_uint(src1_val,0,8);
  ub_3 = get_uint(src2_val,24,8);
  ub_2 = get_uint(src2_val,16,8);
  ub_1 = get_uint(src2_val,8,8);
  ub_0 = get_uint(src2_val,0,8);

  dst_val = ua_3 * ub_3 + ua_2 * ub_2
    + ua_1 * ub_1 + ua_0 * ub_0;

  core->push_reg_delay_ch(side,dst,dst_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,mpyhi)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval;
  long sa_hi,sb;

  sa_hi = get_sign_ext_msb16(src1_val);
  sb = get_sign_ext(src2_val, 0, 32);
  dst_qval = (sqword_t)sa_hi * (sqword_t)sb;

  DE_UPDATE_DELAY_REG2(side,dst,dst_qval,3);
}

// int,xint,int
DE_FUNC(MUnit,de_32bit_ext_compound,mpyhir)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval;
  long sa_hi, sb;

  sa_hi = get_sign_ext_msb16(src1_val);
  sb = get_sign_ext(src2_val, 0, 32);
  dst_qval = (sa_hi * (sqword_t)sb + 0x4000) >> 15;
  word_t dst_val = (word_t)(dst_qval & 0xFFFFFFFF); // round

  core->push_reg_delay_ch(side,dst,dst_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,mpyli)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval;
  long sa_lo, sb;

  sa_lo = get_sign_ext_lsb16(src1_val);
  sb = get_sign_ext(src2_val, 0, 32);
  dst_qval = (sqword_t)sa_lo * sb;

  DE_UPDATE_DELAY_REG2(side,dst,dst_qval,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,mpylir)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval;
  long sa_lo, sb;

  sa_lo = get_sign_ext_lsb16(src1_val);
  sb = get_sign_ext(src2_val, 0, 32);
  dst_qval = ((sqword_t)sa_lo * sb + 0x4000) >> 15;
  word_t dst_val = (word_t)(dst_qval & 0xFFFFFFFF); // round

  core->push_reg_delay_ch(side,dst,dst_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,mpysu4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);

  long sa_3,sa_2,sa_1,sa_0;
  word_t ub_3,ub_2,ub_1,ub_0;
  word_t dst_3,dst_2,dst_1,dst_0;
  sa_3 = get_sign_ext(src1_val,24,8);
  sa_2 = get_sign_ext(src1_val,16,8);
  sa_1 = get_sign_ext(src1_val,8,8);
  sa_0 = get_sign_ext(src1_val,0,8);
  ub_3 = get_uint(src2_val,24,8);
  ub_2 = get_uint(src2_val,16,8);
  ub_1 = get_uint(src2_val,8,8);
  ub_0 = get_uint(src2_val,0,8);

  dst_3 = (sa_3 * ub_3) & 0xFFFF;
  dst_2 = (sa_2 * ub_2) & 0xFFFF;
  dst_1 = (sa_1 * ub_1) & 0xFFFF;
  dst_0 = (sa_0 * ub_0) & 0xFFFF;

  word_t dst_val = dst_1 << 16 | dst_0;
  word_t dst2_val = dst_3 << 16 | dst_2;

  core->push_reg_delay_ch(side,dst,dst_val,3);
  core->push_reg_delay_ch(side,dst+1,dst2_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,mpyu4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);

  word_t ua_3,ua_2,ua_1,ua_0;
  word_t ub_3,ub_2,ub_1,ub_0;
  word_t dst_3,dst_2,dst_1,dst_0;
  ua_3 = get_uint(src1_val,24,8);
  ua_2 = get_uint(src1_val,16,8);
  ua_1 = get_uint(src1_val,8,8);
  ua_0 = get_uint(src1_val,0,8);
  ub_3 = get_uint(src2_val,24,8);
  ub_2 = get_uint(src2_val,16,8);
  ub_1 = get_uint(src2_val,8,8);
  ub_0 = get_uint(src2_val,0,8);

  dst_3 = (ua_3 * ub_3) & 0xFFFF;
  dst_2 = (ua_2 * ub_2) & 0xFFFF;
  dst_1 = (ua_1 * ub_1) & 0xFFFF;
  dst_0 = (ua_0 * ub_0) & 0xFFFF;

  word_t dst_val = dst_1 << 16 | dst_0;
  word_t dst2_val = dst_3 << 16 | dst_2;

  core->push_reg_delay_ch(side,dst,dst_val,3);
  core->push_reg_delay_ch(side,dst+1,dst2_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,mpy2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);

  long sa_hi,sa_lo;
  long sb_hi,sb_lo;

  sa_hi = get_sign_ext_msb16(src1_val);
  sa_lo = get_sign_ext_lsb16(src1_val);
  sb_hi = get_sign_ext_msb16(src2_val);
  sb_lo = get_sign_ext_lsb16(src2_val);
  word_t dst_val = sa_lo * sb_lo;
  word_t dst2_val = sa_hi * sb_hi;

  core->push_reg_delay_ch(side,dst,dst_val,3);
  core->push_reg_delay_ch(side,dst+1,dst2_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_compound,rotl_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);

  word_t shift = src1_val & 0x1F; // 5 bits

  word_t dst_val = (src2_val << shift) | (src2_val >> (32 - shift));
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_ext_compound,rotl_f2)
{
  DE_CONDITION(core,cregz);

  word_t shift = src1 & 0x1F; // 5 bits
  word_t src2_val = core->reg_read(xside,src2);

  word_t dst_val = (src2_val << shift) | (src2_val >> (32 - shift));
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_ext_compound,sshvr)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val;
  sword_t src1_val = core->reg_read(side,src1);
  if(src1_val >= 0 && src1_val <= 31)
  {
    dst_val = src2_val >> src1_val;
  }
  else if(src1_val > 31)
  {
    dst_val = src2_val >> 31;
  }
  else if(src1_val < -31)
  {
    dst_val = sat(src2_val << 31);
  }
  else
  {
    dst_val = sat(src2_val << (-src2_val));
  }
  core->push_reg_ch(side,dst,dst_val);
}


DE_FUNC(MUnit,de_32bit_ext_unary,bitc4)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);

  word_t ub_3,ub_2,ub_1,ub_0;
  word_t dst_3,dst_2,dst_1,dst_0;
  word_t dst_val;

  ub_3 = get_uint(src2_val,24,8);
  ub_2 = get_uint(src2_val,16,8);
  ub_1 = get_uint(src2_val,8,8);
  ub_0 = get_uint(src2_val,0,8);

  dst_3 = bit_count(ub_3,8);
  dst_2 = bit_count(ub_2,8);
  dst_1 = bit_count(ub_1,8);
  dst_0 = bit_count(ub_0,8);

  dst_val = (dst_3 << 24) |(dst_2 << 16) |
    (dst_1 << 8) | dst_0;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_ext_unary,bitr)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = bit_reverse(src2_val);
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_ext_unary,deal)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = deinterleave(src2_val);
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_ext_unary,shfl)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = shfl(src2_val);
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_ext_unary,mvd)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src2_val;
  core->push_reg_delay_ch(side,dst,dst_val,3);
}

DE_FUNC(MUnit,de_32bit_ext_unary,xpnd2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = xpnd2(src2_val);
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_ext_unary,xpnd4)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = xpnd4(src2_val);
  core->push_reg_delay_ch(side,dst,dst_val,1);
}


DE_FUNC(MUnit,de_32bit_mpy,mpy_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa,sb;
  word_t dst_val;

  sa = get_sign_ext_lsb16(src1_val);
  sb = get_sign_ext_lsb16(src2_val);
  dst_val = sa * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpy_f2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  long sa,sb;
  word_t dst_val;

  sa = get_sign_ext_lsb5_quick(src1);
  sb = get_sign_ext_lsb16(src2_val);
  dst_val = sa * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyh)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa,sb;
  word_t dst_val;

  sa = get_sign_ext_msb16(src1_val);
  sb = get_sign_ext_msb16(src2_val);
  dst_val = sa * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyhl)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa,sb;
  word_t dst_val;

  sa = get_sign_ext_msb16(src1_val); //msb16
  sb = get_sign_ext_lsb16(src2_val); //lsb16
  dst_val = sa * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyhlu)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t ua,ub;
  word_t dst_val;

  ua = get_msb16(src1_val);
  ub = get_lsb16(src2_val);
  dst_val = ua * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyhslu)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa;
  word_t ub;
  word_t dst_val;

  sa = get_sign_ext_msb16(src1_val);
  ub = get_lsb16(src2_val);
  dst_val = sa * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyhsu)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa;
  word_t ub;
  word_t dst_val;

  sa = get_sign_ext_msb16(src1_val);
  ub = get_msb16(src2_val);
  dst_val = sa * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyhu)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t ua,ub;
  word_t dst_val;

  ua = get_msb16(src1_val);
  ub = get_msb16(src2_val);
  dst_val = ua * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyhuls)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t ua;
  long sb;
  word_t dst_val;

  ua = get_msb16(src1_val);
  sb = get_sign_ext_lsb16(src2_val);
  dst_val = ua * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyhus)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t ua;
  long sb;
  word_t dst_val;

  ua = get_msb16(src1_val);
  sb = get_sign_ext_msb16(src2_val);
  dst_val = ua * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpylh_nc)
{
  NO_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa,sb;
  word_t dst_val;

  sa = get_sign_ext_lsb16(src1_val);
  sb = get_sign_ext_msb16(src2_val);
  dst_val = sa * sb;
  core->push_reg_delay_ch_1c_delay(side,dst,dst_val);
}

DE_FUNC(MUnit,de_32bit_mpy,mpylh_z0)
{
  DE_CONDITION_Z0(core);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa,sb;
  word_t dst_val;

  sa = get_sign_ext_lsb16(src1_val);
  sb = get_sign_ext_msb16(src2_val);
  dst_val = sa * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpylh_z1)
{
  DE_CONDITION_Z1(core);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa,sb;
  word_t dst_val;

  sa = get_sign_ext_lsb16(src1_val);
  sb = get_sign_ext_msb16(src2_val);
  dst_val = sa * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpylshu)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa;
  word_t ub;
  word_t dst_val;

  sa = get_sign_ext_lsb16(src1_val);
  ub = get_msb16(src2_val);
  dst_val = sa * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyluhs)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sb;
  word_t ua;
  word_t dst_val;

  ua = get_lsb16(src1_val);
  sb = get_sign_ext_msb16(src2_val);
  dst_val = ua * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpylhu)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t ua,ub;
  word_t dst_val;

  ua = get_lsb16(src1_val);
  ub = get_msb16(src2_val);
  dst_val = ua * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpysu_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa;
  word_t ub;
  word_t dst_val;

  sa = get_sign_ext_lsb16(src1_val);
  ub = get_lsb16(src2_val);
  dst_val = sa * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpysu_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long sa;
  word_t ub;
  word_t dst_val;

  sa = get_sign_ext_lsb5_quick(src1);
  ub = get_lsb16(src2_val);
  dst_val = sa * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyus)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t ua;
  long sb;
  word_t dst_val;

  ua = get_lsb16(src1_val);
  sb = get_sign_ext_lsb16(src2_val);
  dst_val = ua * sb;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,mpyu)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t ua,ub;
  word_t dst_val;

  ua = get_lsb16(src1_val);
  ub = get_lsb16(src2_val);
  dst_val = ua * ub;
  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,smpyh)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long src1_mpy,src2_mpy,dst_mpy;
  word_t dst_val;
  src1_mpy = get_sign_ext_msb16(src1_val);
  src2_mpy = get_sign_ext_msb16(src2_val);
  dst_mpy = src1_mpy * src2_mpy;
  dst_mpy <<= 1;
  if(dst_mpy != 0x80000000)
  {
    dst_val = dst_mpy;
  }
  else
  {
    dst_val = 0x7FFFFFFF;    
  }

  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,smpy)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long src1_mpy,src2_mpy,dst_mpy;
  word_t dst_val;
  src1_mpy = get_sign_ext_lsb16(src1_val);
  src2_mpy = get_sign_ext_lsb16(src2_val);
  dst_mpy = src1_mpy * src2_mpy;
  dst_mpy <<= 1;
  if(dst_mpy != 0x80000000)
  {
    dst_val = dst_mpy;
  }
  else
  {
    dst_val = 0x7FFFFFFF;    
  }

  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,smpylh)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long src1_mpy,src2_mpy,dst_mpy;
  word_t dst_val;
  src1_mpy = get_sign_ext_lsb16(src1_val);
  src2_mpy = get_sign_ext_msb16(src2_val);
  dst_mpy = src1_mpy * src2_mpy;
  dst_mpy <<= 1;
  if(dst_mpy != 0x80000000)
  {
    dst_val = dst_mpy;
  }
  else
  {
    dst_val = 0x7FFFFFFF;    
  }

  core->push_reg_delay_ch(side,dst,dst_val,1);
}

DE_FUNC(MUnit,de_32bit_mpy,smpyhl)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  long src1_mpy,src2_mpy,dst_mpy;
  word_t dst_val;
  src1_mpy = get_sign_ext_msb16(src1_val);
  src2_mpy = get_sign_ext_lsb16(src2_val);
  dst_mpy = src1_mpy * src2_mpy;
  dst_mpy <<= 1;
  if(dst_mpy != 0x80000000)
  {
    dst_val = dst_mpy;
  }
  else
  {
    dst_val = 0x7FFFFFFF;    
  }

  core->push_reg_delay_ch(side,dst,dst_val,1);
}

END_NS