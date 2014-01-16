
#include "core/inc/d_unit.hpp"
#include "core/inc/core.hpp"


BEGIN_NS

#define LOAD_DELAY_CYCLES 4

//    FMT C-1. 1 or 2 Sources Instruction Format
//    31 29 | 28 | 27 23 | 22 18 | 17 13 |12 7 |6|5|4|3|2|1|0
//     creg | z  |  dst  |  src2 |  src1 | op  |1|0|0|0|0|s|p
//      3   | 1  |   5   |   5   |   5   | 6   |         |1|1
void DUnit::decode_32bit_1or2_src2(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,src2,src1,op,side;
  creg_z = code >> 28;
  dst = get_uint(code,23,5);
  src2 = get_uint(code,18,5);
  src1 = get_uint(code,13,5);
  op = get_uint(code,7,6);
  side = get_uint(code,1,1);
  
  de_func_t de_func;

  switch(op)
  {
  case 0x0: // 00 0000 MVK
    {
      src1 = get_sign_ext_lsb5_quick(src1);
      de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,mvk);
    }
    break;

  case 0x10: // 01 0000   ADD
    //op_name = "ADD_SINT_SINT_SINT";
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,add_f1);
    break;

  case 0x12: // 01 0010   ADD
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,add_f2);
    break;

  case 0x11:
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,sub_f1);
    break;

  case 0x13: // 01 0011   SUB
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,sub_f2);
    break;

  case 0x30:// 11 0000   ADDAB   TODO:circular mode
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,addab_f1);
    break;

  case 0x32: // 11 0010   ADDAB
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,addab_f2);
    break;

  case 0x31: // 11 0001   SUBAB
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,subab_f1);
    break;

  case 0x33: // 11 0011   SUBAB
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,subab_f2);
    break;

  case 0x34:// 11 0100   ADDAH   TODO:circular mode
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,addah_f1);
    break;

  case 0x36: // 11 0110   ADDAH
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,addah_f2);
    break;

  case 0x35: // 11 0101   SUBAH
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,subah_f1);
    break;

  case 0x37:// 11 0111   SUBAH
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,subah_f2);
    break;

  case 0x38: // 11 1000   ADDAW   TODO:circular mode
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,addaw_f1);
    break;

  case 0x3A: // 11 1010   ADDAW
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,addaw_f2);
    break;

  case 0x39:// 11 1001   SUBAW
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,subaw_f1);
    break;

  case 0x3B: // 11 1011   SUBAW
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,subaw_f2);
    break;

  case 0x3C:// 11 1100   ADDAD   TODO:circular mode
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,addad_f1);
    break;

  case 0x3D: // 11 1101   ADDAD
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_1or2_src,addad_f2);
    break;

  default:
    core->panic("DUnit::decode_32bit_1or2_src");
    break;
  }

  inst->set_de_func(de_func);
  inst->set_side(side);
  inst->set_src1(src1);
  inst->set_src2(src2);
  inst->set_dst(dst);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
}

//    FMT C-2. Extended .D Unit 1 or 2 Sources Instruction Format
//    31 29 | 28 | 27 23 | 22 18 | 17 13 |12|11|10| 9 6 |5|4|3|2|1|0
//     creg | z  |  dst  |  src2 |  src1 |x |1 |0 | op  |1|1|0|0|s|p
//      3   | 1  |   5   |   5   |   5   |1 |     |  4  |       |1|1
void DUnit::decode_32bit_ext_1or2_src2(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,src2,src1,x,op,side,xside;
  de_func_t de_func;
  creg_z = code >> 28;
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }

  dst = get_uint(code,23,5);
  inst->set_dst(dst);
  src2 = get_uint(code,18,5);
  inst->set_src2(src2);
  src1 = get_uint(code,13,5);
  inst->set_src1(src1);
  x = get_uint(code,12,1);
  op = get_uint(code,6,4);
  side = get_uint(code,1,1);
  inst->set_side(side);
  xside = (x == 1) ? (side ^ 1) : side;
  inst->set_xside(xside);

  switch(op)
  {
  case 0x0: // 0000 andn
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,andn);
    break;

  case 0x2: // 0010 or_f1
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,or_f1);
    break;

  case 0x3: // 0011 or_f2
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,or_f2);
    break;

  case 0x4: // 0100 add2
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,add2);
    break;

  case 0x5: // 0101 sub2
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,sub2);
    break;

  case 0x6: // 0110 and_f1
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,and_f1);
    break;

  case 0x7: // 0111 and_f2
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,and_f2);
    break;

  case 0xA: // 1010 add_f1
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,add_f1);
    break;

  case 0xB: // 1011 add_f2
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,add_f2);
    break;

  case 0xC: // 1100 SUB
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,sub);
    break;

  case 0xE: // XOR uint,xuint,uint
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,xor_f1);
    break;

  case 0xF: // 1110 // XOR scst5, xuint,uint
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ext_1or2_src,xor_f2);
    break;

  default:
    assert(false);
    break;
  }
  inst->set_de_func(de_func);

}

