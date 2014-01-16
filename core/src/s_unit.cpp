#include "core/inc/s_unit.hpp"
#include "core/inc/core.hpp"

BEGIN_NS

// 31 29 28| 27 23 | 22 18 | 17 13 | 12 | 11 6  | 5 4 3 2 1 0
// creg  z | dst   | src2  | src1  | x  | op    | 1 0 0 0 s p
// 3     1 | 5     | 5     | 5     | 1  | 6     |         1 1
void SUnit::decode_32bit_1or2_src(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,src2,src1,x,op,s,xside;
  creg_z = code >> 28;
  
  dst = get_uint(code,23,5);
  src2 = get_uint(code,18,5);
  src1 = get_uint(code,13,5);
  x = get_uint(code,12,1);
  op = get_uint(code,6,6);
  s = get_uint(code,1,1);
  xside = s;
  if(x == 1)
  {
    xside = s ^ 1;
  }

  de_func_t de_func = NULL;
  switch (op)
  {
  case 0x3F: // uint,xuint,uint  CLR | 11 1111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,clr);
    break;

  case 0x3B: // src2:xuint,uint,uint  SET | 11 1011
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,set);
    break;
        
  case 0x37: // src2:xsint,uint,sint  SHR | 11 0111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shr_f1);
    break;

  case 0x36: // src2:xsint,ucst5,sint  SHR 11 | 0110
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shr_f2);
    break;

  case 0x35: // src2:slong,uint,slong  SHR | 11 0101
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shr_f3);
    break;

  case 0x34: // src2:slong,ucst5,slong  SHR  11 | 0100
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shr_f4);
    break;

  case 0x33: // src2:xsint,uint,sint  SHL | 11 0011
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f1);
    break;

  case 0x32: // src2:xsint,ucst5,sint  SHL | 11 0010
    if(creg_z)
    {
      de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f2);
    }
    else
    {
      //src2 = (word_t)core->get_reg_addr(xside,src2);
      de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f2_nc);
    }
    break;

  case 0x31: // src2:slong,uint,slong  SHL | 11 0001
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f3);
    break;

  case 0x30: // src2:slong,ucst5,slong  SHL | 11 0000
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f4);
    break;

  case 0x2F: // src2:xsint, uint, sint  EXT | 10 1111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,ext);
    break;

  case 0x2B: // src2:xuint, uint,uint EXTU | 10 1011
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,extu);
    break;

  case 0x27: // src2:xuint,uint,uint  SHRU | 10 0111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shru_f1);
    break;

  case 0x26: // src2:xuint,ucst5,uint  SHRU | 10 0110
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shru_f2);
    break;

  case 0x25: // src2:ulong,uint,ulong SHRU | 10 0101
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shru_f3);
    break;

  case 0x24: // src2:ulong,ucst5,ulong SHRU | 10 0100
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shru_f4);
    break;

  case 0x23: // TODO SSHL
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,sshl_f1);
    break;

  case 0x22: // TODO SSHL
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,sshl_f2);
    break;

  case 0x20: // sint,xsint,sint  SADD | 10 0000
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,sadd);
    break;

  case 0x1F: // uint,xuint,uint  AND | 01 1111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,and_f1);
    break;

  case 0x1E: // scst5,xuint,uint  AND | 01 1110
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,and_f2);
    break;

  case 0x1D: // s2,xs2,bv2  CMPEQ2 | 01 1101
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,cmpeq2);
    break;

  case 0x1C: // s4,xs4    CMPEQ4
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,cmpeq4);
    break;

  case 0x1B: // uint,xuint,uint  OR | 01 1011
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,or_f1);
    break;

  case 0x1A: // scst5,xuint,uint  OR | 01 1010
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,or_f2);
    break;

  case 0x17: // sint,xsint,sint  SUB | 01 0111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,sub_f1);
    break;

  case 0x16: // scst5,xsint,sint  SUB | 01 0110
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,sub_f2);
    break;

  case 0x15: // u4,xu4,bv4  CMPGTU4 | 01 0101
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,cmpgtu4);
    break;

  case 0x14: // s2,xs2,bv2  CMPGT2 | 01 0100
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,cmpgt2);
    break;

  case 0x13: // src2:xuint,uint,ulong  SHL | 01 0011
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f5);
    break;

  case 0x12: // src2:xsint,ucst5,ulong  SHL | 01 0010
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f6);
    break;

  case 0x11: // i2,xi2,i2  SUB2 | 01 0001
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,sub2);
    break;

  case 0x10: // i2,xi2,i2  PACKLH2 | 01 0000
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,packlh2);
    break;

    // control file -> register file
  case 0x0F: // TODO MVC
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,mvc_f1);
    break;

    // register file -> control file         
  case 0x0E: // TODO MVC
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,mvc_f2);
    break;

  case 0x0B: // uint,xuint,uint XOR | 00 1011
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,xor_f1);
    break;

  case 0x0A: // scst5,xuint,uint XOR | 00 1010
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,xor_f2);
    break;

  case 0x09: // i2,xi2,i2  PACKH2 | 00 1001
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,packh2);
    break;

  case 0x08: // i2,xi2,i2  PACKHL2 | 00 1000
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,packhl2);
    break;

  case 0x07: // sint,xsint,sint  ADD | 00 0111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,add_f1);
    break;

  case 0x06: // scst5,xsint,sint  ADD | 00 0110
    {
      if(creg_z == 0)
      {
        de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,add_f2_nc);
      }
      else if(creg_z & 0x1)
      {
        de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,add_f2_z1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,add_f2_z0);
      }
    }
    break;

  case 0x01: // i2,xi2,i2  ADD2 | 00 0001
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,add2);
    break;

  default:
    core->panic("SUnit decode error.");
    break;
  }

  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(s);
  inst->set_xside(xside);
  inst->set_src1(src1);
  inst->set_src2(src2);
  inst->set_dst(dst);

  return;
}

