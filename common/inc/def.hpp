#ifndef COMMON_DEF_HPP
#define COMMON_DEF_HPP

#include <assert.h>
#include <math.h>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <stdarg.h>

#include "common/inc/endian.hpp"

#define BEGIN_NS namespace c6x{
#define END_NS };
#define USING_NS using namespace c6x;

BEGIN_NS
//decode related
typedef unsigned int code_t;
typedef unsigned int uint;
typedef int sint;
typedef unsigned short compact_code_t;

//memory size
const uint _1K = 1024;
const uint _1M = _1K * _1K;
const uint _128M = 128 * _1M;

//class usage
#define ATTR_RW(type,attr)\
public:\
  type attr;\
public:\
  inline type& get_##attr(void)\
  {\
    return attr;\
  }\
  inline void set_##attr(type val)\
  {\
    attr = val;\
  }\


#define ATTR_R(type,attr)\
private:\
  type attr;\
public:\
  inline type& get_##attr(void)\
  {\
    return attr;\
  }\

#define BYTE_MASK(val) (val & 0xFF)

/* host-dependent canonical type definitions */
typedef int bool_t;			/* generic boolean type */
typedef unsigned char byte_t;		/* byte - 8 bits */
typedef signed char sbyte_t;
typedef unsigned short half_t;		/* half - 16 bits */
typedef signed short shalf_t;
typedef unsigned int word_t;		/* word - 32 bits */
typedef signed int sword_t;
typedef float sfloat_t;			/* single-precision float - 32 bits */
typedef double dfloat_t;		/* double-precision float - 64 bits */

#if defined(_MSC_VER)
#define HOST_HAS_QWORD
typedef unsigned __int64 qword_t;	/* qword - 64 bits */
typedef signed __int64 sqword_t;
#define ULL(N)		((qword_t)(N))
#define LL(N)		((sqword_t)(N))
#else /* !__GNUC__ && !__alpha */
#undef HOST_HAS_QWORD
#endif

/* statistical counter types, use largest counter type available */
#ifdef HOST_HAS_QWORD
typedef sqword_t counter_t;
typedef sqword_t tick_t;		/* NOTE: unsigned breaks caches */
#else /* !HOST_HAS_QWORD */
typedef dfloat_t counter_t;
typedef dfloat_t tick_t;
#endif /* HOST_HAS_QWORD */

/* define MD_QWORD_ADDRS if the target requires 64-bit (qword) addresses */
#undef MD_QWORD_ADDRS

/* address type definition */
typedef word_t md_addr_t;
typedef word_t* phy_addr_t;

typedef enum mem_type_t
{
  TYPE_U8 = 1,
  TYPE_U16,
  TYPE_U32,
  TYPE_U64,
  TYPE_U32N,
  TYPE_U64N
}mem_type_t;

typedef enum _unit_t
{
  UNIT_None = 0,
  UNIT_L1,
  UNIT_S1,
  UNIT_M1,
  UNIT_D1,
  UNIT_L2,
  UNIT_S2,
  UNIT_M2,
  UNIT_D2,
  UNIT_COMPACT_HEADER,
  UNIT_COMPILED_BB // compiled basic block form
}unit_t;