//    FMT C-5. Load/Store Basic Operations  (and C-7 C-8)
//    31 29 | 28 | 27 23 | 22 18 |17    13 |12  9 |8|7| 6 4 |3|2|1|0
//     creg | z  |src/dst| baseR | offsetR | mode |r|y| op  |0|1|s|p
//      3   | 1  |   5   |   5   |  5      |  4   |   |  3  |   |1|1
/*  mode Field   Syntax      Modification Performed   hex value
    0 0 0 0   *-R[ucst5]     Negative offset            0x0
    0 0 0 1   *+R[ucst5]     Positive offset            0x1
    0 1 0 0   *-R[offsetR]   Negative offset            0x4
    0 1 0 1   *+R[offsetR]   Positive offset            0x5
    1 0 0 0   *--R[ucst5]    Predecrement               0x8
    1 0 0 1   *++R[ucst5]    Preincrement               0x9
    1 0 1 0   *R--[ucst5]    Postdecrement              0xA
    1 0 1 1   *R++[ucst5]    Postincrement              0xB
    1 1 0 0   *--R[offsetR]  Predecrement               0xC
    1 1 0 1   *++R[offsetR]  Preincrement               0xD
    1 1 1 0   *R--[offsetR]  Postdecrement              0xE
    1 1 1 1   *R++[offsetR]  Postincrement              0xF
    3 2 1 0   (bit pos)  
*/
/*
void DUnit::decode_32bit_ld_st_basic(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,src_or_dst,baseR,offsetR,mode,bit8,y,op,side;
  word_t src_24,sc; // for STNDW/LDNDW

  creg_z = get_uint(code,28,4);
  bool condition = cond(core,creg_z);
  if (!condition)
  {
    return;
  }
  word_t stw_val,ld_result,base_addr,new_base_addr,mem_addr;
  word_t offset_factor;

  src_24 = get_uint(code,24,4) << 1; // xxx ... TI not documented ...
  sc = get_uint(code,23,1);
  src_or_dst = get_uint(code,23,5);
  baseR = get_uint(code,18,5);
  offsetR = get_uint(code,13,5);
  mode = get_uint(code,9,4);
  y = get_uint(code,7,1);
  op = get_uint(code,4,3);
  side = get_uint(code,1,1);
  stw_val = core->reg_read(side,src_or_dst);
  base_addr = core->reg_read(y,baseR);//cross path
  new_base_addr = base_addr;
  mem_addr = base_addr;
  offset_factor = 4;
  bit8 = get_uint(code,8,1);

  bool is_ld = false;
  bool is_st = false;
  bool is_dw_ld = false;
  bool is_st_ld_ndw_fmt = false;
  qword_t qval;

  stw_req_t stw_req;
  word_t offset;

  if (bit_test(mode,2))
  { // register offset
    offset = core->reg_read(y,offsetR);
  }
  else
  {   // ucst5 offset
    offset = offsetR;
  }

  // 1st pass
  switch(op)
  {
  case 0x0: // 000 LDHU
    offset_factor = 2;
    is_ld = true;
    //op_name = "LDHU";
    break;

  case 0x1: // 001 LDBU
    offset_factor = 1;
    is_ld = true;
    //op_name = "LDBU";
    break;

  case 0x2:
    if(bit8 == 0)
    {// 010 LDB
      offset_factor = 1;
      is_ld = true;
    }
    else
    { // 1 + 010 LDNDW
      offset_factor = (sc == 1) ? 8 : 1; // xxx  use scale mode?
      is_dw_ld = true;
      is_st_ld_ndw_fmt = true;
    }
    break;

  case 0x3:
    if(bit8 == 0)
    { // 011 STB
      offset_factor = 1;
      is_st = true;
      //op_name = "STB";
    }
    if(bit8 == 1)
    { // 1 + 011  LDNW
      //offset_factor = 4; // default
      is_ld = true;
      //op_name = "LDNW";
    }
    break;

  case 0x4:
    if(bit8 == 0)
    { // 100 LDH
      offset_factor = 2;
      is_ld = true;
      //op_name = "LDH";
    }
    else
    { // 1 + 100 STDW
      offset_factor = 8;
      is_st = true;
      //op_name = "STDW";
    }
    break;

  case 0x5:
    if(bit8 == 0)
    { // 101 STH
      offset_factor = 2;
      is_st = true;
      //op_name = "STH";
    }
    else
    { // 1 + 101  STNW
      //offset_factor = 4; // default
      is_st = true;
      //op_name = "STNW";
    }
    break;

  case 0x6:
    if(bit8 == 0)
    { // 110 LDW
      //offset_factor = 4; // default
      is_ld = true;
      //op_name = "LDW";
    }
    else
    { // 1 + 110 LDDW
      offset_factor = 8;
      is_dw_ld = true;
      //op_name = "LDDW";
    }
    break;

  case 0x7:
    if(bit8 == 0)
    { // 111 STW
      //offset_factor = 4; // default
      is_st = true;
      //op_name = "STW";
    }
    else
    { // 1 + 111 STNDW
      offset_factor = (sc == 1) ? 8 : 1; // xxx  use scale mode?
      is_st = true;
      is_st_ld_ndw_fmt = true;
      //op_name = "STNDW";
    }
    break;

  default:
    assert(false);
    break;
  }

  switch(mode)
  {
  case 0x8:
  case 0xC:// --R
    new_base_addr = base_addr - offset_factor * offset;
    mem_addr = new_base_addr;
    break;

  case 0x9:
  case 0xD: // ++R
    new_base_addr = base_addr + offset_factor * offset;
    mem_addr = new_base_addr;
    break;

  case 0x0:
  case 0x4: // -R
    mem_addr = base_addr - offset_factor * offset;
    break;

  case 0x1:
  case 0x5: // +R
    mem_addr = base_addr + offset_factor * offset;
    break;

  case 0xA:
  case 0xE: // R--
    new_base_addr = base_addr - offset_factor * offset;
    break;

  case 0xB:
  case 0xF: // R++
    new_base_addr = base_addr + offset_factor * offset;
    break;

  default:
    assert(false);
    break;
  }
 
  // 2nd pass
  switch(op)
  {
  case 0x0: // 000 LDHU
    ld_result = core->get_l2()->mem_read_half(mem_addr);
    break;

  case 0x1: // 001 LDBU
    ld_result = core->get_l2()->mem_read_byte(mem_addr);
    break;

  case 0x2:
    if(bit8 == 0)
    {// 010 LDB
      ld_result = core->get_l2()->mem_read_byte(mem_addr);
      ld_result = get_sign_ext(ld_result,0,8);
    }
    else
    { // 1 + 010 LDNDW
      qval = core->get_l2()->mem_read_qword(mem_addr);  
    }
    break;

  case 0x3:
    if(bit8 == 0)
    { // 011 STB
      stw_val = get_uint(stw_val,0,8);
      stw_req.type = TYPE_U8;
    }
    if(bit8 == 1)
    { // 1 + 011  LDNW
      ld_result = core->get_l2()->mem_read_word(mem_addr); 
    }
    break;

  case 0x4:
    if(bit8 == 0)
    { // 100 LDH
      ld_result = core->get_l2()->mem_read_half(mem_addr);
      ld_result = get_sign_ext(ld_result,0,16);
    }
    else
    { // 1 + 100 STDW
      if(is_reg_even(src_or_dst))
      {
        qval = core->reg_read(side,src_or_dst + 1);
        qval = (qval << 32) | stw_val;
      }
      else
      {
        qval = core->reg_read(side,src_or_dst - 1); // reg_even
        qval = ((qword_t)stw_val << 32) | qval;
      }

      stw_req.type = TYPE_U64;
      stw_req.qval = qval;
    }
    break;

  case 0x5:
    if(bit8 == 0)
    { // 101 STH
      stw_val = get_uint(stw_val,0,16);
      stw_req.type = TYPE_U16;
    }
    else
    { // 1 + 101  STNW
      stw_req.type = TYPE_U32;
    }
    break;

  case 0x6:
    if(bit8 == 0)
    { // 110 LDW
      ld_result = core->get_l2()->mem_read_word(mem_addr);
    }
    else
    { // 1 + 110 LDDW
      qval = core->get_l2()->mem_read_qword(mem_addr);
    }
    break;

  case 0x7:
    if(bit8 == 0)
    { // 111 STW
      stw_req.type = TYPE_U32;
    }
    else
    { // 1 + 111 STNDW

      stw_val = core->reg_read(side,src_24); // xxx use src_24
      if(is_reg_even(src_24)) 
      {
        qval = core->reg_read(side,src_24 + 1);
        qval = (qval << 32) | stw_val;
      }
      else
      {
        qval = core->reg_read(side,src_24 - 1); // reg_even
        qval = ((qword_t)stw_val << 32) | qval;
      }
      stw_req.type = TYPE_U64;
      stw_req.qval = qval;
    }
    break;

  default:
    assert(false);
    break;
  }

  // update baseR
  if (new_base_addr != base_addr)
  {
    core->push_reg_ch(y,baseR,new_base_addr);
  }

  if (is_ld)
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,ld_result);
  }

  //FIXME diff from S or L unit?
  if (is_dw_ld)
  {
    if(is_st_ld_ndw_fmt)
    {
      src_or_dst = src_24;
    }

    if(is_reg_even(src_or_dst))
    {
      core->push_reg_delay_ch_4c_delay(side,src_or_dst,qval & 0xFFFFFFFF);
      core->push_reg_delay_ch_4c_delay(side,src_or_dst+1,(qval >> 32) & 0xFFFFFFFF);
    }
    else
    {
      core->push_reg_delay_ch_4c_delay(side,src_or_dst,(qval >> 32) & 0xFFFFFFFF);
    }
  }

  if (is_st)
  {
    stw_req.addr = mem_addr;
    stw_req.val = stw_val;
    //core->_stw_change_req_list.push_back(stw_req);
    core->push_stw_req(stw_req);
  }
}
*/

