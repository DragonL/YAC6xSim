#ifndef CTRL_REGISTER_HPP
#define CTRL_REGISTER_HPP
#include "common/inc/def.hpp"

BEGIN_NS

typedef union
{
  struct
  {
    word_t GIE:1;
    word_t PGIE:1;
    word_t DCC:3;
    word_t PCC:3;
    word_t EN:1; // endian
    word_t SAT:1;
    word_t PWRD:6;
    word_t REVISION_ID:8;
    word_t CPUID:8;
  }csr_value;
  word_t u32_value;
} csr_data_t;

class CtrlRegister
{
public:
  typedef enum
  {
    R = 0,
    W,
    R_W,
    R_W_P,
    W_P
  }access_enum_t;  //  for Supervisor Mode only

private:
  unsigned long _value;
  const char* _name;
  unsigned long _crlo;
  unsigned long _crhi;
  access_enum_t _type;

public:
  CtrlRegister(const char* name,unsigned long crlo,unsigned long crhi,
    access_enum_t type): _name(name),_crlo(crlo),_crhi(crhi),_type(type),_value(0)
  {}

  inline unsigned long get_val()
  {
    return _value;
  }

  inline void set_val(unsigned long val)
  {
    _value = val;
  }

  inline unsigned long get_crhi()
  {
    return _crhi;
  }

  inline unsigned long get_crlo()
  {
    return _crlo;
  }

  inline const char *get_name()
  {
    return _name;
  }

  inline bool read_ok(void)
  {
    return (_type == access_enum_t::R) ||
      (_type == access_enum_t::R_W) ||
      (_type == access_enum_t::R_W_P);
  }

  inline bool write_ok(void)
  {
    return (_type == access_enum_t::W) ||
      (_type == access_enum_t::R_W) ||
      (_type == access_enum_t::R_W_P);
  }

  //TODO access right control
};


END_NS

#endif //CTRL_REGISTER_HPP