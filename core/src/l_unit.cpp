#include "core/inc/l_unit.hpp"
#include "core/inc/core.hpp"

#include "jit/inc/jit.hpp"

BEGIN_NS

//31 29 28|27 23|22 18|17 13|12|11 5|4 3 2 1 0
//creg  z |dst  |src2 |src1 |x |op  |1 1 0 s p
//3     1 |5    |5    |5    |1 |7   |      1 1
void LUnit::decode_32bit_1or2_src(Core *core, code_t code, Instruction *inst)
{
  word_t creg_z = code >> 28;

#define GET_UINT(code,start,len) (code >> start) & ((1 << len) - 1)
  word_t dst = GET_UINT(code,23,5);
  word_t src2 = GET_UINT(code,18,5);
  word_t src1 = GET_UINT(code,13,5);
  word_t op = GET_UINT(code,5,7);
  word_t side = GET_UINT(code,1,1);
  word_t xside = (BIT_TEST(code,12)) ? (side ^ 1) : side;
#undef GET_UINT

  de_func_t de_func;
  switch(op)
  {
    case 0x53: // sint, xsint, uint   CMPEQ  101 0011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpeq_f1);
      break;

    case 0x52: // scst5, xint, uint CMPEQ  101 0010
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpeq_f2);
      break;

    case 0x51: // xsint,slong,uint CMPEQ  101 0001
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpeq_f3);
      break;

    case 0x50: // scst5,slong,uint CMPEQ  101 0000
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpeq_f4);
      break;

    case 0x4F: // uint, xuint, uint  CMPGTU  100 1111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpgtu_f1);
      break;

    case 0x4E: // ucst4/5, xuint, uint  CMPGTU  100 1110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpgtu_f2);
      break;

    case 0x4D: // xuint, ulong, uint  CMPGTU  100 1101
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpgtu_f3);
      break;

    case 0x4C: // ucst4/5, ulong, uint  CMPGTU  100 1100
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpgtu_f4);
      break;

    case 0x47: // sint, xsint, uint  CMPGT  100 0111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpgt_f1);
      break;

    case 0x46: // scst5, xsint, uint  CMPGT  100 0110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpgt_f2);
      break;

    case 0x45: // xsint, slong, uint  CMPGT  100 0101
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpgt_f3);
      break;

    case 0x44: // scst5, slong, uint  CMPGT  100 0100
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpgt_f4);
      break;

    case 0x48: // u4, xu4, u4  MINU4  100 1000
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,minu4);
      break; 

    case 0x43: // u4, xu4, u4  MAXU4  100 0011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,maxu4);
      break;

    case 0x42: // s2, xs2, s2  MAX2  100 0010
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,max2);
      break;

    case 0x41: // s2, xs2, s2  MIN2  100 0001
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,min2);
      break;

    case 0x5F: // uint, xuint, uint  CMPLTU  101 1111
      //de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpltu_f1);
      SET_DE_FUNC_NC_Z0_Z1(creg_z,LUnit,de_32bit_1or2_src,cmpltu_f1);
      break;

    case 0x5E: // ucst4/5, xuint, uint  CMPLTU  101 1110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpltu_f2);
      break;

    case 0x5D: // xuint, ulong, uint  CMPLTU  101 1101
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpltu_f3);
      break;

    case 0x5C: // ucst4/5, ulong, uint  CMPLTU  101 1100
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpltu_f4);
      break;

    case 0x57: // sint, xsint, uint  CMPLT  101 0111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmplt_f1);
      break;

    case 0x56: // scst5, xsint, uint  CMPLT  101 0110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmplt_f2);
      break;

    case 0x55: // xsint, slong, uint  CMPLT  101 0101
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmplt_f3);
      break;

    case 0x54: // scst5, slong, uint  CMPLT  101 0100
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmplt_f4);
      break;

    case 0x6B: // uint, xuint, uint  LMBD  110 1011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,lmbd_f1);
      break;

    case 0x6A: // cst5, xuint, uint  LMBD  110 1010
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,lmbd_f2);
      break;

    case 0x63: // xsint, uint  NORM  110 0011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,norm_f1);
      break;

    case 0x60: // slong, uint  NORM  110 0000
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,norm_f2);
      break;

    case 0x7F: // uint, xuint, uint  OR  111 1111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,or_f1);
      break;

    case 0x7E: // scst5, xuint, uint  OR  111 1110
      src1 = get_sign_ext_lsb5_quick(src1);
      src2 = (xside << 5) + src2; // abs reg idx
      dst = (side << 5) + dst;
      if(creg_z == 0)
      {
        de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,or_f2_nc);
      }
      else
      {
        de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,or_f2);
      }
      break;

    case 0x00: // i2, xi2, i2  PACK2  000 0000
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,pack2);
      break;

    case 0x1E: // i2, xi, i2  PACKH2  001 1110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,packh2);
      break;

    case 0x61: // u4,xu4,u4  SHLMB 110 0001
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,shlmb);
      break;

    case 0x62: // u4,xu4,u4  SHRMB 110 0010
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,shrmb);
      break;

    case 0x69: // i4, xi4, i4  PACKH4  110 1001
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,packh4);
      break;

    case 0x68: // i4,xi4,i4  PACKL4  110 1000
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,packl4);
      break;

      // xxx 0x11 is wrong
    case 0x1C: // i2,xi2,i2  PACKHL2  001 0001
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,packhl2);
      break;

    case 0x1B: // i2,xi2,i2  PACKLH2  001 1011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,packlh2);
      break;

    case 0x1A: // xsint,sint  ABS  001 1010   |   // xu4,u4  SWAP4  001 1010
      core->panic("<ERROR>LUnit,Detect a unary instruction is 1or2 src");
      break;

    case 0x13: // sint,xsint,sint  SADD  001 0011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sadd_f1);
      break;

    case 0x12: // scst5, xsint, sint  SADD  001 0010
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sadd_f2);
      break;

    case 0x31: // xsint,slong,slong  SADD  011 0001
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sadd_f3);
      break;

    case 0x30: // scst5,slong,slong  SADD  011 0000
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sadd_f4);
      break;

    case 0x0F: // sint,xsint,sint  SSUB  000 1111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sadd_f1);
      break;

    case 0x1F: // scst5, xsint, sint  SSUB  001 1111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sadd_f2);
      break;

    case 0x0E: // xsint,slong,slong  SSUB  000 1110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sadd_f3);
      break;

    case 0x2C: // scst5,slong,slong  SSUB  010 1100
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sadd_f4);
      break;

    case 0x40: // slong,sint  SAT  100 0000
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sat);
      break;

    case 0x38: // xsint,slong,slong ABS 011 1000
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,abs_slong);
      break;

    case 0x07: // sint,xsint,sint  SUB  000 0111
      SET_DE_FUNC_NC_Z0_Z1(creg_z,LUnit,de_32bit_1or2_src,sub_f1);
      break;

    case 0x17: // xsint,sint,sint  SUB  001 0111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sub_f2);
      break;

    case 0x27: // sint,xsint,slong  SUB  010 0111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sub_f3);
      break;

    case 0x37: // xsint,sint,slong  SUB  011 0111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sub_f4);
      break;

    case 0x06: // scst5,xsint,sint  SUB  000 0110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sub_f5);
      break;

    case 0x24: // scst5,slong,slong  SUB  010 0100
		  de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sub_f6);
      break;

    case 0x03: // sint, xsint, sint ADD  000 0011
      if(creg_z)
      {
		    de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f1);
      }
      else
      {
        de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f1_nc);
      }
		  break;
		  
    case 0x23: // sint, xsint, slong ADD  010 0011
		  //de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f2);
      SET_DE_FUNC_NC_Z0_Z1(creg_z,LUnit,de_32bit_1or2_src,add_f2);
		  break;	

		case 0x21: // xsint,slong,slong ADD  010 0001
		  de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f3);
		  break;
		  
		case 0x02: // scst5,xsint,sint ADD 000 0010
		  //de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f4);
      src1 = get_sign_ext_lsb5_quick(src1);
      SET_DE_FUNC_NC_Z0_Z1(creg_z,LUnit,de_32bit_1or2_src,add_f4);
      //SET_DE_FUNC(creg_z,LUnit,de_32bit_1or2_src,add_f4);
		  break;

		case 0x20: // scst5,slong,slong ADD 010 0000
		  de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f5);	  
		  break;

    case 0x2B: // uint,xuint,ulong ADDU  010 1011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,addu_f1);
      break;

    case 0x29: // xuint,ulong,ulong  ADDU  010 1001
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,addu_f2);
      break;

    case 0x05: // i2,xi2,i2  ADD2  000 0101
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add2);
      break;

    case 0x65: // i4,xi4,i4  ADD4  110 0101
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add4);
      break;

    case 0x7C: // uint,xuint,uint ANDN  111 1100
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,andn);
      break;

    case 0x7B: // uint,xuint,uint  AND  111 1011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,and_f1);
      break;

    case 0x7A: // scst5,xuint,uint  AND  111 1010
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,and_f2);
      break;

    case 0x5A: // u4,xu4,u4  SUBABS4  101 1010
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,subabs4);
      break;

    case 0x4B: // uint,xuint,uint  SUBC  100 1011
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,subc);
      break;

    case 0x04: // i2,xi2,i2  SUB2  000 0100
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sub2);
      break;

    case 0x66: // i4,xi4,i4  SUB4  110 0110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,sub4);
      break;

    case 0x6F: // uint,xuint,uint  XOR  110 1111
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,xor_f1);
      break;
          
    case 0x6E: // scst5,xuint,uint  XOR  110 1110
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,xor_f2);
      break;

    case 0x2F: // SUBU uint,xuint,ulong
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,subu_f1);
      break;

    case 0x3F: // SUBU xuint,uint,ulong
      de_func = DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,subu_f2);
      break;

    default:
      std::stringstream ss;
      ss << "<ERROR>Invalid instruction:" <<
        to_hex_str(code) << ",code addr:" << to_hex_str(inst->get_code_addr()) << "\n";
      core->panic(ss.str().c_str());
      break;
  }// switch(op)

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