typedef enum _op_code_t
{
  OP_UNDEF = 0,
  
  OP_D_UNIT_32BIT_1_OR_2_SRC,
  OP_D_UNIT_32BIT_EXT_1_OR_2_SRC,     // FMT C-2
  OP_D_UNIT_32BIT_ADDAX_LONG_IMMED,   // c64x+
  OP_D_UNIT_32BIT_LK_WD,              // FMT C-4  c64x+
  OP_D_UNIT_32BIT_LD_ST_BASIC,        // FMT C-5
  OP_D_UNIT_32BIT_LD_ST_LONG_IMMED,
  OP_D_UNIT_32BIT_LD_ST_DW,  // OP_D_UNIT_32BIT_LD_ST_NON_ALIGN_DW
  //OP_D_UNIT_32BIT_LD_ST_NON_ALIGN_DW,
  OP_D_UNIT_16BIT_Doff4,
  OP_D_UNIT_16BIT_Doff4DW,
  OP_D_UNIT_16BIT_Dind,
  OP_D_UNIT_16BIT_DindDW,
  OP_D_UNIT_16BIT_Dinc,
  OP_D_UNIT_16BIT_DincDW,
  OP_D_UNIT_16BIT_Ddec,
  OP_D_UNIT_16BIT_DdecDW,
  OP_D_UNIT_16BIT_Dstk,
  OP_D_UNIT_16BIT_Dx2op,
  OP_D_UNIT_16BIT_Dx5,
  OP_D_UNIT_16BIT_Dx5p,
  OP_D_UNIT_16BIT_Dx1,
  OP_D_UNIT_16BIT_Dpp,

  OP_L_UNIT_32BIT_1_OR_2_SRC,
  OP_L_UNIT_32BIT_UNARY,
  OP_L_UNIT_32BIT_1_OR_2_SRC_NON_COND,
  OP_L_UNIT_16BIT_L3,
  OP_L_UNIT_16BIT_L3i,
  OP_L_UNIT_16BIT_Ltbd,
  OP_L_UNIT_16BIT_L2c,
  OP_L_UNIT_16BIT_Lx5,
  OP_L_UNIT_16BIT_Lx3c,
  OP_L_UNIT_16BIT_Lx1c,
  OP_L_UNIT_16BIT_Lx1,

  OP_M_UNIT_32BIT_EXT_COMPOUND,
  OP_M_UNIT_32BIT_EXT_UNARY,
  OP_M_UNIT_32BIT_EXT_1_OR_2_SRC_NON_COND,
  OP_M_UNIT_32BIT_MPY,
  OP_M_UNIT_16BIT_M3,
  
  OP_S_UNIT_32BIT_1_OR_2_SRC,              // FMT-1
  OP_S_UNIT_32BIT_ADDK,
  OP_S_UNIT_32BIT_ADDKPC,
  OP_S_UNIT_32BIT_EXT_1_OR_2_SRC,
  OP_S_UNIT_32BIT_B_DISP,
  OP_S_UNIT_32BIT_B_REG,                   // FMT-6
  OP_S_UNIT_32BIT_B_PTR,
  OP_S_UNIT_32BIT_BDEC_OR_BPOS,  // FMT-8
  OP_S_UNIT_32BIT_BNOP_DISP,
  OP_S_UNIT_32BIT_BNOP_REG,
  OP_S_UNIT_32BIT_CALL_NON_COND_IMMED_NOP5,
  OP_S_UNIT_32BIT_MVK_MVKH,               // FMT-12
  OP_S_UNIT_32BIT_EXT_1_OR_2_SRC_NON_COND,
  OP_S_UNIT_32BIT_UNARY,
  OP_S_UNIT_32BIT_FIELD_OP,
  OP_S_UNIT_16BIT_Sbs7,
  OP_S_UNIT_16BIT_Sbu8,
  OP_S_UNIT_16BIT_Scs10,
  OP_S_UNIT_16BIT_Sbs7c,
  OP_S_UNIT_16BIT_Sbu8c,
  OP_S_UNIT_16BIT_S3,
  OP_S_UNIT_16BIT_S3i,
  OP_S_UNIT_16BIT_Smvk8,
  OP_S_UNIT_16BIT_Ssh5,
  OP_S_UNIT_16BIT_S2sh,
  OP_S_UNIT_16BIT_Sc5,
  OP_S_UNIT_16BIT_S2ext,
  OP_S_UNIT_16BIT_Sx2op,
  OP_S_UNIT_16BIT_Sx5,
  OP_S_UNIT_16BIT_Sx1,
  OP_S_UNIT_16BIT_Sx1b,
  
  OP_LSD_UNIT_16BIT_LSDmvto,
  OP_LSD_UNIT_16BIT_LSDmvfr,
  OP_LSD_UNIT_16BIT_LSDx1c,
  OP_LSD_UNIT_16BIT_LSDx1,

  OP_N_UNIT_32BIT_DINT_RINT_SWE_SWENR,
  OP_N_UNIT_32BIT_IDLE_NOP,                 // FMT H-2
  OP_N_UNIT_32BIT_LOOP_BUF_NON_COND,
  OP_N_UNIT_32BIT_LOOP_BUF,
  OP_N_UNIT_16BIT_Uspl,
  OP_N_UNIT_16BIT_Uspldr,
  OP_N_UNIT_16BIT_Uspk,
  OP_N_UNIT_16BIT_Uspm,
  OP_N_UNIT_16BIT_Unop
}op_code_t;

