
#include "core/inc/core.hpp"

USING_NS

//    31 29 28|27  23|22  18|17  13|12|11|10  6| 5 4 3 2 1 0
//    creg  z | dst  |src2  | src1 |x |0 | op  | 1 1 0 0 s p
//      3   1 | 5    | 5    | 5    |1 |  | 5   |         1 1
code_t generate_32bit_ext_compound_inst(word_t creg_z,
                                 word_t dst,
                                 word_t src2,
                                 word_t src1,
                                 word_t x,
                                 word_t op,
                                 word_t s,
                                 word_t p)
{
  code_t code = 0x30;
  code |= creg_z << 28;
  code |= dst << 23;
  code |= src2 << 18;
  code |= src1 << 13;
  code |= x << 12;
  code |= op << 6;
  code |= s << 1;
  code |= p;
  return code;
}

// 31 29 28|27 23|22 18|17 13|12|11 7|6 5 4 3 2 1 0
// creg z  |dst  |src2 |src1 |x |op  |0 0 0 0 0 s p
// 3    1  |5    |5    |5    |1 |5   |          1 1
code_t generate_32bit_mpy_inst(word_t creg_z,
                             word_t dst,
                             word_t src2,
                             word_t src1,
                             word_t x,
                             word_t op,
                             word_t side,
                             word_t p)
{
  code_t code = 0;
  code |= creg_z << 28;
  code |= dst << 23;
  code |= src2 << 18;
  code |= src1 << 13;
  code |= x << 12;
  code |= op << 7;
  code |= side << 1;
  code |= p;
  return code;
}

// 31 29 28|27  23|22  18|17  13|12| 11|  10 9 8 7 6 5 4 3 2 1 0
// creg  z |dst   |src2  |op    |x | 0 |   0 0 0 1 1 1 1 0 0 s p
// 3     1 |5     |5     |5     |1     |                     1 1
code_t generat_32bit_ext_unary_inst(word_t creg_z,
                               word_t dst,
                               word_t src2,
                               word_t op,
                               word_t x,
                               word_t s,
                               word_t p)
{
  code_t code = 0xF0;
  code |= creg_z << 28;
  code |= dst << 23;
  code |= src2 << 18;
  code |= op << 13;
  code |= x << 12;
  code |= s << 1;
  code |= p;
  return code;
}