// 31 29 28| 27 23 | 22 18 | 17 13 |12|11 10 9 8 7 6 5 4 3 2 1 0
// creg   z| dst   |src2   |op     |x | 0  0 1 1 0 1 0 1 1 0 s p
// 3      1| 5     |5      |5      |1 |                      1 1
void LUnit::decode_32bit_unary(Core *core, code_t code,Instruction *inst)
{
  word_t creg_z,dst,src2,op,x,side,xside;
  creg_z = code >> 28;
  dst = get_uint(code,23,5);
  src2 = get_uint(code,18,5);
  op = get_uint(code,13,5);
  side = get_uint(code,1,1);
  xside = (BIT_TEST(code,12)) ? (side ^ 1) : side;

  de_func_t de_func;
  switch (op)
  {
  case 0: // ABS
    //dst_val = labs(src2_val);
    de_func = DE_FUNC_ADDR(LUnit,de_32bit_unary,abs);
    break;

  case 1: // SWAP4
    //dst_val = swap4(src2_val);
    de_func = DE_FUNC_ADDR(LUnit,de_32bit_unary,swap4);
    break;

  case 2: // UNPKLU4
    //dst_val = unpklu4(src2_val);
    de_func = DE_FUNC_ADDR(LUnit,de_32bit_unary,unpklu4);
    break;

  case 3: // UNPKHU4
    //dst_val = unpkhu4(src2_val);
    de_func = DE_FUNC_ADDR(LUnit,de_32bit_unary,unpkhu4);
    break;

  case 4: // ABS2
    //dst_val = abs2(src2_val);
    de_func = DE_FUNC_ADDR(LUnit,de_32bit_unary,abs2);
    break;

  case 5: // MVK   scst5,sint
    //dst_val = get_sign_ext_lsb5_quick(src2);
    src2 = get_sign_ext_lsb5_quick(src2);
    SET_DE_FUNC_NC_Z0_Z1(creg_z,LUnit,de_32bit_unary,mvk);
    
    break;

  default:
    std::stringstream ss;
    ss << "<ERROR>Invalid instruction:" <<
      to_hex_str(code) << "\n";
    core->panic(ss.str().c_str());
    break;
  }

  inst->set_de_func(de_func);
  inst->set_cregz(creg_z);
  if(creg_z != 0)
  {
    inst->set_cond_reg_phy_addr(Unit::get_cond_reg_addr(core,creg_z));
  }
  inst->set_xside(xside);
  inst->set_side(side);
  inst->set_src2(src2);
  inst->set_dst(dst);
}