void DUnit::decode_32bit_ld_st_basic2(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z = code >> 28;
  word_t src_or_dst;
  de_func_t de_func;

  const word_t mode = get_uint(code,9,4);
  const bool is_register_offset = bit_test(mode,2);
  const word_t op = get_uint(code,4,3);
  const word_t bit8 = get_uint(code,8,1);
  const word_t src1 = get_uint(code,18,5); // baseR
  const word_t src2 = get_uint(code,13,5); // offsetR
  const word_t side = get_uint(code,1,1);
  const word_t y = get_uint(code,7,1); // saved in xside
  src_or_dst = get_uint(code,23,5); // dst

  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_side(side);
  inst->set_xside(y);
  inst->set_src1(src1);
  inst->set_src2(src2);

  switch(op)
  {
  case 0x0: // 000 LDHU
    if(is_register_offset)
    {
      de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldhu_f1);
    }
    else
    {
      de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldhu_f2);
    }
    break;

  case 0x1: // 001 LDBU
    if(is_register_offset)
    {
      de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldbu_f1);
    }
    else
    {
      de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldbu_f2);
    }
    break;

  case 0x2:
    if(bit8 == 0)
    {// 010 LDB
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldb_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldb_f2);
      }
    }
    else
    { // 1 + 010 LDNDW
      //word_t sc = get_uint(code,23,1);
      word_t src_24 = get_uint(code,24,4) << 1;
      src_or_dst = src_24;
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldndw_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldndw_f2);
      }
    }
    break;

  case 0x3:
    if(bit8 == 0)
    { // 011 STB
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stb_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stb_f2);
      }
    }
    if(bit8 == 1)
    { // 1 + 011  LDNW
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldnw_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldnw_f2);
      }
    }
    break;

  case 0x4:
    if(bit8 == 0)
    { // 100 LDH
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldh_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldh_f2);
      }
    }
    else
    { // 1 + 100 STDW
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stdw_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stdw_f2);
      }
    }
    break;

  case 0x5:
    if(bit8 == 0)
    { // 101 STH
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,sth_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,sth_f2);
      }
    }
    else
    { // 1 + 101  STNW
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stnw_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stnw_f2);
      }
    }
    break;

  case 0x6:
    if(bit8 == 0)
    { // 110 LDW
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldw_f1);
      }
      else
      {
        if(creg_z == 0)
        {
          de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldw_f2_nc);
        }
        else if(creg_z & 0x1)
        {
          de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldw_f2_z1);
        }
        else
        {
          de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldw_f2_z0);
        }
      }
    }
    else
    { // 1 + 110 LDDW
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,lddw_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,lddw_f2);
      }
    }
    break;

  case 0x7:
    if(bit8 == 0)
    { // 111 STW
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stw_f1);
      }
      else
      {
        if(creg_z == 0)
        {
          de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stw_f2_nc);
        }
        else if(creg_z & 0x1)
        {
          de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stw_f2_z1);
        }
        else
        {
          de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stw_f2_z0);
        }
      }
    }
    else
    { // 1 + 111 STNDW
      word_t src_24 = get_uint(code,24,4) << 1;
      src_or_dst = src_24;
      if(is_register_offset)
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stndw_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stndw_f2);
      }
    }
    break;

  default:
    core->panic("DUnit::decode_32bit_ld_st_basic");
    break;
  }

  inst->set_de_func(de_func);
  inst->set_dst(src_or_dst);
}