void verif_mu_32bit_ext_compound(void)
{
  Core *core = Core::get();
  core->init();
  core->set_mode(UNIT_VERIF);
  
  word_t code;
  word_t nop = 0;
  word_t dst_val;

  //AVG2 .M1 A0,A1,A2
  code = generate_32bit_ext_compound_inst(0,2,1,0,0,0x13,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(A_SIDE,0,0x61984357);
  core->reg_write(A_SIDE,1,0x7582AE15);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0x6B8DF8B6);
  std::cout << "<M> pass A1: AVG2.M1 A0,A1,A2\n";

  //AVGU4 .M1 A0,A1,A2
  code = generate_32bit_ext_compound_inst(0,2,1,0,0,0x12,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(A_SIDE,0,0x1A2E5F4E);
  core->reg_write(A_SIDE,1,0x9EF26E3F);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0x5C906747);
  std::cout << "<M> pass A2: AVGU4.M1 A0,A1,A2\n";

  //DOTP2 .M1 A5,A6,A8
  code = generate_32bit_ext_compound_inst(0,8,6,5,0,0x0C,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(A_SIDE,5,0x6A321193);
  core->reg_write(A_SIDE,6,0xB1746CA4);
  core->reg_write(A_SIDE,8,0x4);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0xE6DFF6D4);
  std::cout << "<M> pass A3: DOTP2.M1 A5,A6,A8\n";

  //(L)DOTP2.M2      B5,B4,B5:B4
  code = 0x0210A2F2;
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,5,0x12343497);
  core->reg_write(B_SIDE,4,0x21ff50a7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0x12343497);
  assert(core->reg_read(B_SIDE,4) == 0x21ff50a7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0x12343497);
  assert(core->reg_read(B_SIDE,4) == 0x21ff50a7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0);
  assert(core->reg_read(B_SIDE,4) == 0x12FC544D);
  std::cout << "<M> pass A4: (Long)DOTP2.M2 B5,B4,B5:B4\n";

  //DOTPN2 .M1 A5,A6,A8
  code = generate_32bit_ext_compound_inst(0,8,6,5,0,0x09,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(A_SIDE,5,0x3629274A);
  core->reg_write(A_SIDE,6,0x325C8036);
  core->reg_write(A_SIDE,8,0x4);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x1E442F20);
  std::cout << "<M> pass A5: DOTPN2 .M1 A5,A6,A8\n";

  //DOTPNRSU2 .M1 A5, A6, A8
  code = generate_32bit_ext_compound_inst(0,8,6,5,0,0x07,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(A_SIDE,5,0x3629274A);
  core->reg_write(A_SIDE,6,0x325C8036);
  core->reg_write(A_SIDE,8,0x4);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0xFFFFF6FA);
  std::cout << "<M> pass A6: DOTPNRSU2 .M1 A5, A6, A8\n";

  //DOTPRSU2 .M1 A5, A6, A8
  code = generate_32bit_ext_compound_inst(0,8,6,5,0,0x0D,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(A_SIDE,5,0x3629274A);
  core->reg_write(A_SIDE,6,0x325C8036);
  core->reg_write(A_SIDE,8,0x4);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x00001E55);
  std::cout << "<M> pass A7: DOTPRSU2 .M1 A5, A6, A8\n";

  //DOTPSU4 .M1 A5, A6, A8
  code = generate_32bit_ext_compound_inst(0,8,6,5,0,0x02,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(A_SIDE,5,0x6A321193);
  core->reg_write(A_SIDE,6,0xB1746CA4);
  core->reg_write(A_SIDE,8,0x4);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x4);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,8) == 0x0000214A);
  std::cout << "<M> pass A8: DOTPSU4 .M1 A5, A6, A8\n";

  //MPYHI.M2      B5,B4,B5:B4
  code = 0x0210A532;
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,5,0x6A321193);
  core->reg_write(B_SIDE,4,0xB1746CA4);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0x6A321193);
  assert(core->reg_read(B_SIDE,4) == 0xB1746CA4);
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0x6A321193);
  assert(core->reg_read(B_SIDE,4) == 0xB1746CA4);
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0x6A321193);
  assert(core->reg_read(B_SIDE,4) == 0xB1746CA4);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0xFFFFDF6A);
  assert(core->reg_read(B_SIDE,4) == 0xDDB92008);
  std::cout << "<M> pass A10: MPYHI.M2      B5,B4,B5:B4\n";

  //MPYHIR .M2 B2,B5,B9
  code = generate_32bit_ext_compound_inst(0,9,5,2,0,0x10,B_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,2,0x12343497);
  core->reg_write(B_SIDE,5,0x21ff50a7);
  core->reg_write(B_SIDE,9,0x7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x04D5B710);
  std::cout << "<M> pass A11: MPYHIR .M2 B2,B5,B9\n";

  //MPYLI .M2 B2,B5,B9:B8
  code = generate_32bit_ext_compound_inst(0,8,5,2,0,0x15,B_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,2,0x12343497);
  core->reg_write(B_SIDE,5,0x21ff50a7);
  core->reg_write(B_SIDE,9,0x7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x000006FB);
  assert(core->reg_read(B_SIDE,8) == 0xE9FA7E81);
  std::cout << "<M> pass A12: MPYLI .M2 B2,B5,B9:B8\n";

  //MPYLIR .M2 B2,B5,B9
  code = generate_32bit_ext_compound_inst(0,9,5,2,0,0x0E,B_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,2,0x12343497);
  core->reg_write(B_SIDE,5,0x21ff50a7);
  core->reg_write(B_SIDE,9,0x7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x0DF7D3F5);
  std::cout << "<M> pass A13: MPYLIR .M2 B2,B5,B9\n";

  //MPYSU4 .M2 B5,B6,B9:B8
  code = generate_32bit_ext_compound_inst(0,8,6,5,0,0x05,B_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,5,0x3FF65010);
  core->reg_write(B_SIDE,6,0xC3560244);
  core->reg_write(B_SIDE,9,0x7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x2FFDFCA4);
  assert(core->reg_read(B_SIDE,8) == 0x00A00440);
  std::cout << "<M> pass A13: MPYSU4 .M2 B5,B6,B9:B8\n";

  //MPYU4 .M2 B2,B5,B9:B8
  code = generate_32bit_ext_compound_inst(0,8,5,2,0,0x04,B_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,2,0x3DE6507F);
  core->reg_write(B_SIDE,5,0xC3560244);
  core->reg_write(B_SIDE,9,0x7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x2E774D44);
  assert(core->reg_read(B_SIDE,8) == 0x00A021BC);
  std::cout << "<M> pass A14: MPYU4 .M2 B2,B5,B9:B8\n";

  //MPY2 .M2 B2, B5, B9:B8
  code = generate_32bit_ext_compound_inst(0,8,5,2,0,0x00,B_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,2,0x12343497);
  core->reg_write(B_SIDE,5,0x21FF50A7);
  core->reg_write(B_SIDE,9,0x7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,9) == 0x026AD5CC);
  assert(core->reg_read(B_SIDE,8) == 0x10917E81);
  std::cout << "<M> pass A15: MPY2 .M2 B2, B5, B9:B8\n";

  //ROTL .M2 B2(src2),B4,B5
  code = generate_32bit_ext_compound_inst(0,5,2,4,0,0x1D,B_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(B_SIDE,2,0xA6E2C179);
  core->reg_write(B_SIDE,4,0x14583B69);
  core->reg_write(B_SIDE,5,0x7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(B_SIDE,5) == 0xC582F34D);
  std::cout << "<M> pass A16: (REG)ROTL .M2 B2(src2),B4,B5\n";

  //ROTL .M1 A4,10h,A5
  code = generate_32bit_ext_compound_inst(0,5,4,0x10,0,0x1E,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->reg_write(A_SIDE,4,0x187A65FC);
  core->reg_write(A_SIDE,5,0x7);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(A_SIDE,5) == 0x7);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,5) == 0x65FC187A);
  std::cout << "<M> pass A17: ROTL .M1 A4,10h,A5\n";

  std::cout << "=====\n";
}