class Core;
class Instruction;
#ifdef DE_FUNC_FASTCALL
#define DE_FUNC_CALL_TYPE __fastcall
#else
#define DE_FUNC_CALL_TYPE
#endif
typedef void (DE_FUNC_CALL_TYPE* de_func_t)(Core* core,Instruction* inst);

typedef void (*jit_func_t)(void);

extern const char* op_type_name_map[];
extern const char* unit_type_name_map[];

inline uint get_sign_ext(code_t code, int start, int len);
inline qword_t get_sign_ext_long(qword_t qval,int start,int len);
inline qword_t get_ulong(qword_t ul,int start,int len);
inline word_t extu(word_t src, int csta, int cstb);
inline word_t get_sign_ext_msb16(word_t code);
inline word_t get_sign_ext_lsb16(word_t code);

inline code_t mask(int len)
{
  /*
  code_t m = 0;
  while(len-- > 0)
  {
    m |= (1 << len);
  }
  return m;
  */
  return ((1 << len) - 1);
}

inline qword_t mask_ll(int len)
{
  qword_t m = 0;
  while(len-- > 0)
  {
    m |= ((qword_t)1 << len);
  }
  return m;
}

inline bool next_parallel_p(code_t code)
{
  return code & 0x1;
}

// test code is for side A(true) or side B(false)
inline bool side_a_p(word_t code)
{
  return (code >> 1) & 0x1;
}

#define BIT_TEST(code,pos) (code & (1 << pos))

inline word_t get_uint(word_t code, int start, int len)
{
  return extu(code,32-start-len,32-len);
}

/*
#define get_uint(code,start,len) \
  ((code >> start) & ((1 << len) - 1))
*/

inline word_t get_lsb16(word_t code)
{
  return code & 0xFFFF;
}

inline word_t get_msb16(word_t code)
{
  return code >> 16;
}

inline word_t shr(word_t src,int len)
{
  assert(len < 32);
  word_t re = src >> len;
  re = get_sign_ext(re,0,32 - len);
  return re;
}

inline qword_t shr_u40(qword_t src,int len)
{
  assert(len <= 40);
  src = src & 0xFFFFFFFFFF;
  qword_t re = src >> len;

  // xxx this is wrong...
  //re = get_sign_ext_long(re,0,40 - len);

  //re = get_ulong(re,0,40);
  return re;
}

inline word_t clr(word_t src, int csta, int cstb)
{
  assert(cstb >= csta);
  word_t bit_mask = (1 << csta);
  word_t mask = 0;

  for(uint i = 0; i < (cstb - csta + 1); ++i)
  {
    mask |= bit_mask;
    bit_mask <<= 1;
  }

  return (src & ~mask);
}

inline word_t set(word_t src, int csta, int cstb)
{
  assert(cstb >= csta);
  word_t bit_mask = (1 << csta);
  word_t mask = 0;

  for(uint i = 0; i < (cstb - csta + 1); ++i)
  {
    mask |= bit_mask;
    bit_mask <<= 1;
  }

  return (src | mask);
}

inline word_t extu(word_t src, int csta, int cstb)
{
  return (src << csta) >> cstb;
}

inline word_t ext(word_t src, int csta, int cstb)
{
  word_t re =  (src << csta) >> cstb;
  return get_sign_ext(re,0,32 - cstb);
}

inline word_t subc(word_t src1,word_t src2)
{
  word_t dst;
  if(src1 >= src2)
  {
    dst = ((src1 - src2) << 1) + 1;
  }
  else
  {
    dst = src1 << 1;
  }
  return dst;
}

inline code_t get_mask_code(code_t code, int len){
  code_t m = mask(len);
  return code & m;
}

inline bool bit_test(code_t val, code_t bit){
  code_t bit_mask = 1;
  if (bit > 0){
    bit_mask <<= bit;
  }
  return (val & bit_mask) != 0;
}