void LUnit::decode(Core *core, Instruction *inst)
{
  op_code_t type = (op_code_t)inst->get_op_type();
  word_t code = inst->get_code();

  switch(type)
  {
//31 29 28|27 23|22 18|17 13|12|11 5|4 3 2 1 0
//creg  z |dst  |src2 |src1 |x |op  |1 1 0 s p
//3     1 |5    |5    |5    |1 |7   |      1 1
    case OP_L_UNIT_32BIT_1_OR_2_SRC: // FMT1
      decode_32bit_1or2_src(core,code,inst);
      break;
       
// 31 29 28| 27 23 | 22 18 | 17 13 |12|11 10 9 8 7 6 5 4 3 2 1 0
// creg   z| dst   |src2   |op     |x | 0  0 1 1 0 1 0 1 1 0 s p
// 3      1| 5     |5      |5      |1 |                      1 1
    case OP_L_UNIT_32BIT_UNARY: // FMT2
      decode_32bit_unary(core,code,inst);
      break;

      //c64x+
    case OP_L_UNIT_32BIT_1_OR_2_SRC_NON_COND: // FMT3
      assert(false);
      break;

    default:
      assert(false);
      break;
  }
}


// sint, xsint, uint   CMPEQ  101 0011
DE_FUNC(LUnit,de_32bit_1or2_src,cmpeq_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = (src1_val == src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// scst5, xint, uint CMPEQ  101 0010
DE_FUNC(LUnit,de_32bit_1or2_src,cmpeq_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = (src1_val == src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// xsint,slong,uint CMPEQ  101 0001
// src1 use xpath
DE_FUNC(LUnit,de_32bit_1or2_src,cmpeq_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  word_t dst_val = ((sqword_t)src2_qval == (long)src1_val);
  core->push_reg_ch(side,dst,dst_val);
}

// scst5,slong,uint CMPEQ  101 0000
DE_FUNC(LUnit,de_32bit_1or2_src,cmpeq_f4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  word_t dst_val = ((sqword_t)src2_qval == (long)src1_val);
  core->push_reg_ch(side,dst,dst_val);
}

// uint, xuint, uint  CMPGTU  100 1111
DE_FUNC(LUnit,de_32bit_1or2_src,cmpgtu_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = (src1_val > src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// ucst4(5?), xuint, uint  CMPGTU  100 1110
//xxx C64 should use ucst5
//xxx TI document wrong?
DE_FUNC(LUnit,de_32bit_1or2_src,cmpgtu_f2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = (src1 > src2_val); // src1 is ucst5
  core->push_reg_ch(side,dst,dst_val);
}

// xuint, ulong, uint  CMPGTU  100 1101
// src1 use xpath
DE_FUNC(LUnit,de_32bit_1or2_src,cmpgtu_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  word_t dst_val = ((qword_t)src1_val > src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

// ucst4/5, ulong, uint  CMPGTU  100 1100
// ucst4 for C62x; ucst5 for C64x or C64x+
DE_FUNC(LUnit,de_32bit_1or2_src,cmpgtu_f4)
{
  DE_CONDITION(core,cregz);

  qword_t src2_qval = core->reg_read_long(side,src2);
  word_t dst_val = ((qword_t)src1 > src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

#define LU_DE_32BIT_1OR2_SRC_CMPLTU_FMT1_BODY() \
  word_t src1_val = core->reg_read(side,src1); \
  word_t src2_val = core->reg_read(xside,src2); \
  word_t dst_val = (src1_val < src2_val); \
  core->push_reg_ch(side,dst,dst_val);

// uint, xuint, uint  CMPLTU  101 1111
DE_FUNC(LUnit,de_32bit_1or2_src,cmpltu_f1_nc)
{
  NO_CONDITION();
  LU_DE_32BIT_1OR2_SRC_CMPLTU_FMT1_BODY();
}

DE_FUNC(LUnit,de_32bit_1or2_src,cmpltu_f1_z0)
{
  DE_CONDITION_Z0(core);
  LU_DE_32BIT_1OR2_SRC_CMPLTU_FMT1_BODY();
}

DE_FUNC(LUnit,de_32bit_1or2_src,cmpltu_f1_z1)
{
  DE_CONDITION_Z1(core);
  LU_DE_32BIT_1OR2_SRC_CMPLTU_FMT1_BODY();
}

// ucst4/5, xuint, uint  CMPLTU  101 1110
//xxx C64 should use ucst5?
//xxx TI document wrong
DE_FUNC(LUnit,de_32bit_1or2_src,cmpltu_f2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = (src1 < src2_val); // src1 is ucst5
  core->push_reg_ch(side,dst,dst_val);
}

// xuint, ulong, uint  CMPLTU  101 1101
// src1 use xpath
DE_FUNC(LUnit,de_32bit_1or2_src,cmpltu_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  word_t dst_val = ((qword_t)src1_val < src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

// ucst4/5, ulong, uint  CMPLTU  101 1100
// ucst4 for C62x; ucst5 for C64x or C64x+
DE_FUNC(LUnit,de_32bit_1or2_src,cmpltu_f4)
{
  DE_CONDITION(core,cregz);

  qword_t src2_qval = core->reg_read_long(side,src2);
  word_t dst_val = ((qword_t)src1 < src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

// sint, xsint, uint  CMPGT  100 0111
DE_FUNC(LUnit,de_32bit_1or2_src,cmpgt_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = ((long)src1_val > (long)src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// scst5, xsint, uint  CMPGT  100 0110
DE_FUNC(LUnit,de_32bit_1or2_src,cmpgt_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = ((long)src1_val > (long)src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// xsint, slong, uint  CMPGT  100 0101
// src1 use xpath
DE_FUNC(LUnit,de_32bit_1or2_src,cmpgt_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  word_t dst_val = ((long)src1_val > (sqword_t)src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

// scst5, slong, uint  CMPGT  100 0100
DE_FUNC(LUnit,de_32bit_1or2_src,cmpgt_f4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  word_t dst_val = ((long)src1_val > (sqword_t)src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

// sint, xsint, uint  CMPLT  101 0111
DE_FUNC(LUnit,de_32bit_1or2_src,cmplt_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = ((long)src1_val < (long)src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// scst5, xsint, uint  CMPLT  101 0110
DE_FUNC(LUnit,de_32bit_1or2_src,cmplt_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = ((long)src1_val < (long)src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// xsint, slong, uint  CMPLT  101 0101
// src1 use xpath
DE_FUNC(LUnit,de_32bit_1or2_src,cmplt_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  word_t dst_val = ((long)src1_val < (sqword_t)src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

// scst5, slong, uint  CMPLT  101 0100
DE_FUNC(LUnit,de_32bit_1or2_src,cmplt_f4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  word_t dst_val = ((long)src1_val < (sqword_t)src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

// u4, xu4, u4  MINU4  100 1000
DE_FUNC(LUnit,de_32bit_1or2_src,minu4)
{
  DE_CONDITION(core,cregz);
  word_t a_3,a_2,a_1,a_0;
  word_t b_3,b_2,b_1,b_0;
  word_t dst_3,dst_2,dst_1,dst_0;

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val;

  a_3 = get_uint(src1_val,24,8);
  a_2 = get_uint(src1_val,16,8);
  a_1 = get_uint(src1_val,8,8);
  a_0 = get_uint(src1_val,0,8);
  b_3 = get_uint(src2_val,24,8);
  b_2 = get_uint(src2_val,16,8);
  b_1 = get_uint(src2_val,8,8);
  b_0 = get_uint(src2_val,0,8);

  dst_3 = min<byte_t>(a_3,b_3);
  dst_2 = min<byte_t>(a_2,b_2);
  dst_1 = min<byte_t>(a_1,b_1);
  dst_0 = min<byte_t>(a_0,b_0);

  dst_val = (dst_3 << 24) | (dst_2 << 16)
    | (dst_1 << 8) | dst_0;
  core->push_reg_ch(side,dst,dst_val);
}

// u4, xu4, u4  MAXU4  100 0011
DE_FUNC(LUnit,de_32bit_1or2_src,maxu4)
{
  DE_CONDITION(core,cregz);
  word_t a_3,a_2,a_1,a_0;
  word_t b_3,b_2,b_1,b_0;
  word_t dst_3,dst_2,dst_1,dst_0;

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val;

  a_3 = get_uint(src1_val,24,8);
  a_2 = get_uint(src1_val,16,8);
  a_1 = get_uint(src1_val,8,8);
  a_0 = get_uint(src1_val,0,8);
  b_3 = get_uint(src2_val,24,8);
  b_2 = get_uint(src2_val,16,8);
  b_1 = get_uint(src2_val,8,8);
  b_0 = get_uint(src2_val,0,8);

  dst_3 = max<byte_t>(a_3,b_3);
  dst_2 = max<byte_t>(a_2,b_2);
  dst_1 = max<byte_t>(a_1,b_1);
  dst_0 = max<byte_t>(a_0,b_0);

  dst_val = (dst_3 << 24) | (dst_2 << 16)
    | (dst_1 << 8) | dst_0;
  core->push_reg_ch(side,dst,dst_val);
}

// s2, xs2, s2  MIN2  100 0001
DE_FUNC(LUnit,de_32bit_1or2_src,min2)
{
  DE_CONDITION(core,cregz);

  shalf_t sa_hi,sa_lo,sb_hi,sb_lo,dst_hi,dst_lo;
  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val;

  sa_hi = get_sign_ext_msb16(src1_val);
  sa_lo = get_sign_ext_lsb16(src1_val);
  sb_hi = get_sign_ext_msb16(src2_val);
  sb_lo = get_sign_ext_lsb16(src2_val);

  dst_hi = min<shalf_t>(sa_hi,sb_hi);
  dst_lo = min<shalf_t>(sa_lo,sb_lo);
  dst_val = (dst_hi << 16) | dst_lo;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_1or2_src,max2)
{
  DE_CONDITION(core,cregz);

  shalf_t sa_hi,sa_lo,sb_hi,sb_lo,dst_hi,dst_lo;
  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val;

  sa_hi = get_sign_ext_msb16(src1_val);
  sa_lo = get_sign_ext_lsb16(src1_val);
  sb_hi = get_sign_ext_msb16(src2_val);
  sb_lo = get_sign_ext_lsb16(src2_val);

  dst_hi = max<shalf_t>(sa_hi,sb_hi);
  dst_lo = max<shalf_t>(sa_lo,sb_lo);
  dst_val = (dst_hi << 16) | dst_lo;
  core->push_reg_ch(side,dst,dst_val);
}

//uint, xuint, uint  LMBD  110 1011
DE_FUNC(LUnit,de_32bit_1or2_src,lmbd_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  src1_val = src1_val & 0x1; // for safe
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = lmbd(src2_val,src1_val);
  core->push_reg_ch(side,dst,dst_val);
}

// cst5, xuint, uint  LMBD  110 1010
DE_FUNC(LUnit,de_32bit_1or2_src,lmbd_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = src1 & 0x1;
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = lmbd(src2_val,src1_val);
  core->push_reg_ch(side,dst,dst_val);
}

// xsint, uint  NORM  110 0011
DE_FUNC(LUnit,de_32bit_1or2_src,norm_f1)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = norm(src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// slong, uint  NORM  110 0000
DE_FUNC(LUnit,de_32bit_1or2_src,norm_f2)
{
  DE_CONDITION(core,cregz);

  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40); // NEED?
  word_t dst_val = norm_u40(src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

// uint, xuint, uint  OR  111 1111
DE_FUNC(LUnit,de_32bit_1or2_src,or_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val | src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// scst5, xuint, uint  OR  111 1110
DE_FUNC(LUnit,de_32bit_1or2_src,or_f2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read_abs_idx(src2);
  word_t dst_val = src1 | src2_val;
  core->push_reg_ch_abs_idx(dst,dst_val);
}

// scst5, xuint, uint  OR  111 1110
DE_FUNC(LUnit,de_32bit_1or2_src,or_f2_nc)
{
  NO_CONDITION();
  word_t src2_val = core->reg_read_abs_idx(src2);
  word_t dst_val = src1 | src2_val;
  core->push_reg_ch_abs_idx(dst,dst_val);
}

// i2, xi2, i2  PACK2  000 0000
DE_FUNC(LUnit,de_32bit_1or2_src,pack2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_lo,b_lo,dst_val;
  a_lo = get_lsb16(src1_val);
  b_lo = get_lsb16(src2_val);
  dst_val = (a_lo << 16) | b_lo;
  core->push_reg_ch(side,dst,dst_val);
}

// i2, xi, i2  PACKH2  001 1110
DE_FUNC(LUnit,de_32bit_1or2_src,packh2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_hi,b_hi,dst_val;
  a_hi = get_msb16(src1_val);
  b_hi = get_msb16(src2_val);
  dst_val = (a_hi << 16) | b_hi;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_1or2_src,shlmb)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = shlmb(src1_val,src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_1or2_src,shrmb)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = shrmb(src1_val,src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// i4, xi4, i4  PACKH4  110 1001
DE_FUNC(LUnit,de_32bit_1or2_src,packh4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_3,a_1,b_3,b_1,dst_val;
  a_3 = get_uint(src1_val,24,8);
  a_1 = get_uint(src1_val,8,8);
  b_3 = get_uint(src2_val,24,8);
  b_1 = get_uint(src2_val,8,8);
  dst_val = (a_3 << 24) | (a_1 << 16) |
    (b_3 << 8) | b_1;
  core->push_reg_ch(side,dst,dst_val);
}

// i4,xi4,i4  PACKL4  110 1000
DE_FUNC(LUnit,de_32bit_1or2_src,packl4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_2,a_0,b_2,b_0,dst_val;
  a_2 = get_uint(src1_val,16,8);
  a_0 = get_uint(src1_val,0,8);
  b_2 = get_uint(src2_val,16,8);
  b_0 = get_uint(src2_val,0,8);
  dst_val = (a_2 << 24) | (a_0 << 16) |
    (b_2 << 8) | b_0;
  core->push_reg_ch(side,dst,dst_val);
}

// i2,xi2,i2  PACKHL2  001 0001
DE_FUNC(LUnit,de_32bit_1or2_src,packhl2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_hi,b_lo,dst_val;
  a_hi = get_msb16(src1_val);
  b_lo = get_lsb16(src2_val);
  dst_val = (a_hi << 16) | b_lo;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_1or2_src,packlh2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_lo,b_hi,dst_val;
  a_lo = get_lsb16(src1_val);
  b_hi = get_msb16(src2_val);
  dst_val = (a_lo << 16) | b_hi;
  core->push_reg_ch(side,dst,dst_val);
}

// sint,xsint,sint  SADD  001 0011
DE_FUNC(LUnit,de_32bit_1or2_src,sadd_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = sadd(src1_val,src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// scst5, xsint, sint  SADD  001 0010
DE_FUNC(LUnit,de_32bit_1or2_src,sadd_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = sadd(src1_val,src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// xsint,slong,slong  SADD  011 0001
// src1 use xpath
DE_FUNC(LUnit,de_32bit_1or2_src,sadd_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  qword_t dst_qval = sadd_u40(src1_val,src2_qval);

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// scst5,slong,slong  SADD  011 0000
DE_FUNC(LUnit,de_32bit_1or2_src,sadd_f4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  qword_t dst_qval = sadd_u40(src1_val,src2_qval);

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// sint,xsint,sint  SSUB  000 1111
DE_FUNC(LUnit,de_32bit_1or2_src,ssub_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = ssub(src1_val,src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// scst5, xsint, sint  SSUB  001 1111
DE_FUNC(LUnit,de_32bit_1or2_src,ssub_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = ssub(src1_val,src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// xsint,slong,slong  SSUB  000 1110
// src1 use xpath
DE_FUNC(LUnit,de_32bit_1or2_src,ssub_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  qword_t dst_qval = ssub_u40(src1_val,src2_qval);
  word_t dst_val,dst2_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// scst5,slong,slong  SSUB  010 1100
DE_FUNC(LUnit,de_32bit_1or2_src,ssub_f4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  qword_t dst_qval = ssub_u40(src1_val,src2_qval);
  word_t dst_val,dst2_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// slong,sint  SAT  100 0000
DE_FUNC(LUnit,de_32bit_1or2_src,sat)
{
  DE_CONDITION(core,cregz);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  word_t dst_val = sat(src2_qval);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_1or2_src,abs_slong)
{
  DE_CONDITION(core,cregz);

  qword_t src2_qval,dst_qval;
  sqword_t src2_sqval;
  if(src2 & 0x1)
  {
    core->panic("<Error>ABS.L odd register id in reg pair");
  }
  src2_qval = core->reg_read_long(side,src2);
  src2_sqval = (sqword_t)get_sign_ext_long(src2_qval,0,40); // slong 40
  if(src2_sqval <= 0) // == change to  <=
  {
    dst_qval = -src2_sqval;
  }
  else
  {
    dst_qval = src2_qval;
  }

  DE_UPDATE_REG2(side,dst,dst_qval);
}

#define LU_DE_32BIT_1OR2_SRC_SUB_FMT1_BODY() \
  word_t src1_val = core->reg_read(side,src1); \
  word_t src2_val = core->reg_read(xside,src2); \
  word_t dst_val = src1_val - src2_val; \
  core->push_reg_ch(side,dst,dst_val);

// sint,xsint,sint  SUB  000 0111
DE_FUNC(LUnit,de_32bit_1or2_src,sub_f1_nc)
{
  NO_CONDITION();
  LU_DE_32BIT_1OR2_SRC_SUB_FMT1_BODY();
}

DE_FUNC(LUnit,de_32bit_1or2_src,sub_f1_z0)
{
  DE_CONDITION_Z0(core);
  LU_DE_32BIT_1OR2_SRC_SUB_FMT1_BODY();
}

DE_FUNC(LUnit,de_32bit_1or2_src,sub_f1_z1)
{
  DE_CONDITION_Z1(core);
  LU_DE_32BIT_1OR2_SRC_SUB_FMT1_BODY();
}

// xsint,sint,sint  SUB  001 0111
// src1 xpath
DE_FUNC(LUnit,de_32bit_1or2_src,sub_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  word_t src2_val = core->reg_read(side,src2);
  word_t dst_val = (long)src1_val - (long)src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// sint,xsint,slong  SUB  010 0111
DE_FUNC(LUnit,de_32bit_1or2_src,sub_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval = (long)src1_val - (long)src2_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// xsint,sint,slong  SUB  011 0111
// src1 xpath
DE_FUNC(LUnit,de_32bit_1or2_src,sub_f4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  word_t src2_val = core->reg_read(side,src2);
  qword_t dst_qval = (long)src1_val - (long)src2_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// scst5,xsint,sint  SUB  000 0110
DE_FUNC(LUnit,de_32bit_1or2_src,sub_f5)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = (long)src1_val - (long)src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// scst5,slong,slong  SUB  010 0100
DE_FUNC(LUnit,de_32bit_1or2_src,sub_f6)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  qword_t src2_qval = core->reg_read_long(xside,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  qword_t dst_qval = (long)src1_val - (sqword_t)src2_qval;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// sint, xsint, sint ADD  000 0011
DE_FUNC(LUnit,de_32bit_1or2_src,add_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// sint, xsint, sint ADD  000 0011
DE_FUNC(LUnit,de_32bit_1or2_src,add_f1_nc)
{
  NO_CONDITION();
  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// sint, xsint, slong ADD  010 0011
DE_FUNC(LUnit,de_32bit_1or2_src,add_f2_nc)
{
  NO_CONDITION();

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval = src1_val + src2_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

DE_FUNC(LUnit,de_32bit_1or2_src,add_f2_z0)
{
  DE_CONDITION_Z0(core);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval = src1_val + src2_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

DE_FUNC(LUnit,de_32bit_1or2_src,add_f2_z1)
{
  DE_CONDITION_Z1(core);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval = src1_val + src2_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// xsint,slong,slong ADD  010 0001
// src1 xpath
DE_FUNC(LUnit,de_32bit_1or2_src,add_f3)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  qword_t dst_qval = (long)src1_val + (sqword_t)src2_qval;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// scst5,xsint,sint ADD 000 0010
DE_FUNC(LUnit,de_32bit_1or2_src,add_f4_nc)
{
  NO_CONDITION(core,cregz);

  //word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1 + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_1or2_src,add_f4_z0)
{
  DE_CONDITION_Z0(core);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1 + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_1or2_src,add_f4_z1)
{
  DE_CONDITION_Z1(core);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1 + src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// scst5,slong,slong ADD 010 0000
DE_FUNC(LUnit,de_32bit_1or2_src,add_f5)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  qword_t src2_qval = core->reg_read_long(xside,src2);
  src2_qval = get_sign_ext_long(src2_qval,0,40);
  qword_t dst_qval = (long)src1_val + (sqword_t)src2_qval;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// uint,xuint,ulong ADDU  010 1011
DE_FUNC(LUnit,de_32bit_1or2_src,addu_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval = src1_val + src2_val;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// xuint,ulong,ulong  ADDU  010 1001
// src1 xpath
DE_FUNC(LUnit,de_32bit_1or2_src,addu_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  qword_t src2_qval = core->reg_read_long(side,src2);
  qword_t dst_qval = src1_val + src2_qval;

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// i2,xi2,i2  ADD2  000 0101
DE_FUNC(LUnit,de_32bit_1or2_src,add2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_hi,a_lo,b_hi,b_lo,dst_hi,dst_lo;
  word_t dst_val;

  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_hi = (a_hi + b_hi) & 0xFFFF;
  dst_lo = (a_lo + b_lo) & 0xFFFF;
  dst_val = (dst_hi << 16) | dst_lo;

  core->push_reg_ch(side,dst,dst_val);
}

// i4,xi4,i4  ADD4  110 0101
DE_FUNC(LUnit,de_32bit_1or2_src,add4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_3,a_2,a_1,a_0;
  word_t b_3,b_2,b_1,b_0;
  word_t dst_3,dst_2,dst_1,dst_0;
  word_t dst_val;

  a_3 = get_sign_ext(src1_val,24,8);
  a_2 = get_sign_ext(src1_val,16,8);
  a_1 = get_sign_ext(src1_val,8,8);
  a_0 = get_sign_ext(src1_val,0,8);
  b_3 = get_sign_ext(src2_val,24,8);
  b_2 = get_sign_ext(src2_val,16,8);
  b_1 = get_sign_ext(src2_val,8,8);
  b_0 = get_sign_ext(src2_val,0,8);

  dst_3 = (a_3 + b_3) & 0xFF;
  dst_2 = (a_2 + b_2) & 0xFF;
  dst_1 = (a_1 + b_1) & 0xFF;
  dst_0 = (a_0 + b_0) & 0xFF;

  dst_val = (dst_3 << 24) | (dst_2 << 16) |
    (dst_1 << 8) | dst_0;
  core->push_reg_ch(side,dst,dst_val);
}

// uint,xuint,uint ANDN  111 1100
DE_FUNC(LUnit,de_32bit_1or2_src,andn)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val & (~src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// uint,xuint,uint  AND  111 1011
DE_FUNC(LUnit,de_32bit_1or2_src,and_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val & src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// scst5,xuint,uint  AND  111 1010
DE_FUNC(LUnit,de_32bit_1or2_src,and_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val & src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// u4,xu4,u4  SUBABS4  101 1010
DE_FUNC(LUnit,de_32bit_1or2_src,subabs4)
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

  dst_3 = labs(ua_3 - ub_3);
  dst_2 = labs(ua_2 - ub_2);
  dst_1 = labs(ua_1 - ub_1);
  dst_0 = labs(ua_0 - ub_0);

  dst_val = (dst_3 << 24) | (dst_2 << 16)
    | (dst_1 << 8) | dst_0;
  core->push_reg_ch(side,dst,dst_val);
}

// uint,xuint,uint  SUBC  100 1011
DE_FUNC(LUnit,de_32bit_1or2_src,subc)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = subc(src1_val,src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// i2,xi2,i2  SUB2  000 0100
DE_FUNC(LUnit,de_32bit_1or2_src,sub2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t a_hi,a_lo,b_hi,b_lo,dst_hi,dst_lo;
  word_t dst_val;

  a_hi = get_sign_ext_msb16(src1_val);
  a_lo = get_sign_ext_lsb16(src1_val);
  b_hi = get_sign_ext_msb16(src2_val);
  b_lo = get_sign_ext_lsb16(src2_val);

  dst_hi = (shalf_t)a_hi - (shalf_t)b_hi;
  dst_lo = (shalf_t)a_lo - (shalf_t)b_lo;
  dst_hi = dst_hi & 0xFFFF;
  dst_lo = dst_lo & 0xFFFF;
  dst_val = (dst_hi << 16) | dst_lo;
  core->push_reg_ch(side,dst,dst_val);
}

// i4,xi4,i4  SUB4  110 0110
DE_FUNC(LUnit,de_32bit_1or2_src,sub4)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = sub4(src1_val,src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

// uint,xuint,uint  XOR  110 1111
DE_FUNC(LUnit,de_32bit_1or2_src,xor_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val ^ src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// scst5,xuint,uint  XOR  110 1110
DE_FUNC(LUnit,de_32bit_1or2_src,xor_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val ^ src2_val;
  core->push_reg_ch(side,dst,dst_val);
}

// SUBU uint,xuint,ulong
DE_FUNC(LUnit,de_32bit_1or2_src,subu_f1)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  qword_t dst_qval = (qword_t)src1_val - (qword_t)src2_val;
  dst_qval &= 0xFFFFFFFFFF; // round 40bits

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// SUBU xuint,uint,ulong
DE_FUNC(LUnit,de_32bit_1or2_src,subu_f2)
{
  DE_CONDITION(core,cregz);

  word_t src1_val = core->reg_read(xside,src1);
  word_t src2_val = core->reg_read(side,src2);
  qword_t dst_qval = (qword_t)src1_val - (qword_t)src2_val;
  dst_qval &= 0xFFFFFFFFFF; // round 40bits

  DE_UPDATE_REG2(side,dst,dst_qval);
}

// Unary ABS always decode as 1or2 src inst format
// TODO: remove this function?
DE_FUNC(LUnit,de_32bit_unary,abs)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = labs(src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_unary,swap4)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = swap4(src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_unary,unpklu4)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = unpklu4(src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_unary,unpkhu4)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = unpkhu4(src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_unary,abs2)
{
  DE_CONDITION(core,cregz);

  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = abs2(src2_val);
  core->push_reg_ch(side,dst,dst_val);
}

DE_FUNC(LUnit,de_32bit_unary,mvk_nc)
{
  NO_CONDITION();

  //word_t dst_val = get_sign_ext_lsb5_quick(src2);
  core->push_reg_ch(side,dst,src2);
}

DE_FUNC(LUnit,de_32bit_unary,mvk_z0)
{
  DE_CONDITION_Z0(core);

  //word_t dst_val = get_sign_ext_lsb5_quick(src2);
  core->push_reg_ch(side,dst,src2);
}

DE_FUNC(LUnit,de_32bit_unary,mvk_z1)
{
  DE_CONDITION_Z1(core);

  //word_t dst_val = get_sign_ext_lsb5_quick(src2);
  core->push_reg_ch(side,dst,src2);
}

END_NS