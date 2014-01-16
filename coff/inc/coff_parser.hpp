#ifndef COFF_PARSER_HPP
#define COFF_PARSER_HPP

#include <stdio.h>
#include <vector>
#include <fstream>
#include <map>
#include "common/inc/def.hpp"
#include "coff/inc/coff_def.hpp"
#include "coff/inc/dwarf_def.hpp"
#include "core/inc/core.hpp"

using namespace dwarf;

class COFF_parser
{
public:
  COFF_parser(const char* coff_path);
  void connect(c6x::Core* core);
  virtual ~COFF_parser();
  void parse();

  void set_reverse(bool bReverse)
  {
    m_bReverse = bReverse;
  }

private:
  void parse1();
  void parse2();
  void parse3();

  void finish();

  void read_debug_abbrev_raw_info(COFF_sectionHeader*);
  void read_debug_info_raw_info(COFF_sectionHeader*);
  void dwarf_parse_debug_info_section();

  void parse_header(COFF_header*,const char*);
  void parse_option_header(COFF_optionHeader*, const char*);
  void parse_section_header(COFF_sectionHeader*, const char*);
  void parse_symbol_entry(ST_entry*);

  void parse_char8_name(char*&,COFF_name& name);

  void parse_string_table();
  std::string parse_string_entry();

private:
  bool m_bReverse;
  char _header[COFF_HEADER_LEN + 1];
  char _optionHeader[COFF_OPTION_HEADER_LEN + 1];

  char *m_pcDebugInfoRaw;
  char *m_pcDebugAbbrevRaw;

  c6x::Core *m_pCore;

  COFF_sectionHeader *m_pSecDebugAbbrev;
  COFF_sectionHeader *m_pSecDebugInfo;

  FILE *m_pFIn;
  const char* m_pcFName;
  COFF_header *m_pCoffHeader;
  COFF_optionHeader *m_pCoffOptionHeader;

  int m_iBeginAddrOfStringTable;
  int m_iParsedSymbolEntries;
  std::ofstream *m_pofs;

  std::vector<COFF_sectionHeader*> m_vecSecHeaders;
  std::vector<ST_entry*> m_vecSTEntries;

  std::vector<std::string> m_vecStrTbl;
  std::map<c6x::qword_t,StringTable_entry*> m_mapStrTbl; // diff -> strTbl_entry

  dw_ab_map_t m_mapDwarfAbbrEntryMap; // addr -> AbbrevEntry*

  inline c6x::L2MemCtroller* get_l2()
  {
    if (NULL == m_pCore){
      return NULL;
    }
    return m_pCore->get_l2();
  } 
};

#endif