inline sint get_sint(code_t code, int start, int len){
  uint u = get_uint(code,start,len);
  uint sign_bit = 1 << (len-1);
  uint mask2 = sign_bit - 1;
  uint mask1 = sign_bit | mask2;
  sint s = u;
  if ((u & sign_bit) != 0){
    s = 0 - ( ((u ^ mask1) + 1));
  }
  return s;
}

inline qword_t get_ulong(qword_t ul,int start,int len)
{
  qword_t tmp = ul >> start;

  return tmp & mask_ll(len);
}

inline uint bit_count(uint src, int len)
{
  uint mask = 0x1;
  uint count = 0;
  for(uint i = 0; i < len; ++i)
  {
    if(src & mask)
      count++;
    mask <<= 1;
  }
  return count;
}

inline uint bit_reverse(uint src)
{
  uint dst = 0;
  uint mask_src = 0x1;
  uint bit_dst;
  for(uint i = 0; i < 32; ++i)
  {
    if(src & mask_src)
    {
      dst |= 1 << (32 -i -1);
    }
    mask_src <<= 1;
  }
  return dst;
}

inline uint shfl(uint src)
{
  word_t mask_hi = 0x80000000;
  word_t mask_lo = 0x8000;
  word_t re = 0;
  for(word_t i = 0; i < 16;++i)
  {
    re |= (src & mask_hi) >> i;
    re |= (src & mask_lo) << (15 - i);
    mask_hi >>= 1;
    mask_lo >>= 1;
  }
  return re;
}

inline uint deinterleave(uint src)
{
  uint mask = 0x1;
  uint bit_dst = 0x1;
  uint dst = 0;
  uint bit_shift = 0;
  for(uint i = 0; i < 32; i+=2)
  { // even bits 0,2,...
    dst |= ((src & mask) != 0) << bit_shift;
    bit_shift++;
    mask <<= 2;
  }
  mask = 0x2;
  for(uint i = 1; i < 32; i+=2)
  { // odd bits 1,3,...
    dst |= ((src & mask) != 0) << bit_shift;
    bit_shift++;
    mask <<= 2;
  }
  return dst;
}

inline uint xpnd2(uint src)
{
  uint dst = 0;
  if(src & 0x1)
  {
    dst |= 0xFFFF;
  }
  if(src & 0x2)
  {
    dst |= 0xFFFF0000;
  }
  return dst;
}

inline uint xpnd4(uint src)
{
  uint dst = 0;
  if(src & 0x1)
  {
    dst |= 0xFF;
  }
  if(src & 0x2)
  {
    dst |= 0xFF00;
  }
  if(src & 0x4)
  {
    dst |= 0xFF0000;
  }
  if(src & 0x8)
  {
    dst |= 0xFF000000;
  }
  return dst;
}

inline word_t sub4(word_t src1,word_t src2)
{
  word_t ua_3,ua_2,ua_1,ua_0;
  word_t ub_3,ub_2,ub_1,ub_0;
  word_t dst_3,dst_2,dst_1,dst_0;
  word_t re;

  ua_3 = get_sign_ext(src1,24,8);
  ua_2 = get_sign_ext(src1,16,8);
  ua_1 = get_sign_ext(src1,8,8);
  ua_0 = get_sign_ext(src1,0,8);
  ub_3 = get_sign_ext(src2,24,8);
  ub_2 = get_sign_ext(src2,16,8);
  ub_1 = get_sign_ext(src2,8,8);
  ub_0 = get_sign_ext(src2,0,8);

  dst_3 = (ua_3 - ub_3) & 0xFF;
  dst_2 = (ua_2 - ub_2) & 0xFF;
  dst_1 = (ua_1 - ub_1) & 0xFF;
  dst_0 = (ua_0 - ub_0) & 0xFF;

  re = (dst_3 << 24) | (dst_2 << 16) |
    (dst_1 << 8) | dst_0;
  return re;
}

inline word_t abs2(word_t src)
{
  shalf_t hi,lo;
  word_t dst_hi,dst_lo;
  hi = get_sign_ext_msb16(src);
  lo = get_sign_ext_lsb16(src);

  if(hi > 0 && hi <= 0x7FFF)
  {
    dst_hi = hi;
  }
  else if(hi == -0x8000)
  {
    dst_hi = 0x7FFF;
  }
  else
  {
    dst_hi = -hi;
  }

  if(lo > 0 && lo <= 0x7FFF)
  {
    dst_lo = lo;
  }
  else if(lo == -0x8000)
  {
    dst_lo = 0x7FFF;
  }
  else
  {
    dst_lo = -lo;
  }

  return ((dst_hi << 16) | dst_lo);
}