void verif_mu_32bit_ext_unary(void)
{
  Core *core = Core::get();
  core->init();
  core->set_mode(UNIT_VERIF);
  
  word_t code;
  word_t nop = 0;
  word_t dst_val;

  //BITC4 A3->A4
  code = generat_32bit_ext_unary_inst(0,4,3,0x1E,0,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->set_pc_e1(0x0);
  core->reg_write(A_SIDE,3,0xFF011122);
  core->reg_write(A_SIDE,4,1);
  core->step();
  assert(core->reg_read(A_SIDE,4) == 1);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,4) == 0x08010202);
  std::cout << "<M> pass B1: BITC4" << "\n";

  //BITR.M1X B3->A4
  code = generat_32bit_ext_unary_inst(0,4,3,0x1F,1,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->set_pc_e1(0x0);
  core->reg_write(B_SIDE,3,0x00FFFFFF);
  core->reg_write(A_SIDE,4,1);
  core->step();
  assert(core->reg_read(A_SIDE,4) == 1);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,4) == 0xFFFFFF00);
  std::cout << "<M> pass B2: BITR" << "\n";

  //DEAL.M1 A3->A4
  code = generat_32bit_ext_unary_inst(0,4,3,0x1D,0,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->set_pc_e1(0x0);
  core->reg_write(A_SIDE,3,0x12345678);
  core->reg_write(A_SIDE,4,1);
  core->step();
  assert(core->reg_read(A_SIDE,4) == 1);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,4) == 0x141646EC);
  std::cout << "<M> pass B3: DEAL" << "\n";

  //MVD.M1 A3->A4
  code = generat_32bit_ext_unary_inst(0,4,3,0x1A,0,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->get_l2()->mem_write_word_xendian(0x8,nop);
  core->get_l2()->mem_write_word_xendian(0xC,nop);
  core->set_pc_e1(0x0);
  core->reg_write(A_SIDE,3,0x12345678);
  core->reg_write(A_SIDE,4,1);
  core->step();
  assert(core->reg_read(A_SIDE,4) == 1);
  core->step();
  assert(core->reg_read(A_SIDE,4) == 1);
  core->step();
  assert(core->reg_read(A_SIDE,4) == 1);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,4) == 0x12345678);
  std::cout << "<M> pass B4: MVD" << "\n";

  //XPND2.M1 A3->A4
  code = generat_32bit_ext_unary_inst(0,4,3,0x19,0,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->set_pc_e1(0x0);
  core->reg_write(A_SIDE,3,0x00000002);
  core->reg_write(A_SIDE,4,1);
  core->step();
  assert(core->reg_read(A_SIDE,4) == 1);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,4) == 0xFFFF0000);
  std::cout << "<M> pass B5: XPND2" << "\n";

  //XPND4.M1 A3->A4
  code = generat_32bit_ext_unary_inst(0,4,3,0x18,0,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);
  core->set_pc_e1(0x0);
  core->reg_write(A_SIDE,3,0x00000009);
  core->reg_write(A_SIDE,4,1);
  core->step();
  assert(core->reg_read(A_SIDE,4) == 1);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,4) == 0xFF0000FF);
  std::cout << "<M> pass B6: XPND4" << "\n";

  std::cout << "=====\n";
}