void DUnit::decode_32bit_ld_st_long_immed2(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,offsetR,y,op,side;
  word_t src1,src2;
  word_t offset_byte,factor;
  creg_z = code >> 28;
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  de_func_t de_func;

  dst = get_uint(code,23,5);
  inst->set_dst(dst);
  offsetR = get_uint(code,8,15);
  y = get_uint(code,7,1);
  inst->set_xside(y);
  op = get_uint(code,4,3);
  side = get_uint(code,1,1);
  inst->set_side(side);

  if (y == 0)
  { // B14
    src1 = 14;
  }
  else
  { // B15
    src1 = 15;
  }
  inst->set_src1(src1);

  switch(op)
  {
  case 0x0:// LDHU
    factor = 2;
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_long_immed,ldhu);
    break;

  case 0x1:// LDBU
    factor = 1;
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_long_immed,ldbu);
    break;
    
  case 0x2:// LDB
    factor = 1;
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_long_immed,ldb);
    break;

  case 0x4:// LDH
    factor = 2;
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_long_immed,ldh);
    break;

  case 0x6:// LDW
    factor = 4;
    de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_long_immed,ldw);
    break;

  default:// store operation
    { 
      //word_t src = dst;
      if (op == 0x3)
      { // STB
        factor = 1;
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_long_immed,stb);
      }
      else if (op == 0x5)
      { // STH
        factor = 2;
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_long_immed,sth);
      }
      else if (op == 0x7)
      { // STW
        factor = 4;
        de_func = DE_FUNC_ADDR(DUnit,de_32bit_ld_st_long_immed,stw);
      }
      else
      {
        assert(false);
      }
    }
    break;
  }

  offset_byte = offsetR * factor;
  inst->set_de_func(de_func);
  inst->set_src2(offset_byte);
}

//    FMT C-6. Load/Store Long-Immediate Operations
//    31 29 | 28 | 27 23 | 22     8 |7| 6 4 |3|2|1|0
//     creg | z  |src/dst| offsetR  |y| op  |1|1|s|p
//      3   | 1  |   5   |   15     |1|  3  |   |1|1
/*
void DUnit::decode_32bit_ld_st_long_immed(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z,dst,offsetR,y,op,side;
  word_t src1,src2;
  word_t offset_byte;
  creg_z = code >> 28;
  de_func_t de_func;
  bool condition = cond(core,creg_z);
  if(!condition)
  {
    return;
  }

  dst = get_uint(code,23,5);
  offsetR = get_uint(code,8,15);
  y = get_uint(code,7,1);
  op = get_uint(code,4,3);
  side = get_uint(code,1,1);

  word_t stw_val;
  word_t baseR,dst_val,mem_addr;
  word_t factor;
  bool is_ld = true; // LD operation

  if (y == 0)
  { // B14
    baseR = core->reg_read(B_SIDE,14);
    src1 = 14;
  }
  else
  { // B15
    baseR = core->reg_read(B_SIDE,15);
    src1 = 15;
  }
  stw_req_t stw_req;

  switch(op)
  {
  case 0x1:
  case 0x2:
    factor = 1;
    break;

  case 0x0:
  case 0x4:
    factor = 2;
    break;

  case 0x6:
    factor = 4;
    break;

  default:
    factor = 4;
    break;
  }

  offset_byte = offsetR * factor;
  mem_addr= baseR + offset_byte;

  switch(op)
  {
  case 0x0:// LDHU
    dst_val = core->get_l2()->mem_read_half(mem_addr);
    //op_name = "LDHU_15bit_offset";
    break;

  case 0x1:// LDBU
    dst_val = core->get_l2()->mem_read_byte(mem_addr);
    //op_name = "LDBU_15bit_offset";
    break;
    
  case 0x2:// LDB
    dst_val = core->get_l2()->mem_read_byte(mem_addr);
    dst_val = get_sign_ext(dst_val,0,8);
    //op_name = "LDB_15bit_offset";
    break;

  case 0x4:// LDH
    dst_val = core->get_l2()->mem_read_half(mem_addr);
    dst_val = get_sign_ext(dst_val,0,16);
    //op_name = "LDH_15bit_offset";
    break;

  case 0x6:// LDW
    dst_val = core->get_l2()->mem_read_word(mem_addr);
    break;

  default:// store operation
    { 
      word_t src = dst;
      stw_val = core->reg_read(side,src);
      is_ld = false;
      if (op == 0x3)
      { // STB
        stw_val = get_uint(stw_val,0,8);
        //op_name = "STB_15bit_offset";
        //pCore->get_l2()->mem_write_byte(mem_addr,(byte_t)src_val);
        stw_req.type = TYPE_U8;
        offset_byte = offsetR;
      }
      else if (op == 0x5)
      { // STH
        stw_val = get_uint(stw_val,0,16);
        //op_name = "STH_15bit_offset";
        //pCore->get_l2()->mem_write_half(mem_addr,(half_t)src_val);
        stw_req.type = TYPE_U16;
        offset_byte = offsetR * 2;
      }
      else if (op == 0x7)
      { // STW
        //op_name = "STW_15bit_offset";
        //pCore->get_l2()->mem_write_word(mem_addr,src_val);
        stw_req.type = TYPE_U32;
        offset_byte = offsetR * 4;
      }
      else
      {
        assert(false);
      }
      mem_addr = baseR + offset_byte;
    }
    break;
  }

  src2 = offset_byte;

  if (is_ld)
  {
    core->push_reg_delay_ch_4c_delay(side,dst,dst_val);
  }
  else
  {
    stw_req.addr = mem_addr;
    stw_req.val = stw_val;
    //=core->_stw_change_req_list.push_back(stw_req);
    core->push_stw_req(stw_req);
  }
}
*/