// code should less than 0x20
inline word_t get_sign_ext_lsb5_quick(word_t code)
{
  return (0x10 & code) ? (code | 0xFFFFFFE0) : code;
}

inline word_t get_sign_ext_lsb5(word_t code)
{
  if(0x10 & code)
  {
    return (code & 0x1F) | 0xFFFFFFE0;
  }
  else
  {
    return code & 0x1F;
  }
}

inline word_t get_sign_ext_lsb16(word_t code)
{
  word_t lsb = code & 0xFFFF;

  if(0x8000 & lsb)
  {
    return lsb | 0xFFFF0000;
  }
  else
  {
    return lsb;
  }
  /*
  half_t ext_lsb = (half_t)lsb;
  return ext_lsb;
  */
}

inline word_t get_sign_ext_msb16(word_t code)
{
  word_t msb = code >> 16;
  if(0x8000 & msb)
  {
    return msb | 0xFFFF0000;
  }
  else
  {
    return msb;
  }
  /*
  half_t ext_msb = (half_t)msb;
  return ext_msb;
  */
}

inline uint get_sign_ext(code_t code, int start, int len)
{
  uint u = get_uint(code,start,len);
  uint sign_bit = 1 << (len-1);
  uint mask2 = sign_bit - 1;
  uint mask1 = sign_bit | mask2;
  uint ext_mask = (mask1 ^ 0xFFFFFFFF);
  uint re = u;
  if (re & sign_bit)
  {
    re = re | ext_mask;
  }
  return re;
}

const int SINT16_MIN = 0x8000;
const int SINT16_MAX = 0x7FFF;
const int SINT32_MIN = 0x80000000;
const int SINT32_MAX = 0x7FFFFFFF;
const sqword_t SINT40_MIN = -0x8000000000;
const sqword_t SINT40_MAX = 0x7FFFFFFFFF;

inline sword_t sadd(sword_t src1, sword_t src2)
{
  sqword_t re = (sqword_t)src1 + (sqword_t)src2;
  if(re < SINT32_MIN)
    return SINT32_MIN;
  if(re > SINT32_MAX)
    return SINT32_MAX;
  return re;
}

inline word_t swap4(word_t src)
{
  word_t tmp1,tmp2;
  tmp1 = src & 0xFF00FF00;
  tmp2 = src & 0x00FF00FF;
  tmp1 >>= 8;
  tmp2 <<= 8;
  return (tmp1 | tmp2);
}

inline word_t unpkhu4(word_t src)
{
  return ((src & 0xFF000000) >> 8)| ((src & 0x00FF0000) >> 16);
}

inline word_t unpklu4(word_t src)
{
  return ((src & 0x0000FF00) << 8)| (src & 0x000000FF);
}

inline qword_t sadd_u40(qword_t src1,qword_t src2)
{
  sqword_t re = (sqword_t)src1 + (sqword_t)src2;
  if(re < SINT40_MIN)
    return SINT40_MIN;
  if(re > SINT40_MAX)
    return SINT40_MAX;
  return re;
}

inline sword_t ssub(sword_t src1, sword_t src2)
{
  sqword_t re = (sqword_t)src1 - (sqword_t)src2;
  if(re < SINT32_MIN)
    return SINT32_MIN;
  if(re > SINT32_MAX)
    return SINT32_MAX;
  return re;
}

inline qword_t ssub_u40(qword_t src1,qword_t src2)
{
  sqword_t re = (sqword_t)src1 - (sqword_t)src2;
  if(re < SINT40_MIN)
    return SINT40_MIN;
  if(re > SINT40_MAX)
    return SINT40_MAX;
  return re;
}

inline sword_t sat(sqword_t src2)
{
  if(src2 < SINT32_MIN)
    return SINT32_MIN;
  if(src2 > SINT32_MAX)
    return SINT32_MAX;
  return src2;
}

