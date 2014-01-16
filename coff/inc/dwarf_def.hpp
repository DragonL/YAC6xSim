#ifndef DWARF_DEF_HPP
#define DWARF_DEF_HPP

#include <vector>
#include <string>
#include <map>

namespace dwarf
{
  unsigned decode_unsigned_LEB128(char*& pInput);
  int decode_signed_LEB128(char*& pInput);

  typedef struct dw_at_t
  {
    unsigned name;
    unsigned format;
    inline bool isNull()
    {
      return (name == 0 && format == 0);
    }
  }dw_at_t;

  typedef std::vector<dw_at_t> dw_at_lst_t;
  

  class AbbrevEntry;
  class DebugEntry;
  typedef std::map<int,AbbrevEntry*> dw_ab_map_t;

  class AbbrevEntry
  {
  public:
    AbbrevEntry *nextSibling;
    AbbrevEntry *firstChild;
    AbbrevEntry *parent;
    unsigned entryCode;
    unsigned entryTag;
    bool     hasChildren;
    dw_at_lst_t    vecAttrType;

    AbbrevEntry():nextSibling(0),firstChild(0),parent(0){}

    std::string to_s();
  };

  class DebugEntry
  {
  public:
    DebugEntry *nextSibling;
    DebugEntry *firstChild;
    DebugEntry *parent;
    unsigned entryCode;
    unsigned entryTag;
    bool     hasChildren;

    // attr lst
  };
}

#endif