void DUnit::decode(Core *core, Instruction *inst)
{
  /*
  op_code_t type = inst->get_op_type();
  word_t code = inst->get_code();
  de_func_t de_func = DE_FUNC_ADDR(DUnit,de_32bit,general); 
  inst->set_de_func(de_func);
  inst->set_src1(code);
  inst->set_src2(type);
  */
  decode2(core,inst);
}

inline void DUnit::decode2(Core *core, Instruction *inst)
{
  word_t code = inst->get_code();
  op_code_t type = (op_code_t)inst->get_op_type();

  switch(type)
  {
    //    FMT C-1. 1 or 2 Sources Instruction Format
    //    31 29 | 28 | 27 23 | 22 18 | 17 13 |12 7 |6|5|4|3|2|1|0
    //     creg | z  |  dst  |  src2 |  src1 | op  |1|0|0|0|0|s|p
    //      3   | 1  |   5   |   5   |   5   | 6   |         |1|1
    case OP_D_UNIT_32BIT_1_OR_2_SRC:
      decode_32bit_1or2_src2(core,code,inst);
      //inst->set_de_func(DE_FUNC_ADDR(DUnit,de_32bit,general)); 
      break;

    //    FMT C-2. Extended .D Unit 1 or 2 Sources Instruction Format
    //    31 29 | 28 | 27 23 | 22 18 | 17 13 |12|11|10| 9 6 |5|4|3|2|1|0
    //     creg | z  |  dst  |  src2 |  src1 |x |1 |0 | op  |1|1|0|0|s|p
    //      3   | 1  |   5   |   5   |   5   |1 |     |  4  |       |1|1
    case OP_D_UNIT_32BIT_EXT_1_OR_2_SRC:
      decode_32bit_ext_1or2_src2(core,code,inst);
      //inst->set_de_func(DE_FUNC_ADDR(DUnit,de_32bit,general)); 
      break;

    //    FMT C-3. ADDAB/ADDAH/ADDAW Long-Immediate Operations
    //    31|30|29|28| 27 23 | 22      8 |7| 6 4 |3|2|1|0
    //     0| 0| 0| 1| dst   |  offsetR  |y| op  |1|1|s|p
    //               |   5   |   15      | |  3  |
    case OP_D_UNIT_32BIT_ADDAX_LONG_IMMED:
      core->panic("OP_D_UNIT_32BIT_ADDAX_LONG_IMMED"); // c64x+
      break;

    //    FMT C-4. Linked Word Operations
    //    31 29 | 28 | 27 23 | 22 18 |17|16|15|14|13|12|11|10| 9 7 |6|5|4|3|2|1|0
    //     creg | z  |src/dst|  src2 |0 |0 |0 |0 |0 |0 |1 |0 | op  |1|0|0|0|0|1|p
    //      3   | 1  |   5   |   5   |                       |  3  |         |1|1
    case OP_D_UNIT_32BIT_LK_WD:
      core->panic("OP_D_UNIT_32BIT_LK_WD"); // c64x+
      break;


    //    FMT C-5. Load/Store Basic Operations  (and C-7 C-8)
    //    31 29 | 28 | 27 23 | 22 18 |17    13 |12  9 |8|7| 6 4 |3|2|1|0
    //     creg | z  |src/dst| baseR | offsetR | mode |r|y| op  |0|1|s|p
    //      3   | 1  |   5   |   5   |  5      |  4   |   |  3  |   |1|1
    case OP_D_UNIT_32BIT_LD_ST_BASIC:
    case OP_D_UNIT_32BIT_LD_ST_DW:
      decode_32bit_ld_st_basic2(core,code,inst);
      //inst->set_de_func(DE_FUNC_ADDR(DUnit,de_32bit,general)); 
      break;

    //    FMT C-6. Load/Store Long-Immediate Operations
    //    31 29 | 28 | 27 23 | 22     8 |7| 6 4 |3|2|1|0
    //     creg | z  |src/dst| offsetR  |y| op  |1|1|s|p
    //      3   | 1  |   5   |   15     |1|  3  |   |1|1
    case OP_D_UNIT_32BIT_LD_ST_LONG_IMMED:
      decode_32bit_ld_st_long_immed2(core,code,inst);
      //inst->set_de_func(DE_FUNC_ADDR(DUnit,de_32bit,general)); 
      break;

    default:
      core->panic("DUnit");
      break;
  }
}