//31 29 28 | 27 23 | 22 7  | 6 5 4 3 2 1 0
//creg  z  | dst   | cst16 | 1 0 1 0 0 s p
//3     1  | 5     | 16    |           1 1
void SUnit::decode_32bit_addk(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,cst16,side;
  word_t dst_val;
  creg_z = code >> 28;

  dst = get_uint(code,23,5);
  cst16 = get_sign_ext(code,7,16);
  side = get_uint(code,1,1);

  de_func_t de_func = DE_FUNC_ADDR(SUnit,de_32bit,addk);
  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_src1(cst16);
  inst->set_dst(dst);

}

// 31 29 28 | 27 23 | 22 16 | 15 13  | 12 11 10 9 8 7 6 5 4 3 2 1 0
// creg  z  | dst   | src1  | src2   |  0  0  0 0 1 0 1 1 0 0 0 s p
// 3     1  | 5     | 7     | 3      |                          1 1
void SUnit::decode_32bit_addkpc(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,src1,src2_nop,side;
  md_addr_t base_addr = inst->get_base_addr();
  creg_z = code >> 28;
  src2_nop = get_uint(code,13,3);
  side = get_uint(code,1,1);
  assert(side == 1); // only valid in S2

  dst = get_uint(code,23,5);
  src1 = get_sign_ext(code,16,7);
  src1 = src1 << 2;
  word_t pce1_of_inst = base_addr;
  word_t ret_addr = pce1_of_inst + src1;

  de_func_t de_func = DE_FUNC_ADDR(SUnit,de_32bit,addkpc);
  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_src1(ret_addr);
  inst->set_src2(src2_nop);
  inst->set_nop_count(src2_nop);
  inst->set_dst(dst);
}

// 31 29 28 | 27 23 | 22 18 | 17 13 | 12 | 11 10 | 9 6  | 5 4 3 2 1 0
// creg  z  | dst   |src2   |src1   | x  |  1  1 | op   | 1 1 0 0 s p
// 3     1  | 5     |5      |5      | 1  |       | 4    |         1 1
void SUnit::decode_32bit_ext_1or2_src(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,src1,src2,x,op,side;
  creg_z = code >> 28;
  dst = get_uint(code,23,5);
  src2 = get_uint(code,18,5);
  src1 = get_uint(code,13,5);
  x = get_uint(code,12,1);
  op = get_uint(code,6,4);
  side = get_uint(code,1,1);
  word_t xside = side;
  de_func_t de_func;
  if(x == 1) // cross path
  {
    xside = side ^ 1;
  }

  switch(op)
  {
  case 0x6: // uint,xuint,uint  ANDN  |  0110
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,andn);
    break;

  case 0x5: // src2:xuint,uint,uint  SUB | 0101
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,sub);
    break;

  case 0x9: // u4,xu4,u4  SHLMB | 1001
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,shlmb);
    break;

  case 0xE: // uint,xs2,s2  SHR2 | 0111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,shr2);
    break;

  case 0xA: // u4,xu4,u4  SHRMB | 1010
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,shrmb);
    break;

  case 0x8: // uint,x2,u2 SHRU2 | 1000
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,shru2);
    break;

  case 0xF: // i2,xi2,i2  PACK2 | 1111
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,pack2);
    break;

  case 0x0: // s2,xs2,s2  SADD2 | 0000
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,sadd2);
    break;

  case 0x3: // u4,xu4,u4 SADDU4 | 0011
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,saddu4);
    break;

  case 0x4: // TODO SPACKU4
    core->panic("SUnit:SPACKU4");
    break;

  case 0x2: // TODO SPACK2
    core->panic("SUnit:SPACK2");
    break;

  case 0x1: // u2,xs2,u2  SADDSU2 | 0001
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_ext_1or2_src,saddsu2);
    break;

  default:
    core->panic("SUnit:decode_32bit_ext_1or2_src");
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

// 31 29 28 | 27 7  |6 5 4 3 2 1 0
// creg z   | cst21 |0 0 1 0 0 s p
// 3    1   | 21    |          1 1
void SUnit::decode_32bit_b_disp(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,side;
  creg_z = code >> 28;
  side = get_uint(code,1,1);
  long cst21 = get_sign_ext(code,7,21);
  md_addr_t jmp_addr = (cst21 << 2) + inst->get_base_addr();

  //de_func_t de_func = DE_FUNC_ADDR(SUnit,de_32bit,b_disp);
  de_func_t de_func;
  SET_DE_FUNC_NC_Z0_Z1(creg_z,SUnit,de_32bit,b_disp);
  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_src1(jmp_addr); // save jmp_addr in src1
}

// 31 29 28|27 26 25 24 23| 22 18 |17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
// creg   z|0   0  0  0  0| src2  |0   0  0  0  0  x  0  0 1 1 0 1 1 0 0 0 s p
// 3      1|              | 5     |                1                       1 1
void SUnit::decode_32bit_b_reg(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,src2,x,xside;
  creg_z = code >> 28;
  src2 = get_uint(code,18,5);
  x = get_uint(code,12,1);
  xside = get_uint(code,1,1);
  if(x == 1)
  {
    xside = xside ^ 1;
  }

  de_func_t de_func = DE_FUNC_ADDR(SUnit,de_32bit,b_reg);
  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_xside(xside);
  inst->set_src2(src2);
}

void SUnit::decode_32bit_b_ptr(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z = code >> 28;
  word_t crlo = get_uint(code,18,3);

  de_func_t de_func = DE_FUNC_ADDR(SUnit,de_32bit,b_ptr);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_cregz(creg_z);
  inst->set_de_func(de_func);
  inst->set_src1(crlo);
}

// 31 29  28 | 27 23 | 22 13 | 12 | 11 10 9 8 7 6 5 4 3 2 1 0
// creg   z  | dst   | src   | n  |  0  0 0 0 0 0 1 0 0 0 s p
// 3      1  | 5     | 10    | 1  |                       1 1
void SUnit::decode_32bit_bdec_or_bpos(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,src,n,side;
  word_t src2_val,dst_val;
  md_addr_t base_addr = inst->get_base_addr();
  creg_z = code >> 28;
  dst = get_uint(code,23,5);
  src = get_sign_ext(code,13,10);
  n = get_uint(code,12,1);
  side = get_uint(code,1,1);
  md_addr_t jmp_addr;
  de_func_t de_func;
  if(n == 1)
  { // BDEC
    jmp_addr = (src << 2) + base_addr;
    de_func = DE_FUNC_ADDR(SUnit,de_32bit,b_dec);
    inst->set_de_func(de_func);
    inst->set_cregz(creg_z);
    if(creg_z != 0)
    {
      inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
    }
    inst->set_side(side);
    inst->set_src1(jmp_addr);
    inst->set_dst(dst);
  }
  else
  {
    core->panic("B_POS");
  }
}