inline shalf_t sat16(shalf_t src2)
{
  if(src2 < SINT16_MIN)
    return SINT16_MIN;
  if(src2 > SINT16_MAX)
    return SINT16_MAX;
  return src2;
}

inline byte_t satu8(word_t src)
{
  if(src > 0xFF)
    return 0xFF;
  return src;
}

inline word_t sshl(word_t src1, word_t src2)
{
  word_t mask= 0x80000000;
  word_t test_mask = 0;
  word_t test_val = 0;
  for(word_t i = 0; i <= src1 ; ++i)
  {
    test_mask |= mask;
    test_val |= (src2 & mask);
    mask >>= 1;
  }

  // bit31 ~ bit(31 - src1) all 0s
  if(test_val == 0)
  {
    return src2 << src1;
  }

  // bit31 ~ bit(31 - src1) all 1s
  if(test_val == test_mask)
  {
    return src2 << src1;
  }

  // other
  if((long)src2 > 0)
  {
    return 0x7FFFFFFF;
  }

  return 0x80000000;
}

inline word_t shlmb(word_t src1,word_t src2)
{
  word_t re;
  re = (src2 << 8);
  re |= (src1 >> 24);
  return re;
} 

inline word_t shrmb(word_t src1,word_t src2)
{
  word_t re;
  re = src2 >> 8;
  re |= (src1 << 24);
  return re;
} 

inline uint lmbd(word_t src,word_t test_bit)
{
  uint pos = 0;
  uint mask = 0x80000000;
  uint bit;
  for(uint i = 0; i < 32; ++i)
  {
    bit = ( (src & mask) != 0);
    if(bit == test_bit) // find
    {
      break;
    }
    mask = (mask >> 1);
    pos++;
  }
  return pos;
}

inline uint rmbd(word_t src, word_t test_bit)
{
  uint pos = 0;
  uint mask = 0x00000001;
  uint bit;
  for(uint i = 0; i < 32; ++i)
  {
    bit = ( (src & mask) != 0);
    if(bit == test_bit) // find
    {
      break;
    }
    mask = (mask << 1);
    pos++;
  }
  return pos;
}

inline uint norm(word_t src)
{
  uint sign_bit_num = 0;
  uint mask = 0x80000000;
  uint sign_bit = ((src & mask) != 0);
  uint bit;
  for(uint i = 0; i < 32; ++i)
  {
    bit = ((src & mask) != 0);
    if(bit != sign_bit)
      break;
    sign_bit_num++;
    mask = (mask >> 1);
  }
  return sign_bit_num - 1;
}

//TODO: test is
inline uint norm_u40(qword_t src)
{
  uint sign_bit_num = 0;
  //qword_t mask = 0x8000000000000000;
  qword_t mask = 0x8000000000;
  uint sign_bit = ((src & mask) != 0);
  uint bit;
  for(uint i = 0; i < 40; ++i)
  {
    bit = ((src & mask) != 0);
    if(bit != sign_bit)
      break;
    sign_bit_num++;
    mask = (mask >> 1);
  }
  return sign_bit_num - 1;
}

inline qword_t get_sign_ext_long(qword_t qval,int start,int len)
{
  qword_t qu = get_ulong(qval,start,len);
  //xxx 1 should change to qword_t type
  qword_t sign_bit = (qword_t)1 << (len-1);
  qword_t mask2 = sign_bit - 1;
  qword_t mask1 = sign_bit | mask2;
  qword_t ext_mask = (mask1 ^ 0xFFFFFFFFFFFFFFFF);
  qword_t re = qu;
  if(re & sign_bit)
  {
    re |= ext_mask; 
  }
  return re;
}

inline bool is_reg_even(word_t reg)
{
  return ((reg % 2) == 0);
}

template <class T>
inline T max(T left, T right)
{
  if(left > right)
    return left;
  return right;
}

template <class T>
inline T min(T left, T right)
{
  if(left < right)
    return left;
  return right;
}

// misc
template <class T>
inline std::string to_hex_str(T val)
{
  static char buf[256];
  sprintf_s(buf,256,"0x%08x",val);
  return std::string(buf);
}