//TODO remove it and use specific decode funtions
/*
DE_FUNC(DUnit,de_32bit,general)
{
  NO_CONDITION();
  //op_code_t type = static_cast<op_code_t>(src2); // save type in src2
  //code_t code = src1; // save code in src1
  op_code_t type = inst->get_op_type();
  code_t code = inst->get_code();

  switch(type)
  {
    //    FMT C-1. 1 or 2 Sources Instruction Format
    //    31 29 | 28 | 27 23 | 22 18 | 17 13 |12 7 |6|5|4|3|2|1|0
    //     creg | z  |  dst  |  src2 |  src1 | op  |1|0|0|0|0|s|p
    //      3   | 1  |   5   |   5   |   5   | 6   |         |1|1
    case OP_D_UNIT_32BIT_1_OR_2_SRC:
      decode_32bit_1or2_src(core,code,inst);
      break;

    //    FMT C-2. Extended .D Unit 1 or 2 Sources Instruction Format
    //    31 29 | 28 | 27 23 | 22 18 | 17 13 |12|11|10| 9 6 |5|4|3|2|1|0
    //     creg | z  |  dst  |  src2 |  src1 |x |1 |0 | op  |1|1|0|0|s|p
    //      3   | 1  |   5   |   5   |   5   |1 |     |  4  |       |1|1
    case OP_D_UNIT_32BIT_EXT_1_OR_2_SRC:
      decode_32bit_ext_1or2_src(core,code,inst);
      break;

    //    FMT C-3. ADDAB/ADDAH/ADDAW Long-Immediate Operations
    //    31|30|29|28| 27 23 | 22      8 |7| 6 4 |3|2|1|0
    //     0| 0| 0| 1| dst   |  offsetR  |y| op  |1|1|s|p
    //               |   5   |   15      | |  3  |
    case OP_D_UNIT_32BIT_ADDAX_LONG_IMMED:
      core->panic("OP_D_UNIT_32BIT_ADDAX_LONG_IMMED"); // c64x+
      break;

    //    FMT C-4. Linked Word Operations
    //    31 29 | 28 | 27 23 | 22 18 |17|16|15|14|13|12|11|10| 9 7 |6|5|4|3|2|1|0
    //     creg | z  |src/dst|  src2 |0 |0 |0 |0 |0 |0 |1 |0 | op  |1|0|0|0|0|1|p
    //      3   | 1  |   5   |   5   |                       |  3  |         |1|1
    case OP_D_UNIT_32BIT_LK_WD:
      core->panic("OP_D_UNIT_32BIT_LK_WD"); // c64x+
      break;


    //    FMT C-5. Load/Store Basic Operations  (and C-7 C-8)
    //    31 29 | 28 | 27 23 | 22 18 |17    13 |12  9 |8|7| 6 4 |3|2|1|0
    //     creg | z  |src/dst| baseR | offsetR | mode |r|y| op  |0|1|s|p
    //      3   | 1  |   5   |   5   |  5      |  4   |   |  3  |   |1|1
    case OP_D_UNIT_32BIT_LD_ST_BASIC:
    case OP_D_UNIT_32BIT_LD_ST_DW:
      decode_32bit_ld_st_basic(core,code,inst);
      break;

    //    FMT C-6. Load/Store Long-Immediate Operations
    //    31 29 | 28 | 27 23 | 22     8 |7| 6 4 |3|2|1|0
    //     creg | z  |src/dst| offsetR  |y| op  |1|1|s|p
    //      3   | 1  |   5   |   15     |1|  3  |   |1|1
    case OP_D_UNIT_32BIT_LD_ST_LONG_IMMED:
      decode_32bit_ld_st_long_immed(core,code,inst);
      break;

    default:
      core->panic("DUnit");
      break;
  }
}
*/

//"MVK_SCST5_SINT"
DE_FUNC(DUnit,de_32bit_1or2_src,mvk)
{
  DE_CONDITION(core,creg_z);

  //word_t dst_val = get_sign_ext_lsb5_quick(src1);
  const word_t dst_val = src1;
  core->push_reg_ch(side,dst,dst_val);
}