void SUnit::decode_32bit_bnop_disp(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,nop,src2_val;
  md_addr_t base_addr = inst->get_base_addr();
  nop = get_uint(code,13,3);
  src2_val = get_sign_ext(code,16,12);
  creg_z = code >> 28;

  md_addr_t jmp_addr = (src2_val << 2) + base_addr;
  de_func_t de_func;
  if(creg_z == 0)
  {
    de_func = DE_FUNC_ADDR(SUnit,de_32bit,bnop_disp_nc);
  }
  else if(creg_z & 0x1)
  {
    de_func = DE_FUNC_ADDR(SUnit,de_32bit,bnop_disp_z1);
  }
  else
  {
    de_func = DE_FUNC_ADDR(SUnit,de_32bit,bnop_disp_z0);
  }
  
  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_src1(jmp_addr);
  inst->set_src2(nop);
  inst->set_nop_count(nop);
}

// 31 29 28 | 27 26 25 24 23 | 22 18  | 17 16 | 15 13 | 12 |11 10 9 8 7 6 5 4 3 2 1 0
// creg  z  | 0 0 0 0 1      |src2    | 0 0   | src1  | x  | 0  0 1 1 0 1 1 0 0 0 1 p
// 3     1  |                |5       |       | 3     | 1  |                        1
void SUnit::decode_32bit_bnop_reg(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,src2,nop,x,xside;
  word_t src2_val;
  creg_z = get_uint(code,28,4);
  src2 = get_uint(code,18,5);
  nop = get_uint(code,13,3);
  x = get_uint(code,12,1);
  xside = 1; // side == S2
  if(x == 1)
  {
    xside = 0;
  }

  de_func_t de_func = DE_FUNC_ADDR(SUnit,de_32bit,bnop_reg);
  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_xside(xside);
  inst->set_src1(nop);
  inst->set_nop_count(nop);
  inst->set_src2(src2);
}

//31 29 28 27 23  22  7  6 5 4 3 2 1 0
//creg  z   dst   cst16  h 1 0 1 0 s p
//3     1    5     16    1         1 1
void SUnit::decode_32bit_mvk_mvkh(Core *core, code_t code, Instruction *inst)
{
  word_t cst16,dst,h,side;
  word_t creg_z = code >> 28;
  dst = get_uint(code,23,5);
  h = get_uint(code,6,1);
  side = get_uint(code,1,1);
  de_func_t de_func;
  cst16 = get_sign_ext(code,7,16);
  if (h == 0)
  { // MVK
    //de_func = DE_FUNC_ADDR(SUnit,de_32bit,mvk);
    SET_DE_FUNC_NC_Z0_Z1(creg_z,SUnit,de_32bit,mvk);
  }
  else
  { // MVKH
    de_func = DE_FUNC_ADDR(SUnit,de_32bit,mvkh);
  }

  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_src1(cst16);
  inst->set_dst(dst);
}

// 31 29 28 | 27 23 | 22 18 | 17 13 | 12 11 10 9 8 7 6 5 4 3 2 1 0
// creg  z  | dst   | src2  | op    |  x  1  1 1 1 0 0 1 0 0 0 s p
// 3     1  | 5     | 5     |5      |  1                       1 1
void SUnit::decode_32bit_unary(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z = code >> 28;
  word_t dst,src2,op,x,side,xside;
  word_t dst_val,src1_val,src2_val;
  de_func_t de_func;
  dst = get_uint(code,23,5);
  src2 = get_uint(code,18,5);
  op = get_uint(code,13,5);
  x = get_uint(code,12,1);
  side = get_uint(code,1,1);
  xside = side;
  if(x == 1)
  {
    xside = side ^ 1;
  }
  switch(op)
  {
  case 0x3: //UNPKHU4
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_unary,unpkhu4);
    break;

  case 0x2: //UNPKLU4
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_unary,unpklu4);
    break;

  default:
    core->panic("SUnit:32bit_unary");
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
  inst->set_src2(src2);
  inst->set_dst(dst);
}

// 31 29 28 | 27 23 | 22 18 | 17 13 | 12 8 | 7 6 | 5 4 3 2 1 0
// creg   z | dst   | src2  | csta  | cstb | op  | 0 0 1 0 s p
// 3      1 | 5     | 5     | 5     | 5    | 2   |         1 1
void SUnit::decode_32bit_field_op(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z = code >> 28;
  word_t dst,src2,op,side;
  word_t dst_val,src2_val;
  de_func_t de_func;
  dst = get_uint(code,23,5);
  src2 = get_uint(code,18,5);
  op = get_uint(code,6,2);
  side = get_uint(code,1,1);

  switch(op)
  {
  case 0x3: // CLR
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_fop,clr);
    break;

  case 0x1: // EXT
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_fop,ext);
    break;

  case 0x0: // EXTU
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_fop,extu);
    break;

  case 0x2: // SET
    de_func = DE_FUNC_ADDR(SUnit,de_32bit_fop,set);
    break;
  }
  
  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_src1(code);
  inst->set_src2(src2);
  inst->set_dst(dst);
}

