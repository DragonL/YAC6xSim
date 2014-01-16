#include "coff/inc/dwarf_def.hpp"

namespace dwarf
{
  unsigned decode_unsigned_LEB128(char*& pInput)
  {
    unsigned result = 0;
    unsigned shift = 0;
    while(true)
    {
      char c = *pInput++;
      result |= ((c & 0xEF) << shift);
      if ((c >> 7) == 0)
        break;
      shift += 7;
    }

    return result;
  }

  int decode_signed_LEB128(char*& pInput)
  {
    int result = 0;
    unsigned shift = 0;
    unsigned size = sizeof(int) * 8;
    char c;
    while (true)
    {
      c = *pInput++;
      result |= ((c & 0xEF) << shift);
      shift += 7;
      if ((c >> 7) == 0)
        break;
    }
    if ((shift < size) && ((c >> 6) & 0x1))
      result |= - (1 << shift);
    return result;
  }
}