//"ADD_SINT_SINT_SINT"
DE_FUNC(DUnit,de_32bit_1or2_src,add_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src1_val + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,add_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src1 + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

//"SUB_SINT_SINT_SINT"
DE_FUNC(DUnit,de_32bit_1or2_src,sub_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val - src1_val;
  core->push_reg_ch(side,dst,dst_val);
}

//"SUB_SINT_UCST5_SINT"
DE_FUNC(DUnit,de_32bit_1or2_src,sub_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val - src1;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,addab_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src1_val + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,addab_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src1 + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,subab_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val - src1_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,subab_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val - src1;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,addah_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val + (src1_val << 1);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,addah_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val + (src1 << 1);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,subah_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val - (src1_val << 1);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,subah_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val - (src1 << 1);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,addaw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val + (src1_val << 2);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,addaw_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val + (src1 << 2);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,subaw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val - (src1_val << 2);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,subaw_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val - (src1 << 2);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,addad_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val + (src1_val << 3);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_1or2_src,addad_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = src2_val + (src1 << 3);
  core->push_reg_ch(side,dst,dst_val);
}

//"ANDN_UINT_XUINT_UINT";
DE_FUNC(DUnit,de_32bit_ext_1or2_src,andn)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  src2_val = 0xFFFFFFFF ^ src2_val;
  word_t dst_val = src1_val & src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

//"OR_UINT_XUINT_UINT"
DE_FUNC(DUnit,de_32bit_ext_1or2_src,or_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val | src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ext_1or2_src,or_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1 | src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

//"ADD2_I2_XI2_I2"
DE_FUNC(DUnit,de_32bit_ext_1or2_src,add2)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t src1_hi,src2_hi,src1_lo,src2_lo;
  word_t dst_hi,dst_lo,dst_val;

  src1_hi = get_sign_ext_msb16(src1_val);
  src2_hi = get_sign_ext_msb16(src2_val);
  src1_lo = get_sign_ext_lsb16(src1_val);
  src2_lo = get_sign_ext_lsb16(src2_val);
  dst_hi = (src1_hi + src2_hi) & 0xFFFF;
  dst_lo = (src1_lo + src2_lo) & 0xFFFF;
  dst_val = dst_lo | (dst_hi << 16);

  core->push_reg_ch(side,dst,dst_val);
}

//"SUB2_I2_XI2_I2"
DE_FUNC(DUnit,de_32bit_ext_1or2_src,sub2)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t src1_hi,src2_hi,src1_lo,src2_lo;
  word_t dst_hi,dst_lo,dst_val;

  src1_hi = get_sign_ext_msb16(src1_val);
  src2_hi = get_sign_ext_msb16(src2_val);
  src1_lo = get_sign_ext_lsb16(src1_val);
  src2_lo = get_sign_ext_lsb16(src2_val);
  dst_hi = (src1_hi - src2_hi) & 0xFFFF;
  dst_lo = (src1_lo - src2_lo) & 0xFFFF;
  dst_val = dst_lo | (dst_hi << 16);

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ext_1or2_src,and_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val & src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ext_1or2_src,and_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val & src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ext_1or2_src,add_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val + src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ext_1or2_src,add_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val + src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ext_1or2_src,sub)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val - src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ext_1or2_src,xor_f1)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val ^ src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ext_1or2_src,xor_f2)
{
  DE_CONDITION(core,creg_z);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val ^ src2_val;

  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ld_st_long_immed,ldb)
{
  DE_CONDITION(core,creg_z);

  word_t baseR = core->reg_read(B_SIDE,src1);
  const word_t offset_byte = src2;
  word_t mem_addr = baseR + offset_byte;

  word_t dst_val = core->get_l2()->mem_read_byte(mem_addr);
  dst_val = get_sign_ext(dst_val,0,8);

  core->push_reg_delay_ch_4c_delay(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ld_st_long_immed,ldbu)
{
  DE_CONDITION(core,creg_z);

  word_t baseR = core->reg_read(B_SIDE,src1);
  const word_t offset_byte = src2;
  word_t mem_addr = baseR + offset_byte;

  word_t dst_val = core->get_l2()->mem_read_byte(mem_addr);

  core->push_reg_delay_ch_4c_delay(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ld_st_long_immed,ldh)
{
  DE_CONDITION(core,creg_z);

  word_t baseR = core->reg_read(B_SIDE,src1);
  const word_t offset_byte = src2;
  word_t mem_addr = baseR + offset_byte;

  word_t dst_val = core->get_l2()->mem_read_half(mem_addr);
  dst_val = get_sign_ext(dst_val,0,16);

  core->push_reg_delay_ch_4c_delay(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ld_st_long_immed,ldhu)
{
  DE_CONDITION(core,creg_z);

  word_t baseR = core->reg_read(B_SIDE,src1);
  const word_t offset_byte = src2;
  word_t mem_addr = baseR + offset_byte;

  word_t dst_val = core->get_l2()->mem_read_half(mem_addr);

  core->push_reg_delay_ch_4c_delay(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ld_st_long_immed,ldw)
{
  DE_CONDITION(core,creg_z);

  word_t baseR = core->reg_read(B_SIDE,src1);
  const word_t offset_byte = src2;
  word_t mem_addr = baseR + offset_byte;

  word_t dst_val = core->get_l2()->mem_read_word(mem_addr);

  core->push_reg_delay_ch_4c_delay(side,dst,dst_val);
}

DE_FUNC(DUnit,de_32bit_ld_st_long_immed,stb)
{
  DE_CONDITION(core,creg_z);

  word_t baseR = core->reg_read(B_SIDE,src1);
  const word_t offset_byte = src2;

  stw_req_t stw_req;
  stw_req.addr = baseR + offset_byte;
  stw_req.type = TYPE_U8;
  stw_req.val = core->reg_read(side,dst);

  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_long_immed,sth)
{
  DE_CONDITION(core,creg_z);

  word_t baseR = core->reg_read(B_SIDE,src1);
  const word_t offset_byte = src2;

  stw_req_t stw_req;
  stw_req.addr = baseR + offset_byte;
  stw_req.type = TYPE_U16;
  stw_req.val = core->reg_read(side,dst);

  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_long_immed,stw)
{
  DE_CONDITION(core,creg_z);

  word_t baseR = core->reg_read(B_SIDE,src1);
  const word_t offset_byte = src2;

  stw_req_t stw_req;
  stw_req.addr = baseR + offset_byte;
  stw_req.type = TYPE_U32;
  stw_req.val = core->reg_read(side,dst);

  core->push_stw_req(stw_req);
}

#define MODE_PROC \
  mem_addr = base_addr;\
  switch(mode)\
  {\
  case 0x8:\
  case 0xC:\
    new_base_addr = base_addr - offset_factor * offset;\
    mem_addr = new_base_addr;\
    break;\
    \
  case 0x9:\
  case 0xD:\
    new_base_addr = base_addr + offset_factor * offset;\
    mem_addr = new_base_addr;\
    break;\
    \
  case 0x0:\
  case 0x4:\
    mem_addr = base_addr - offset_factor * offset;\
    break;\
    \
  case 0x1:\
  case 0x5:\
    mem_addr = base_addr + offset_factor * offset;\
    break;\
    \
  case 0xA:\
  case 0xE:\
    new_base_addr = base_addr - offset_factor * offset;\
    break;\
    \
  case 0xB:\
  case 0xF:\
    new_base_addr = base_addr + offset_factor * offset;\
    break;\
    \
  default:\
    break;\
  }

// src1 : baseR
// src2 : offsetR
// ldb_f1 : LDB register form
// xside : y
// dst : src_or_dst
DE_FUNC(DUnit,de_32bit_ld_st_basic,ldb_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 1;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_byte(mem_addr);
  ld_result = get_sign_ext(ld_result,0,8); // xxx sign ext

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldb_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  const word_t offset = src2;
  const word_t offset_factor = 1;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_byte(mem_addr);
  ld_result = get_sign_ext(ld_result,0,8); // xxx sign ext

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldbu_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 1;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_byte(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldbu_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  const word_t offset = src2;
  const word_t offset_factor = 1;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_byte(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldh_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 2;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_half(mem_addr);
  ld_result = get_sign_ext_lsb16(ld_result);// xxx sign ext

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldh_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 2;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_half(mem_addr);
  ld_result = get_sign_ext_lsb16(ld_result);// xxx sign ext

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldhu_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 2;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_half(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldhu_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 2;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_half(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_word(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldw_f2_z0)
{
  DE_CONDITION_Z0(core);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_word(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldw_f2_z1)
{
  DE_CONDITION_Z1(core);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_word(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldw_f2_nc)
{
  NO_CONDITION();

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_word(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

//same as ldw_f1
DE_FUNC(DUnit,de_32bit_ld_st_basic,ldnw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_word(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

// same as ldw_f2
DE_FUNC(DUnit,de_32bit_ld_st_basic,ldnw_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  word_t ld_result = core->get_l2()->mem_read_word(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }
  core->push_reg_delay_ch_4c_delay(side,dst,ld_result);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,lddw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 8;
  const word_t src_or_dst = dst;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  qword_t qval = core->get_l2()->mem_read_qword(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  if(is_reg_even(src_or_dst))
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,qval & 0xFFFFFFFF);
    core->push_reg_delay_ch_4c_delay(side,src_or_dst+1,(qval >> 32) & 0xFFFFFFFF);
  }
  else
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,(qval >> 32) & 0xFFFFFFFF);
  }
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,lddw_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 8;
  const word_t src_or_dst = dst;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  qword_t qval = core->get_l2()->mem_read_qword(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  if(is_reg_even(src_or_dst))
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,qval & 0xFFFFFFFF);
    core->push_reg_delay_ch_4c_delay(side,src_or_dst+1,(qval >> 32) & 0xFFFFFFFF);
  }
  else
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,(qval >> 32) & 0xFFFFFFFF);
  }
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldndw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t sc = get_uint(inst->get_code(),23,1);
  word_t offset_factor = (sc == 1) ? 8 : 1;
  const word_t src_or_dst = dst;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  qword_t qval = core->get_l2()->mem_read_qword(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  if(is_reg_even(src_or_dst))
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,qval & 0xFFFFFFFF);
    core->push_reg_delay_ch_4c_delay(side,src_or_dst+1,(qval >> 32) & 0xFFFFFFFF);
  }
  else
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,(qval >> 32) & 0xFFFFFFFF);
  }
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,ldndw_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t sc = get_uint(inst->get_code(),23,1);
  word_t offset_factor = (sc == 1) ? 8 : 1;
  const word_t src_or_dst = dst;
  word_t new_base_addr = base_addr;
  word_t mem_addr;

  MODE_PROC;

  qword_t qval = core->get_l2()->mem_read_qword(mem_addr);

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  if(is_reg_even(src_or_dst))
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,qval & 0xFFFFFFFF);
    core->push_reg_delay_ch_4c_delay(side,src_or_dst+1,(qval >> 32) & 0xFFFFFFFF);
  }
  else
  {
    core->push_reg_delay_ch_4c_delay(side,src_or_dst,(qval >> 32) & 0xFFFFFFFF);
  }
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stb_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 1;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);
  stw_val &= 0xFF;

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U8;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stb_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 1;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);
  stw_val &= 0xFF;

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U8;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,sth_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 2;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);
  stw_val &= 0xFFFF;

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U16;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,sth_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 2;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);
  stw_val &= 0xFFFF;

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U16;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U32;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stw_f2_nc)
{
  NO_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U32;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stw_f2_z0)
{
  DE_CONDITION_Z0(core);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U32;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stw_f2_z1)
{
  DE_CONDITION_Z1(core);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U32;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stnw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U32;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stnw_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 4;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  stw_req_t stw_req;
  stw_req.val = stw_val;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U32;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stdw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t offset_factor = 8;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);
  qword_t qval;

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  if(is_reg_even(dst))
  {
    qval = core->reg_read(side,dst + 1);
    qval = (qval << 32) | stw_val;
  }
  else
  {
    qval = core->reg_read(side,dst - 1); // reg_even
    qval = ((qword_t)stw_val << 32) | qval;
  }

  stw_req_t stw_req;
  stw_req.qval = qval;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U64;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stdw_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t offset_factor = 8;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);
  qword_t qval;

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  if(is_reg_even(dst))
  {
    qval = core->reg_read(side,dst + 1);
    qval = (qval << 32) | stw_val;
  }
  else
  {
    qval = core->reg_read(side,dst - 1); // reg_even
    qval = ((qword_t)stw_val << 32) | qval;
  }

  stw_req_t stw_req;
  stw_req.qval = qval;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U64;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stndw_f1)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = core->reg_read(xside,src2);
  const word_t sc = get_uint(inst->get_code(),23,1);
  word_t offset_factor = (sc == 1) ? 8 : 1;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);
  qword_t qval;

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  if(is_reg_even(dst))
  {
    qval = core->reg_read(side,dst + 1);
    qval = (qval << 32) | stw_val;
  }
  else
  {
    qval = core->reg_read(side,dst - 1); // reg_even
    qval = ((qword_t)stw_val << 32) | qval;
  }

  stw_req_t stw_req;
  stw_req.qval = qval;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U64;
  core->push_stw_req(stw_req);
}

DE_FUNC(DUnit,de_32bit_ld_st_basic,stndw_f2)
{
  DE_CONDITION(core,creg_z);

  word_t mode = get_uint(inst->get_code(),9,4);
  word_t base_addr = core->reg_read(xside,src1);
  word_t offset = src2;
  const word_t sc = get_uint(inst->get_code(),23,1);
  word_t offset_factor = (sc == 1) ? 8 : 1;
  word_t new_base_addr = base_addr;
  word_t mem_addr;
  word_t stw_val = core->reg_read(side,dst);
  qword_t qval;

  MODE_PROC;

  // update baseR
  if(new_base_addr != base_addr)
  {
    core->push_reg_ch(xside,src1,new_base_addr);
  }

  if(is_reg_even(dst))
  {
    qval = core->reg_read(side,dst + 1);
    qval = (qval << 32) | stw_val;
  }
  else
  {
    qval = core->reg_read(side,dst - 1); // reg_even
    qval = ((qword_t)stw_val << 32) | qval;
  }

  stw_req_t stw_req;
  stw_req.qval = qval;
  stw_req.addr = mem_addr;
  stw_req.type = TYPE_U64;
  core->push_stw_req(stw_req);
}



END_NS