void SUnit::decode(Core* pCore, Instruction* inst)
{
  word_t type = inst->get_op_type();
  word_t code = inst->get_code();
  switch(type)
  {
// 31 29 28| 27 23 | 22 18 | 17 13 | 12 | 11 6  | 5 4 3 2 1 0
// creg  z | dst   | src2  | src1  | x  | op    | 1 0 0 0 s p
// 3     1 | 5     | 5     | 5     | 1  | 6     |         1 1
    case OP_S_UNIT_32BIT_1_OR_2_SRC: // FMT-1
      decode_32bit_1or2_src(pCore,code,inst);  
      break;

//31 29 28 | 27 23 | 22 7  | 6 5 4 3 2 1 0
//creg  z  | dst   | cst16 | 1 0 1 0 0 s p
//3     1  | 5     | 16    |           1 1
    case OP_S_UNIT_32BIT_ADDK: // FMT-2
      decode_32bit_addk(pCore,code,inst);
      break;

// 31 29 28 | 27 23 | 22 16 | 15 13  | 12 11 10 9 8 7 6 5 4 3 2 1 0
// creg  z  | dst   | src1  | src2   |  0  0  0 0 1 0 1 1 0 0 0 s p
// 3     1  | 5     | 7     | 3      |                          1 1
    case OP_S_UNIT_32BIT_ADDKPC:  // FMT-3
      decode_32bit_addkpc(pCore,code,inst);
      break;

// 31 29 28 | 27 23 | 22 18 | 17 13 | 12 | 11 10 | 9 6  | 5 4 3 2 1 0
// creg  z  | dst   |src2   |src1   | x  |  1  1 | op   | 1 1 0 0 s p
// 3     1  | 5     |5      |5      | 1  |       | 4    |         1 1
    case OP_S_UNIT_32BIT_EXT_1_OR_2_SRC: // FMT-4
      decode_32bit_ext_1or2_src(pCore,code,inst);
      break;

// 31 29 28 | 27 7  |6 5 4 3 2 1 0
// creg z   | cst21 |0 0 1 0 0 s p
// 3    1   | 21    |          1 1
    case OP_S_UNIT_32BIT_B_DISP: // FMT-5
      decode_32bit_b_disp(pCore,code,inst);
      break;

// 31 29 28|27 26 25 24 23| 22 18 |17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
// creg   z|0   0  0  0  0| src2  |0   0  0  0  0  x  0  0 1 1 0 1 1 0 0 0 s p
// 3      1|              | 5     |                1                       1 1
    case OP_S_UNIT_32BIT_B_REG: // FMT-6
      decode_32bit_b_reg(pCore,code,inst);
      break;

    case OP_S_UNIT_32BIT_B_PTR: // FMT-7
      decode_32bit_b_ptr(pCore,code,inst);
      break;

// 31 29  28 | 27 23 | 22 13 | 12 | 11 10 9 8 7 6 5 4 3 2 1 0
// creg   z  | dst   | src   | n  |  0  0 0 0 0 0 1 0 0 0 s p
// 3      1  | 5     | 10    | 1  |                       1 1
    case OP_S_UNIT_32BIT_BDEC_OR_BPOS: // FMT-8
      decode_32bit_bdec_or_bpos(pCore,code,inst);
      break;

    case OP_S_UNIT_32BIT_BNOP_DISP: // FMT-9
      decode_32bit_bnop_disp(pCore,code,inst);
      break;

// 31 29 28 | 27 26 25 24 23 | 22 18  | 17 16 | 15 13 | 12 |11 10 9 8 7 6 5 4 3 2 1 0
// creg  z  | 0 0 0 0 1      |src2    | 0 0   | src1  | x  | 0  0 1 1 0 1 1 0 0 0 1 p
// 3     1  |                |5       |       | 3     | 1  |                        1
    case OP_S_UNIT_32BIT_BNOP_REG: // FMT-10
      decode_32bit_bnop_reg(pCore,code,inst);
      break;

      //c64x+
    case OP_S_UNIT_32BIT_CALL_NON_COND_IMMED_NOP5: // FMT-11
      assert(false);
      break;

//31 29 28 27 23  22  7  6 5 4 3 2 1 0
//creg  z   dst   cst16  h 1 0 1 0 s p
//3     1    5     16    1         1 1
    case OP_S_UNIT_32BIT_MVK_MVKH: // FMT-12
      decode_32bit_mvk_mvkh(pCore,code,inst);
      break;

      //c64x+
    case OP_S_UNIT_32BIT_EXT_1_OR_2_SRC_NON_COND:
      assert(false);
      break;

// 31 29 28 | 27 23 | 22 18 | 17 13 | 12 11 10 9 8 7 6 5 4 3 2 1 0
// creg  z  | dst   | src2  | op    |  x  1  1 1 1 0 0 1 0 0 0 s p
// 3     1  | 5     | 5     |5      |  1                       1 1
    case OP_S_UNIT_32BIT_UNARY:
      decode_32bit_unary(pCore,code,inst);
      break;

// 31 29 28 | 27 23 | 22 18 | 17 13 | 12 8 | 7 6 | 5 4 3 2 1 0
// creg   z | dst   | src2  | csta  | cstb | op  | 0 0 1 0 s p
// 3      1 | 5     | 5     | 5     | 5    | 2   |         1 1
    case OP_S_UNIT_32BIT_FIELD_OP: // FMT-15
      decode_32bit_field_op(pCore,code,inst);
      break;

    default:
      assert(false);
      break;
  }

  return;
}

// uint,xuint,uint  CLR | 11 1111
DE_FUNC(SUnit,de_32bit_1or2_src,clr)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t csta,cstb;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  cstb = get_uint(src1_val,0,5); // 0~4
  csta = get_uint(src1_val,5,5); // 5~9
  dst_val = clr(src2_val,csta,cstb);

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xuint,uint,uint  SET | 11 1011
DE_FUNC(SUnit,de_32bit_1or2_src,set)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t csta,cstb;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  cstb = get_uint(src1_val,0,5); // 0~4
  csta = get_uint(src1_val,5,5); // 5~9
  dst_val = set(src2_val,csta,cstb);

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xsint,uint,sint  SHR | 11 0111
DE_FUNC(SUnit,de_32bit_1or2_src,shr_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1) & 0x1F;
  src2_val = core->reg_read(xside,src2);
  dst_val = shr(src2_val,src1_val);

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xsint,ucst5,sint  SHR 11 | 0110
DE_FUNC(SUnit,de_32bit_1or2_src,shr_f2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val,dst_val;

  src2_val = core->reg_read(xside,src2);
  dst_val = shr(src2_val,src1);

  core->push_reg_ch(side,dst,dst_val);
}