void verif_mu_32bit_mpy(void)
{
  Core *core = Core::get();
  core->init();
  core->set_mode(UNIT_VERIF);
  
  word_t code;
  word_t nop = 0;
  word_t dst_val;

  //MPY.M1 2,A3,A3    |   0x018c4c
  code = generate_32bit_mpy_inst(0,3,3,2,0,0x18,0,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);

  core->reg_write(0,3,99); // A3 = 99;
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  dst_val = core->reg_read(0,3); // read A3
  assert(dst_val == 198);
  std::cout << "<M> pass C1: MPY cst5 | MPY.M1 2,A3,A3" << "\n";

  //MPY.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x19,0,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->get_l2()->mem_write_word_xendian(0x4,nop);

  core->reg_write(0,0,2); // A0 = 2;
  core->reg_write(0,1,0xFFFFFFFF); // A1 = -1;
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  dst_val = core->reg_read(0,2);
  assert((long)dst_val == -2);
  std::cout << "<M> pass C2: MPY slsb16[case 1] | MPY.M1 A0,A1,A2" << "\n";

  core->reg_write(0,1,0xFFFF); // A1 = 65535
  core->reg_write(A_SIDE,2,22);
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(A_SIDE,2) == 22);
  core->step();
  core->step();
  //A2 change
  assert(core->reg_read(A_SIDE,2) == 0xFFFFFFFE); // -2
  std::cout << "<M> pass C3: MPY slsb16[case 2] | MPY.M1 A0,A1,A2" << "\n";

  // MPYH.M2X B10,A10,B10  |  B10 = -1 * -1;
  code = generate_32bit_mpy_inst(0,10,10,10,1,0x1,B_SIDE,0);
  core->reg_write(A_SIDE,10,0xFFFF0000);
  core->reg_write(B_SIDE,10,0xFFFFFFFF);
  core->set_pc_e1(0x0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->step();
  core->step();
  core->step();

  assert(core->reg_read(B_SIDE,10) == 1);
  std::cout << "<M> pass C4: MPYH smsb16,xsmsb16 | MPYH.M2X B10,A10,B10" << "\n";
  
  // MPYHL.M1 A2,A2,A2 
  code = generate_32bit_mpy_inst(0,2,2,2,0,0x9,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,2,0x00050005); // A2 = 5;
  core->set_pc_e1(0x0);
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0x00050005);
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 25);
  std::cout << "<M> pass C5: MPYHL | MPYHL.M1 A2,A2,A2\n";

  // MPYHLU.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0xF,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0xFFFF0000); // umsb16(src1) = 0xFFFF
  core->reg_write(A_SIDE,1,0x8); // xulsb16(src2) = 0x8;
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0x7FFF8);
  std::cout << "<M> pass C6: MPYHLU | MPYHLU.M1 A0,A1,A2\n";

  // MPYHLU.M1 A0,A1,A2 case 2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0xF,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0xFFFF0000); 
  core->reg_write(A_SIDE,1,0xFFFF);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFE0001);
  std::cout << "<M> pass C7: MPYHLU(case 2) | MPYHLU.M1 A0,A1,A2\n";

  // MPYHSLU.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0xB,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0xFFFF0000);
  core->reg_write(A_SIDE,1,0xFFFF);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFF0001);
  std::cout << "<M> pass C8: MPYHSLU | MPYHSLU.M1 A0,A1,A2\n";

  // MPYHSU.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x3,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0xFFFF0000);
  core->reg_write(A_SIDE,1,0xFFFF0000);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFF0001);
  std::cout << "<M> pass C9: MPYHSU | MPYHSU.M1 A0,A1,A2\n";

  // MPYHU.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x7,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0xFFFF0000);
  core->reg_write(A_SIDE,1,0xFFFF0000);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFE0001);
  std::cout << "<M> pass C10: MPYHU | MPYHU.M1 A0,A1,A2\n";

  // MPYHULS.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0xD,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0x00010000);
  core->reg_write(A_SIDE,1,0xFFFF);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFFFFFF); // 1 * -1
  std::cout << "<M> pass C11: MPYHULS | MPYHULS.M1 A0,A1,A2\n";

  // MPYHUS.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x5,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0x00020000);
  core->reg_write(A_SIDE,1,0xFFFE0000);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFFFFFC); // 2 * -2
  std::cout << "<M> pass C12: MPYHUS | MPYHUS.M1 A0,A1,A2\n";

  // MPYLH.M1 A0,A1,A2 
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x11,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0xFFFE);  // -2
  core->reg_write(A_SIDE,1,0xFFFE0000); // -2
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0x4); // -2 * -2
  std::cout << "<M> pass C13: MPYLH | MPYLH.M1 A0,A1,A2\n";

  // MPYLSHU.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x13,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0xFFFE);  // -2
  core->reg_write(A_SIDE,1,0x00010000); // 1
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFFFFFE);
  std::cout << "<M> pass C14: MPYLSHU | MPYLSHU.M1 A0,A1,A2\n";

  // MPYLUHS.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x15,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0x0002);
  core->reg_write(A_SIDE,1,0x00030000);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0x6);
  std::cout << "<M> pass C15: MPYLUHS | MPYLUHS.M1 A0,A1,A2\n";

  // MPYLHU.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x17,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0x0002);
  core->reg_write(A_SIDE,1,0xFFFF0000);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0x1FFFE);
  std::cout << "<M> pass C16: MPYLHU | MPYLHU.M1 A0,A1,A2\n";

  // MPYSU.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x1B,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0xFFFF);
  core->reg_write(A_SIDE,1,0x0002);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFFFFFE);
  std::cout << "<M> pass C17: MPYSU | MPYSU.M1 A0,A1,A2\n";

  // MPYUS.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x1D,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0x0002);
  core->reg_write(A_SIDE,1,0xFFFF);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFFFFFE);
  std::cout << "<M> pass C18: MPYUS | MPYUS.M1 A0,A1,A2\n";

  // MPYU.M1 A0,A1,A2
  code = generate_32bit_mpy_inst(0,2,1,0,0,0x1F,A_SIDE,0);
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,0,0x0002);
  core->reg_write(A_SIDE,1,0x0008);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0x10);
  std::cout << "<M> pass C19: MPYU | MPYU.M1 A0,A1,A2\n";

  // MPYSU + scst5
  code = generate_32bit_mpy_inst(0,2,1,0x1F,0,0x1E,A_SIDE,0); // src1 = -1;
  core->get_l2()->mem_write_word_xendian(0x0,code);
  core->reg_write(A_SIDE,1,0x0001);
  core->set_pc_e1(0x0);
  core->step();
  core->step();
  core->step();
  assert(core->reg_read(A_SIDE,2) == 0xFFFFFFFF);
  std::cout << "<M> pass C20: MPYSU + scst5\n";

  std::cout << "=====\n";
}

void verif_m_unit(void)
{
  std::cout <<   "*********************************************************\n"
            <<   "************  start to verif M uint *********************\n"
            <<   "*********************************************************\n";

  verif_mu_32bit_ext_compound();
  verif_mu_32bit_ext_unary();
  verif_mu_32bit_mpy();

  std::cout <<   "*********************************************************\n"
            <<   "************  M uint verif OK!  *************************\n"
            <<   "*********************************************************\n";

  system("pause");
  //exit(0);
}