template <class T>
inline std::string to_yes_or_no(T val)
{
  if(val != 0)
  {
    return std::string("yes");
  }
  else
  {
    return std::string("no");
  }
}


template <>
inline std::string to_hex_str(qword_t val)
{
  static char buf[256];
  sprintf_s(buf,256,"0x%08x %08x",(word_t)(val >> 32), (word_t)(val & 0xFFFFFFFF));
  return std::string(buf);
}

inline std::string to_bin_str(code_t code)
{
  int len = 32;
  std::stringstream ss;
  while(len-- > 0){
    int tmp = ((code & 0x80000000) == 0x80000000);
    ss << tmp;
    code <<= 1;
  }
  return ss.str();
}

enum md_fault_type 
{
  md_fault_none = 0,		/* no fault */
  md_fault_access,		/* storage access fault */
  md_fault_alignment,		/* storage alignment fault */
  md_fault_overflow,		/* signed arithmetic overflow fault */
  md_fault_div0,		/* division by zero fault */
  md_fault_break,		/* BREAK instruction fault */
  md_fault_unimpl,		/* unimplemented instruction fault */
  md_fault_internal		/* internal S/W fault */
};

/* data swapping functions, from big/little to little/big endian format */
#define SWAP_HALF(X)							\
  (((((half_t)(X)) & 0xff) << 8) | ((((half_t)(X)) & 0xff00) >> 8))
#define SWAP_WORD(X)	(((word_t)(X) << 24) |				\
  (((word_t)(X) << 8)  & 0x00ff0000) |		\
  (((word_t)(X) >> 8)  & 0x0000ff00) |		\
  (((word_t)(X) >> 24) & 0x000000ff))
#define SWAP_QWORD(X)	(((qword_t)(X) << 56) |				\
  (((qword_t)(X) << 40) & ULL(0x00ff000000000000)) |\
  (((qword_t)(X) << 24) & ULL(0x0000ff0000000000)) |\
  (((qword_t)(X) << 8)  & ULL(0x000000ff00000000)) |\
  (((qword_t)(X) >> 8)  & ULL(0x00000000ff000000)) |\
  (((qword_t)(X) >> 24) & ULL(0x0000000000ff0000)) |\
  (((qword_t)(X) >> 40) & ULL(0x000000000000ff00)) |\
  (((qword_t)(X) >> 56) & ULL(0x00000000000000ff)))

/* target swap support */
#ifdef MD_CROSS_ENDIAN

#ifdef _WIN32
#define MD_SWAPH(X)		_byteswap_ushort(X)
#define MD_SWAPW(X)   _byteswap_ulong(X)
#define MD_SWAPQ(X)		_byteswap_uint64(X)
#define MD_SWAPI(X)		_byteswap_ulong(X)
#else
#define MD_SWAPH(X)		SWAP_HALF(X)
#define MD_SWAPW(X)		SWAP_WORD(X)
#define MD_SWAPQ(X)		SWAP_QWORD(X)
#define MD_SWAPI(X)		SWAP_WORD(X)
#endif

inline word_t swapw(register word_t w)
{
  __asm
  {
    mov eax,w;
    bswap eax;
  }
}

#else /* !MD_CROSS_ENDIAN */

#define MD_SWAPH(X)		(X)
#define MD_SWAPW(X)		(X)
#define MD_SWAPQ(X)		(X)
#define MD_SWAPD(X)		(X)
#define MD_SWAPI(X)		(X)

#endif

#ifdef __GNUC__
/* declare a fatal run-time error, calls fatal hook function */
#define fatal(fmt, args...)	\
  _fatal(__FILE__, __FUNCTION__, __LINE__, fmt, ## args)

void
_fatal(char *file, const char *func, int line, char *fmt, ...)
__attribute__ ((noreturn));
#else /* !__GNUC__ */
void
fatal(char *fmt, ...);
#endif /* !__GNUC__ */

/* portable 64-bit I/O package */

/* portable vsprintf with qword support, returns end pointer */
char *myvsprintf(char *obuf, char *format, va_list v);

/* portable sprintf with qword support, returns end pointer */
char *mysprintf(char *obuf, char *format, ...);

/* portable vfprintf with qword support, returns end pointer */
void myvfprintf(FILE *stream, char *format, va_list v);

END_NS

#endif