// src2:slong,uint,slong  SHR | 11 0101
DE_FUNC(SUnit,de_32bit_1or2_src,shr_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val;
  qword_t dst_qval,src2_qval;

  src1_val = core->reg_read(side,src1);
  if(src1_val > 40)
  {
    src1_val = 40;
  }
  src2_qval = core->reg_read_long(side,src2);
  dst_qval = shr_u40(src2_qval,src1_val);

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// src2:slong,ucst5,slong  SHR  11 | 0100
DE_FUNC(SUnit,de_32bit_1or2_src,shr_f4)
{
  DE_CONDITION(core,cregz);

  qword_t dst_qval,src2_qval;

  src2_qval = core->reg_read_long(side,src2);
  dst_qval = shr_u40(src2_qval,src1);

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// src2:xsint,uint,sint  SHL | 11 0011
DE_FUNC(SUnit,de_32bit_1or2_src,shl_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  //L:xxx & 0x1F will miss with 0x20
  //src1_val = core->reg_read(side,src1) & 0x1F;
  //L:xxx  (0xFFFFFFFF << 0x20) should be 0,
  //but in x86 SHL eax,0x20 leave eax unchanged.
  src1_val = core->reg_read(side,src1) & 0x3F;
  if(src1_val >= 0x20)
  {
    dst_val = 0;
  }
  else
  {
    src2_val = core->reg_read(xside,src2);
    dst_val = ((sword_t)src2_val << src1_val);
  }
  core->push_reg_ch(side,dst,dst_val);
}

// src2:xsint,ucst5,sint  SHL | 11 0010
DE_FUNC(SUnit,de_32bit_1or2_src,shl_f2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val,dst_val;

  // src1 always <= 0x1F (ucst5)
  src2_val = core->reg_read(xside,src2);
  dst_val = src2_val << src1;

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xsint,ucst5,sint  SHL | 11 0010
DE_FUNC(SUnit,de_32bit_1or2_src,shl_f2_nc)
{
  NO_CONDITION();
  word_t src2_val,dst_val;

  src2_val = core->reg_read(xside,src2);
  // src2 is physical addr of src2 register
  //src2_val = *(word_t*)src2;

  dst_val = src2_val << src1;

  core->push_reg_ch(side,dst,dst_val);
}

// src2:slong,uint,slong  SHL | 11 0001
DE_FUNC(SUnit,de_32bit_1or2_src,shl_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val;
  qword_t dst_qval,src2_qval;

  src1_val = core->reg_read(side,src1);
  if(src1_val > 40)
  {
    src1_val = 40;
  }
  src2_qval = core->reg_read_long(side,src2);
  dst_qval = src2_qval << src1_val;
  dst_qval &= 0xFFFFFFFFFF; // 40bits

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// src2:slong,ucst5,slong  SHL | 11 0000
DE_FUNC(SUnit,de_32bit_1or2_src,shl_f4)
{
  DE_CONDITION(core,cregz);

  qword_t dst_qval,src2_qval;

  src2_qval = core->reg_read_long(side,src2);
  dst_qval = src2_qval << src1;
  dst_qval &= 0xFFFFFFFFFF; // 40bits

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// src2:xsint, uint, sint  EXT | 10 1111
DE_FUNC(SUnit,de_32bit_1or2_src,ext)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t csta,cstb;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  cstb = get_uint(src1_val,0,5); // 0~4
  csta = get_uint(src1_val,5,5); // 5~9
  dst_val = ext(src2_val,csta,cstb);

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xuint, uint,uint EXTU | 10 1011
DE_FUNC(SUnit,de_32bit_1or2_src,extu)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t csta,cstb;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  cstb = get_uint(src1_val,0,5); // 0~4
  csta = get_uint(src1_val,5,5); // 5~9
  dst_val = extu(src2_val,csta,cstb);

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xuint,uint,uint  SHRU | 10 0111
DE_FUNC(SUnit,de_32bit_1or2_src,shru_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1) & 0x1F;
  src2_val = core->reg_read(xside,src2);
  dst_val = src2_val >> src1_val;

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xuint,ucst5,uint  SHRU | 10 0110
DE_FUNC(SUnit,de_32bit_1or2_src,shru_f2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val,dst_val;

  src2_val = core->reg_read(xside,src2);
  dst_val = src2_val >> src1;

  core->push_reg_ch(side,dst,dst_val);
}

// src2:ulong,uint,ulong SHRU | 10 0101
DE_FUNC(SUnit,de_32bit_1or2_src,shru_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val;
  qword_t dst_qval,src2_qval;

  src1_val = core->reg_read(side,src1);
  if(src1_val > 40)
  {
    src1_val = 40;
  }
  src2_qval = core->reg_read_long(side,src2);
  src2_qval &= 0xFFFFFFFFFF; // 40bits
  dst_qval = src2_qval >> src1_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// src2:ulong,ucst5,ulong SHRU | 10 0100
DE_FUNC(SUnit,de_32bit_1or2_src,shru_f4)
{
  DE_CONDITION(core,cregz);

  qword_t dst_qval,src2_qval;

  src2_qval = core->reg_read_long(side,src2);
  src2_qval &= 0xFFFFFFFFFF; // 40bits
  dst_qval = src2_qval >> src1;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// src2:xsint,uint,sint  SSHL
DE_FUNC(SUnit,de_32bit_1or2_src,sshl_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1) & 0x3F; // 6 LSB
  src2_val = core->reg_read(xside,src2);
  dst_val = sshl(src1_val,src2_val);

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xsint,ucst5,sint  SSHL
DE_FUNC(SUnit,de_32bit_1or2_src,sshl_f2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val,dst_val;

  src2_val = core->reg_read(xside,src2);
  dst_val = sshl(src1,src2_val);

  core->push_reg_ch(side,dst,dst_val);
}

// sint,xsint,sint  SADD | 10 0000
DE_FUNC(SUnit,de_32bit_1or2_src,sadd)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = sadd(src1_val,src2_val);

  core->push_reg_ch(side,dst,dst_val);
}

// uint,xuint,uint  AND | 01 1111
DE_FUNC(SUnit,de_32bit_1or2_src,and_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = src1_val & src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

// scst5,xuint,uint  AND | 01 1110
DE_FUNC(SUnit,de_32bit_1or2_src,and_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = get_sign_ext_lsb5_quick(src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = src1_val & src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

// s2,xs2,bv2  CMPEQ2 | 01 1101
DE_FUNC(SUnit,de_32bit_1or2_src,cmpeq2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a_hi,a_lo,b_hi,b_lo;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_val = 0;
  if(a_lo == b_lo)
  {
    dst_val |= 0x1;
  }
  if(a_hi == b_hi)
  {
    dst_val |= 0x2;
  }  

  core->push_reg_ch(side,dst,dst_val);
}

// s4,xs4    CMPEQ4
DE_FUNC(SUnit,de_32bit_1or2_src,cmpeq4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a3,a2,a1,a0,b3,b2,b1,b0;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a3 = get_sign_ext(src1_val,24,8);
  a2 = get_sign_ext(src1_val,16,8);
  a1 = get_sign_ext(src1_val,8,8);
  a0 = get_sign_ext(src1_val,0,8);
  b3 = get_sign_ext(src2_val,24,8);
  b2 = get_sign_ext(src2_val,16,8);
  b1 = get_sign_ext(src2_val,8,8);
  b0 = get_sign_ext(src2_val,0,8);

  dst_val = 0;
  if(a0 == b0)
  {
    dst_val |= 0x1;
  }
  if(a1 == b1)
  {
    dst_val |= 0x2;
  }
  if(a2 == b2)
  {
    dst_val |= 0x4;
  }
  if(a3 == b3)
  {
    dst_val |= 0x8;
  }
  core->push_reg_ch(side,dst,dst_val);
}

// uint,xuint,uint  OR | 01 1011
DE_FUNC(SUnit,de_32bit_1or2_src,or_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = src1_val | src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

// scst5,xuint,uint  OR | 01 1010
DE_FUNC(SUnit,de_32bit_1or2_src,or_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = get_sign_ext_lsb5_quick(src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = src1_val | src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

// sint,xsint,sint  SUB | 01 0111
DE_FUNC(SUnit,de_32bit_1or2_src,sub_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = (long)src1_val - (long)src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

// scst5,xsint,sint  SUB | 01 0110
DE_FUNC(SUnit,de_32bit_1or2_src,sub_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = get_sign_ext_lsb5_quick(src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = (long)src1_val - (long)src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

// u4,xu4,bv4  CMPGTU4 | 01 0101
DE_FUNC(SUnit,de_32bit_1or2_src,cmpgtu4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a3,a2,a1,a0,b3,b2,b1,b0;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a3 = get_sign_ext(src1_val,24,8);
  a2 = get_sign_ext(src1_val,16,8);
  a1 = get_sign_ext(src1_val,8,8);
  a0 = get_sign_ext(src1_val,0,8);
  b3 = get_sign_ext(src2_val,24,8);
  b2 = get_sign_ext(src2_val,16,8);
  b1 = get_sign_ext(src2_val,8,8);
  b0 = get_sign_ext(src2_val,0,8);

  dst_val = 0;
  if(a0 > b0)
  {
    dst_val |= 0x1;
  }
  if(a1 > b1)
  {
    dst_val |= 0x2;
  }
  if(a2 > b2)
  {
    dst_val |= 0x4;
  }
  if(a3 > b3)
  {
    dst_val |= 0x8;
  }
  core->push_reg_ch(side,dst,dst_val);
}

// s2,xs2,bv2  CMPGT2 | 01 0100
DE_FUNC(SUnit,de_32bit_1or2_src,cmpgt2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a_hi,a_lo,b_hi,b_lo;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_val = 0;
  if((shalf_t)a_lo > (shalf_t)b_lo)
  {
    dst_val |= 0x1;
  }
  if((shalf_t)a_hi > (shalf_t)b_hi)
  {
    dst_val |= 0x2;
  }

  core->push_reg_ch(side,dst,dst_val);
}

// src2:xuint,uint,ulong  SHL | 01 0011
DE_FUNC(SUnit,de_32bit_1or2_src,shl_f5)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val;
  qword_t dst_qval;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  if(src1_val > 40)
  {
    src1_val = 40;
  }
  dst_qval = (qword_t)src2_val << src1_val;
  dst_qval &= 0xFFFFFFFFFF;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// src2:xsint,ucst5,ulong  SHL | 01 0010
DE_FUNC(SUnit,de_32bit_1or2_src,shl_f6)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val;
  qword_t dst_qval;

  src2_val = core->reg_read(xside,src2);
  dst_qval = (qword_t)src2_val << src1;
  dst_qval &= 0xFFFFFFFFFF;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// i2,xi2,i2  SUB2 | 01 0001
DE_FUNC(SUnit,de_32bit_1or2_src,sub2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a_hi,a_lo,b_hi,b_lo,dst_hi,dst_lo;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_hi = (shalf_t)a_hi - (shalf_t)b_hi;
  dst_lo = (shalf_t)a_lo - (shalf_t)b_lo;
  dst_hi &= 0xFFFF;
  dst_lo &= 0xFFFF;
  dst_val = (dst_hi << 16) | dst_lo;

  core->push_reg_ch(side,dst,dst_val);
}

// i2,xi2,i2  PACKLH2 | 01 0000
DE_FUNC(SUnit,de_32bit_1or2_src,packlh2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a_lo,b_hi;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a_lo = get_lsb16(src1_val);
  b_hi = get_msb16(src2_val);
  dst_val = (a_lo << 16) | b_hi;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_1or2_src,mvc_f1)
{
  DE_CONDITION(core,cregz);

  word_t dst_val = core->read_ctrl_reg(src2);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_1or2_src,mvc_f2)
{
  DE_CONDITION(core,cregz);

  word_t dst_val = core->reg_read(xside,src2);

  //core->push_reg_ch(2,dst,dst_val); // change ctl register
  core->write_ctrl_reg(dst,dst_val);
}

// uint,xuint,uint XOR | 00 1011
DE_FUNC(SUnit,de_32bit_1or2_src,xor_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = src1_val ^ src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// scst5,xuint,uint XOR | 00 1010
DE_FUNC(SUnit,de_32bit_1or2_src,xor_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = get_sign_ext_lsb5_quick(src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = src1_val ^ src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// i2,xi2,i2  PACKH2 | 00 1001
DE_FUNC(SUnit,de_32bit_1or2_src,packh2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a_hi,b_hi;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a_hi = get_msb16(src1_val);
  b_hi = get_msb16(src2_val);
  dst_val = (a_hi << 16) | b_hi;
  core->push_reg_ch(side,dst,dst_val);
}

// i2,xi2,i2  PACKHL2 | 00 1000
DE_FUNC(SUnit,de_32bit_1or2_src,packhl2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a_hi,b_lo;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a_hi = get_msb16(src1_val);
  b_lo = get_lsb16(src2_val);
  dst_val = (a_hi << 16) | b_lo;
  core->push_reg_ch(side,dst,dst_val);
}

// sint,xsint,sint  ADD | 00 0111
DE_FUNC(SUnit,de_32bit_1or2_src,add_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;

  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = (long)src1_val + (long)src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// scst5,xsint,sint  ADD | 00 0110
DE_FUNC(SUnit,de_32bit_1or2_src,add_f2_nc)
{
  NO_CONDITION();
  word_t src1_val,src2_val,dst_val;

  src1_val = get_sign_ext_lsb5_quick(src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = (long)src1_val + (long)src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_1or2_src,add_f2_z0)
{
  DE_CONDITION_Z0(core);

  word_t src1_val,src2_val,dst_val;

  src1_val = get_sign_ext_lsb5_quick(src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = (long)src1_val + (long)src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_1or2_src,add_f2_z1)
{
  DE_CONDITION_Z1(core);

  word_t src1_val,src2_val,dst_val;

  src1_val = get_sign_ext_lsb5_quick(src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = (long)src1_val + (long)src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_1or2_src,add2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val,src2_val,dst_val;
  word_t a_hi,a_lo,b_hi,b_lo,dst_hi,dst_lo;

  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_hi = (shalf_t)a_hi + (shalf_t)b_hi;
  dst_lo = (shalf_t)a_lo + (shalf_t)b_lo;
  dst_val = ((dst_hi & 0xFFFF) << 16) | (dst_lo & 0xFFFF);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit,addk)
{
  DE_CONDITION(core,cregz);
  word_t cst16,dst_val;

  cst16 = src1;
  dst_val = core->reg_read(side,dst);
  dst_val = (long)dst_val + (long)cst16;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit,addkpc)
{
  core->set_nop_remains(inst->get_src2());
  DE_CONDITION(core,cregz);
  const word_t ret_addr = src1;
  core->push_reg_ch(side,dst,ret_addr);
}

DE_FUNC(SUnit,de_32bit,b_disp_nc)
{
  DE_CONDITION_BRANCH_NC(core,cregz);
  core->add_jmp_req(src1);
}

DE_FUNC(SUnit,de_32bit,b_disp_z0)
{
  DE_CONDITION_BRANCH_Z0(core,cregz);
  core->add_jmp_req(src1);
}

DE_FUNC(SUnit,de_32bit,b_disp_z1)
{
  DE_CONDITION_BRANCH_Z1(core,cregz);
  core->add_jmp_req(src1);
}

DE_FUNC(SUnit,de_32bit,b_reg)
{
  DE_CONDITION_BRANCH(core,cregz);
  core->add_jmp_req(core->reg_read(xside,src2));
}

DE_FUNC(SUnit,de_32bit,b_ptr)
{
  //DE_CONDITION_BRANCH(core,cregz);
  Core::dummy_or_real_jmp_delay_cycles = 6;
  if(not_cond(core,inst)) 
  {
    return;
  }
  const word_t src1 = inst->get_src1();
  const word_t src2 = inst->get_src2();
  const word_t dst = inst->get_dst();
  const word_t side = inst->get_side();
  const word_t xside = inst->get_xside();
  word_t crlo = src1; // crlo saved in src1
  md_addr_t ret_addr = core->read_ctrl_reg(crlo); // IRP
  core->add_jmp_req(ret_addr);

  word_t csr = core->read_ctrl_reg(Core::CTL_CSR);
  word_t pgie = (csr & 0x2) >> 1;
  csr &= 0xFFFFFFFE; 
  csr |= pgie;
  core->write_ctrl_reg(Core::CTL_CSR,csr);

  if(crlo != Core::CTL_IRP)
  {
    Core::get()->get_ofs() << "<WARN> B_PTR|" << "crlo:" <<
      to_hex_str(crlo) << "RET ADDR:" << to_hex_str(ret_addr) << "\n";
  }
}

DE_FUNC(SUnit,de_32bit,b_dec)
{
  DE_CONDITION_BRANCH(core,cregz);
  word_t dst_val = core->reg_read(side,dst);
  if((long)dst_val > 0)
  {
    dst_val = (long)dst_val - 1;
    core->push_reg_ch(side,dst,dst_val);
    core->add_jmp_req(src1);
  }
}

DE_FUNC(SUnit,de_32bit,bnop_disp_nc)
{
  core->set_nop_remains(inst->get_src2());
  DE_CONDITION_BRANCH_NC(core,cregz);
  core->add_jmp_req(src1);
}

DE_FUNC(SUnit,de_32bit,bnop_disp_z0)
{
  core->set_nop_remains(inst->get_src2());
  DE_CONDITION_BRANCH_Z0(core,cregz);
  core->add_jmp_req(src1);
}

DE_FUNC(SUnit,de_32bit,bnop_disp_z1)
{
  core->set_nop_remains(inst->get_src2());
  DE_CONDITION_BRANCH_Z1(core,cregz);
  core->add_jmp_req(src1);
}

DE_FUNC(SUnit,de_32bit,bnop_reg)
{
  core->set_nop_remains(inst->get_src1()); // nop saved in src1
  DE_CONDITION_BRANCH(core,cregz);
  core->add_jmp_req(core->reg_read(xside,src2));
}

DE_FUNC(SUnit,de_32bit,mvk_nc)
{
  NO_CONDITION(core,cregz);
  core->push_reg_ch(side,dst,src1);
}

DE_FUNC(SUnit,de_32bit,mvk_z0)
{
  DE_CONDITION_Z0(core);
  core->push_reg_ch(side,dst,src1);
}

DE_FUNC(SUnit,de_32bit,mvk_z1)
{
  DE_CONDITION_Z1(core);
  core->push_reg_ch(side,dst,src1);
}

DE_FUNC(SUnit,de_32bit,mvkh)
{
  DE_CONDITION(core,cregz);
  word_t reg_val,dst_val;
  reg_val = core->reg_read(side,dst);
  dst_val = (src1 << 16) | (reg_val & 0xFFFF);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_unary,unpkhu4)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src2_val;
  src2_val = core->reg_read(xside,src2);
  dst_val = ((src2_val & 0xFF000000) >> 8) |
    ((src2_val & 0x00FF0000) >> 16);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_unary,unpklu4)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src2_val;
  src2_val = core->reg_read(xside,src2);
  dst_val = ((src2_val & 0x0000FF00) << 8) | 
    (src2_val & 0xFF);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_fop,clr)
{ // save code in src1
  DE_CONDITION(core,cregz);
  word_t dst_val,src2_val,csta,cstb;
  src2_val = core->reg_read(side,src2);
  csta = get_uint(src1,13,5);
  cstb = get_uint(src1,8,5);
  dst_val = clr(src2_val,csta,cstb);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_fop,ext)
{ // save code in src1
  DE_CONDITION(core,cregz);
  word_t dst_val,src2_val,csta,cstb;
  src2_val = core->reg_read(side,src2);
  csta = get_uint(src1,13,5);
  cstb = get_uint(src1,8,5);
  dst_val = ext(src2_val,csta,cstb);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_fop,extu)
{ // save code in src1
  DE_CONDITION(core,cregz);
  word_t dst_val,src2_val,csta,cstb;
  src2_val = core->reg_read(side,src2);
  csta = get_uint(src1,13,5);
  cstb = get_uint(src1,8,5);
  dst_val = extu(src2_val,csta,cstb);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_fop,set)
{ // save code in src1
  DE_CONDITION(core,cregz);
  word_t dst_val,src2_val,csta,cstb;
  src2_val = core->reg_read(side,src2);
  csta = get_uint(src1,13,5);
  cstb = get_uint(src1,8,5);
  dst_val = set(src2_val,csta,cstb);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,andn)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = src1_val & (~src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,sub)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  dst_val = src2_val - src1_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,shlmb)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  src2_val = src2_val << 8;
  src1_val = src1_val >> 24;
  dst_val = src2_val | src1_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,shr2)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  word_t b_hi,b_lo;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);

  src1_val = get_uint(src1_val,0,5);
  b_hi = get_uint(src2_val,16,16);
  b_lo = get_uint(src2_val,0,16);
  b_hi >>= src1_val;
  b_lo >>= src1_val;
  assert(src1_val <= 16);
  b_hi = get_sign_ext(b_hi,0,16 - src1_val) & 0xFFFF;
  b_lo = get_sign_ext(b_lo,0,16 - src1_val) & 0xFFFF;
  dst_val = (b_hi << 16) | b_lo;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,shrmb)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  src1_val = src1_val << 24;
  src2_val = src2_val >> 8;
  dst_val = src1_val | src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,shru2)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  word_t b_hi,b_lo;

  src1_val = get_uint(src1_val,0,5);
  b_hi = get_uint(src2_val,16,16);
  b_lo = get_uint(src2_val,0,16);
  b_hi >>= src1_val;
  b_lo >>= src1_val;
  dst_val = (b_hi << 16) | b_lo;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,pack2)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  word_t a_lo,b_lo;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a_lo = get_sign_ext_lsb16(src1_val) & 0xFFFF;
  b_lo = get_sign_ext_lsb16(src2_val) & 0xFFFF;
  dst_val = (a_lo << 16) | b_lo;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,sadd2)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  word_t a_lo,b_lo,a_hi,b_hi,dst_hi,dst_lo;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);
  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_hi = sat16((shalf_t)a_hi + (shalf_t)b_hi);
  dst_lo = sat16((shalf_t)a_lo + (shalf_t)b_lo);
  dst_val = (dst_hi << 16) | dst_lo;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,saddu4)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  word_t a3,a2,a1,a0;
  word_t b3,b2,b1,b0;
  word_t dst3,dst2,dst1,dst0;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);

  a3 = get_uint(src1_val,24,8);
  a2 = get_uint(src1_val,16,8);
  a1 = get_uint(src1_val,8,8);
  a0 = get_uint(src1_val,0,8);
  b3 = get_uint(src2_val,24,8);
  b2 = get_uint(src2_val,16,8);
  b1 = get_uint(src2_val,8,8);
  b0 = get_uint(src2_val,0,8);
  dst3 = satu8(a3+b3);
  dst2 = satu8(a2+b2);
  dst1 = satu8(a1+b1);
  dst0 = satu8(a0+b0);

  dst_val = (dst3 << 24) | (dst2 << 16) |
    (dst1 << 8) | dst0;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(SUnit,de_32bit_ext_1or2_src,saddsu2)
{
  DE_CONDITION(core,cregz);
  word_t dst_val,src1_val,src2_val;
  word_t a_lo,b_lo,a_hi,b_hi;
  src1_val = core->reg_read(side,src1);
  src2_val = core->reg_read(xside,src2);

  long d_hi,d_lo;
  a_hi = get_uint(src1_val,16,16);
  a_lo = get_uint(src1_val,0,16);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  d_hi = (long)a_hi + (long)b_hi;
  d_lo = (long)a_lo + (long)b_lo;
  if(d_hi > 0xFFFF)
    d_hi = 0xFFFF;
  if(d_hi < 0)
    d_hi = 0;
  if(d_lo > 0xFFFF)
    d_lo = 0xFFFF;
  if(d_lo < 0)
    d_lo = 0;
  d_hi &= 0xFFFF;
  d_lo &= 0xFFFF;
  dst_val = (d_hi << 16) | d_lo;

  core->push_reg_ch(side,dst,dst_val);
}


END_NS