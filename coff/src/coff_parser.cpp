#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <assert.h>
#include <sstream>
#include <iostream>
#include <map>
#include "coff/inc/coff_parser.hpp"

USING_NS

COFF_parser::COFF_parser(const char *coff_path):m_iParsedSymbolEntries(0),
  m_pCore(NULL)
{
  m_pcFName = coff_path;
  m_pFIn = fopen(coff_path,"rb");
  assert(m_pFIn);

  //temp  output file
  m_pofs = new std::ofstream("o.txt");
  m_pofs->clear();
}

COFF_parser::~COFF_parser()
{
  if(m_pFIn != NULL)
  {
    fclose(m_pFIn);
  }
  if(m_pofs != NULL)
  {
    m_pofs->flush();
    m_pofs->close();
    delete m_pofs;
    m_pofs = NULL;
  }

  if (m_pcDebugInfoRaw != NULL)
  {
    delete [] m_pcDebugInfoRaw;
    m_pcDebugInfoRaw = NULL;
  }

  if (m_pcDebugAbbrevRaw != NULL)
  {
    delete [] m_pcDebugAbbrevRaw;
    m_pcDebugAbbrevRaw = NULL;
  }
}

void COFF_parser::parse_header(COFF_header* pHeader, const char* buf)
{ 
  char* pPos = (char*)buf; 
  pHeader->versionID = read_ushort(pPos, m_bReverse);
  pHeader->numOfSecHeaders = read_ushort(pPos, m_bReverse);
  pHeader->timeStamp = read_int(pPos, m_bReverse);
  pHeader->addressOfST = read_int(pPos, m_bReverse);
  pHeader->numOfEntryST = read_int(pPos, m_bReverse);
  pHeader->optionHeaderLen = read_ushort(pPos, m_bReverse);
  pHeader->flags = read_ushort(pPos, m_bReverse);
  pHeader->targetID = read_ushort(pPos, m_bReverse);
}

void COFF_parser::parse_option_header(COFF_optionHeader* pOptionHeader, const char* buf)
{
  char* pPos = (char*)buf;
  pOptionHeader->s0_1_magic = read_short(pPos, m_bReverse);
  pOptionHeader->s2_3_versionStamp = read_short(pPos, m_bReverse);
  pOptionHeader->i4_7_exeCodeSizeInBytes = read_int(pPos, m_bReverse);
  pOptionHeader->i8_11_initializedDataSizeInBytes = read_int(pPos, m_bReverse);
  pOptionHeader->i12_15_uninitializedDataSizeInBytes = read_int(pPos, m_bReverse);
  pOptionHeader->i16_19_entryPoint = read_int(pPos, m_bReverse);
  pOptionHeader->i20_23_beginningAddrOfExeCode = read_int(pPos, m_bReverse);
  pOptionHeader->i24_27_beginningAddrOfinitializedData = read_int(pPos, m_bReverse);

  if (NULL != m_pCore){
    m_pCore->set_entry_point(pOptionHeader->i16_19_entryPoint);
  }
}

void COFF_parser::parse_char8_name(char*& pAddress, COFF_name& name)
{
  char first_char = *pAddress;
  if (first_char)
  {
    read_buf(pAddress,name.n.c0_7_name,8);
    name.bShortName = true;
  }
  else
  {
    pAddress += 4;
    name.n.fp = read_int(pAddress, m_bReverse);
    name.bShortName = false;
  }
}

void COFF_parser::parse_section_header(COFF_sectionHeader* pSecHeader, const char* buf)
{
  char* pPos = (char*)buf;
  
  parse_char8_name(pPos,pSecHeader->name);
  pSecHeader->i8_11_physicalAddr = read_int(pPos, m_bReverse);
  pSecHeader->i12_15_virtualAddr = read_int(pPos, m_bReverse);
  pSecHeader->i16_19_size = read_int(pPos, m_bReverse);
  pSecHeader->i20_23_fpRawData = read_int(pPos, m_bReverse);
  pSecHeader->i24_27_fpRelocEntries = read_int(pPos, m_bReverse);
  pSecHeader->i28_31_reserved = read_int(pPos, m_bReverse);

  pSecHeader->u32_35_numOfRelocEntries = read_uint(pPos, m_bReverse);
  pSecHeader->u36_39_numOfLineNumberEntries = read_uint(pPos, m_bReverse);
  pSecHeader->u40_43_flags = read_uint(pPos, m_bReverse);

  pSecHeader->us44_45_reserved = read_ushort(pPos, m_bReverse);
  pSecHeader->u46_47_memPageNumber = read_ushort(pPos, m_bReverse);
}

std::string COFF_parser::parse_string_entry()
{
  char buf[1024];
  memset(buf,0,1024);
  char *pChar = &buf[0];
  char c;

  if((int)m_pFIn < 0x50000000)
  {
    std::cout << to_hex_str(m_pFIn) << "\n";
  }
  while((c = fgetc(m_pFIn)) != NULL)
  {
    *pChar++ = c;
  }

  std::string str = buf;

  m_vecStrTbl.push_back(str);
  return str;
}

void COFF_parser::parse_string_table()
{
  fpos_t saved_pos;
  fgetpos(m_pFIn,&saved_pos);
  m_iBeginAddrOfStringTable = (int)saved_pos;
  fseek(m_pFIn, 0L, SEEK_END);
 
  fpos_t fsize = ftell(m_pFIn);
  
  //std::cout << "current pos:" << to_hex_str(saved_pos) << "\n";
  //std::cout << "file size:" << to_hex_str(fsize) << "\n";

  fsetpos(m_pFIn,&saved_pos);
  while (saved_pos < fsize)
  {
    fpos_t pos;
    fgetpos(m_pFIn,&pos);
    fpos_t diff = pos - m_iBeginAddrOfStringTable;

    std::string& str = parse_string_entry();
    StringTable_entry* pStrTE = new StringTable_entry(str,m_vecStrTbl.size()-1,diff);
    m_mapStrTbl.insert(std::make_pair(diff,pStrTE));
    fgetpos(m_pFIn,&saved_pos);
  }

  //std::cout << "string table entries:" << m_vecStrTbl.size();
}

void COFF_parser::parse_symbol_entry(ST_entry* pSTE)
{
  char buf[COFF_SYMBOL_TABLE_ENTRY_LEN + 1];
  fpos_t pos;
  fgetpos(m_pFIn,&pos);
  if(COFF_SYMBOL_TABLE_ENTRY_LEN == fread(buf,1,COFF_SYMBOL_TABLE_ENTRY_LEN,m_pFIn))
  {
    char* pPos = &buf[0];
    parse_char8_name(pPos, pSTE->name);
    pSTE->i8_11_value = read_int(pPos, m_bReverse);
    pSTE->s12_13_secNumberDefinedIn = read_short(pPos, m_bReverse);
    pSTE->us14_15_reserved = read_ushort(pPos, m_bReverse);
    pSTE->c16_storageClass = read_char(pPos);
    pSTE->c17_numOfAuxEntries = read_char(pPos);

    pSTE->address = (int)pos;
    m_iParsedSymbolEntries++;
    m_pCoffHeader->numOfSymbol++;

    if (pSTE->c17_numOfAuxEntries) // has Aux Entry
    {
      if (COFF_SYMBOL_TABLE_ENTRY_LEN == fread(buf,1,COFF_SYMBOL_TABLE_ENTRY_LEN,m_pFIn))
      {
        char* pPos = &buf[0];
        pSTE->iAux0_3_secLength = read_int(pPos, m_bReverse);
        pSTE->usAux4_5_numOfRelocEntries = read_ushort(pPos, m_bReverse);
        pSTE->usAux6_7_numOfLineNumberEntries = read_ushort(pPos, m_bReverse);
        pSTE->hasAuxEntry = true;
        // 8 - 17 not used

        m_iParsedSymbolEntries++;
        m_pCoffHeader->numOfAuxSymbolEntry++;
      }
      else
      {
        throw new COFF_Parse_Error;
      }
    }
    else
    {
      pSTE->hasAuxEntry = false;
    }
    
  }
  else
  {
    throw new COFF_Parse_Error;
  }
}


void COFF_parser::parse()
{
  parse1();

  // resolve long section/symbol name
  parse2();

  // resolve all section info
  parse3();


  finish();
}

void COFF_parser::finish()
{
  // puts header
  std::cout << m_pCoffHeader->to_s() << "\n";
  *m_pofs << m_pCoffHeader->to_s() << "\n";

  // puts option header
  if (m_pCoffHeader->has_option_header())
  {
    //std::cout << m_pCoffOptionHeader->to_s() << "\n";
    *m_pofs << m_pCoffOptionHeader->to_s() << "\n";
  }

  // puts section headers
  std::vector<COFF_sectionHeader*>::iterator itSH =  m_vecSecHeaders.begin();
  for (;itSH != m_vecSecHeaders.end();itSH++)
  {
    COFF_sectionHeader* pSecH = *itSH;
    *m_pofs << pSecH->to_s();
  }

  // puts all symbol
  std::vector<ST_entry*>::iterator itSTE = m_vecSTEntries.begin();
  for (;itSTE != m_vecSTEntries.end();itSTE++)
  {//TODO add option
    //ST_entry *pSTE = *itSTE;
    //*m_pofs << pSTE->to_s();
  }

  // puts string table
  std::map<c6x::qword_t,StringTable_entry*>::iterator it = m_mapStrTbl.begin();
  for (; it != m_mapStrTbl.end();it++)
  {//TODO add option
    StringTable_entry* pStrTE = it->second;
    //if (NULL != pStrTE)
    //{
    //  *m_pofs << to_hex_str(it->first) << " , " << it->second->_id 
    //    << " , " << it->second->_str << "\n";
    //}

  }
}

void COFF_parser::parse1()
{
  char buf[49]; // temporary buffer 

  // read header;
  if(COFF_HEADER_LEN == fread(_header,1,COFF_HEADER_LEN,m_pFIn))
  {
    // test byte order
    byte first_byte = _header[0];
    if (first_byte == 0xc2)
    {
      set_reverse(true);
    }
    else
    {
      set_reverse(false);
    }

    m_pCoffHeader = new COFF_header();
    parse_header(m_pCoffHeader,_header);

    // option header
    if (m_pCoffHeader->has_option_header())
    {
      if (COFF_OPTION_HEADER_LEN != m_pCoffHeader->optionHeaderLen)
      {
        throw new COFF_Parse_Error;
      }

      m_pCoffOptionHeader = new COFF_optionHeader;
      if(COFF_OPTION_HEADER_LEN == fread(_optionHeader,1,COFF_OPTION_HEADER_LEN,m_pFIn))
      {
        parse_option_header(m_pCoffOptionHeader,_optionHeader);
      }
      else
      {
        throw new COFF_Parse_Error;
      }
    }
  }
  else
  {
    throw new COFF_Parse_Error;
  }

  // each section header
  for (int i = 0; i < m_pCoffHeader->numOfSecHeaders; i++)
  {
    memset(buf,0,sizeof(buf));
    COFF_sectionHeader *pSecHeader = new COFF_sectionHeader;

    fpos_t pos;
    fgetpos(m_pFIn,&pos);
    //std::cout << "current pos:" << to_hex_str(pos) << "\n";

    if(COFF_SECTION_HEADER_LEN == fread(buf,1,COFF_SECTION_HEADER_LEN,m_pFIn))
    {
      parse_section_header(pSecHeader,buf);
      pSecHeader->iFilePos = COFF_HEADER_LEN + i * COFF_SECTION_HEADER_LEN;
      if (m_pCoffHeader->has_option_header())
      {
        pSecHeader->iFilePos += COFF_OPTION_HEADER_LEN;
      }
      pSecHeader->id = i + 1;  // section id start from 1
      m_vecSecHeaders.push_back(pSecHeader);
    }
    else
    {
      throw new COFF_Parse_Error;
    }
  }

  // locate to symbol table
  fpos_t pos;
  pos = (fpos_t)m_pCoffHeader->addressOfST;
  fsetpos(m_pFIn,&pos);
  fgetpos(m_pFIn,&pos);
  //std::cout << "current pos:" << to_hex_str(pos) << "\n";

  //for (int i = 0;i < m_pCoffHeader->numOfEntryST;i++)
  int i =0;
  while(m_iParsedSymbolEntries < m_pCoffHeader->numOfEntryST)
  {
    ST_entry *pSTE = new ST_entry;
    parse_symbol_entry(pSTE);
    pSTE->id = i++;

    //std::cout << pSTE->to_s();
    //*m_pofs << pSTE->to_s();
    m_vecSTEntries.push_back(pSTE);

  }

  // string table
  try
  {
    parse_string_table();
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
}

void COFF_parser::parse2()
{
  // fix section header name
  std::vector<COFF_sectionHeader*>::iterator it = m_vecSecHeaders.begin();
  for (; it != m_vecSecHeaders.end();it++)
  {
    COFF_sectionHeader *pSecH = *it;
    if (!pSecH->name.bShortName)  // file pointer name
    {
      int diff = pSecH->name.n.fp;
      StringTable_entry* pStrTE = m_mapStrTbl[diff];
      if (NULL == pStrTE)
      {
        throw new COFF_Parse_Error;
      }
      pSecH->realName = pStrTE->_str;
    }
    else
    {
      pSecH->realName = pSecH->name.n.c0_7_name;
    }

  }

  // fix symbol name
  std::vector<ST_entry*>::iterator itSTE = m_vecSTEntries.begin();
  for (; itSTE != m_vecSTEntries.end();itSTE++)
  {
    ST_entry *pSTE = *itSTE;
    if (!pSTE->name.bShortName)
    {
      int diff = pSTE->name.n.fp;

      //if (diff >= m_vecStrTbl.size())
      {

        //try to find as file pointer?
        StringTable_entry* pStrTE = m_mapStrTbl[diff];
        if (NULL == pStrTE)
        {
          //throw new COFF_Parse_Error;
          // the first symbol use a index to string table?
          //std::cout << "\n" << pSTE->id << "\n";
          //std::cout << "i " << "\n";
          pSTE->realName = m_vecStrTbl[diff];   // as index
        }
        else
        {
          //std::cout << pStrTE->_str << "\n-----\n";
          pSTE->realName = pStrTE->_str;
        }
      }
    }
    else
    {
      pSTE->realName = pSTE->name.n.c0_7_name;
    }

    //std::cout<<pSTE->realName << "\n";

    //FIXME CIO process
    if(pSTE->realName.compare("__CIOBUF_") == 0)
    {
      std::cout << "find ciobuf" << "\n";
      std::cout << to_hex_str(pSTE->i8_11_value) << "\n";
      m_pCore->set_ciobuf(pSTE->i8_11_value);
    }
    if(pSTE->realName.compare("C$$IO$$") == 0)
    {
      std::cout << "find cio" << "\n";
      std::cout << to_hex_str(pSTE->i8_11_value) << "\n";
      m_pCore->set_cio_hook(pSTE->i8_11_value);
    }
    if(pSTE->realName.compare("C$$EXIT") == 0)
    {
      std::cout << "find cexit" << "\n";
      std::cout << to_hex_str(pSTE->i8_11_value) << "\n";
      m_pCore->set_cexit_hook(pSTE->i8_11_value);
    }

    //TODO add attr
    if(pSTE->realName.compare("_main") == 0)
    {
      m_pCore->set_main(pSTE->i8_11_value);
    }

    //TODO 
    if(pSTE->realName.compare("_DPP_userFatalErrHandler") == 0)
    {
      m_pCore->add_bp(pSTE->i8_11_value);
    }

    // add to symbol table
    if( pSTE->realName.find_first_of(".$") == std::string::npos)
    {
      m_pCore->get_sym_tbl().insert(std::make_pair(pSTE->i8_11_value,pSTE->realName));
    }
  }
}

void COFF_parser::parse3()
{
  // parse each section
  std::vector<COFF_sectionHeader*>::iterator it = m_vecSecHeaders.begin();

  for (; it != m_vecSecHeaders.end();it++)
  {
    COFF_sectionHeader* pSecH = *it;
    if (pSecH->realName.compare(".debug_abbrev") == 0) // .debug_abbrev section
    {
      read_debug_abbrev_raw_info(pSecH);
      m_pSecDebugAbbrev = pSecH;
    }

    if (pSecH->realName.compare(".debug_info") == 0)
    {
      read_debug_info_raw_info(pSecH);
      m_pSecDebugInfo = pSecH;
    }

    // parse section data
    if (SEC_HAS_FLAG(pSecH->u40_43_flags,SYTP_DATA) ||
      SEC_HAS_FLAG(pSecH->u40_43_flags,SYTP_TEXT))
    {
        fpos_t pos = pSecH->i20_23_fpRawData;
        size_t sec_len = pSecH->i16_19_size;
        fsetpos(m_pFIn,&pos);

        char* raw = new char[pSecH->i16_19_size + 1];
        memset(raw,0,pSecH->i16_19_size + 1);

        if(pSecH->i16_19_size == fread(raw,1,pSecH->i16_19_size,m_pFIn))
        {
          //std::cout << "read OK\n";
          
          //NEED?
          //if (pSecH->i16_19_size % 4 != 0){
          //  throw new COFF_Parse_Error;
          //}
          int size_in_u32 = pSecH->i16_19_size / 4;
          word_t *raw_u32 = (word_t*)raw;
          
          //md_addr_t addr = pSecH->i8_11_physicalAddr;

          // xxx load to virtual addr
          md_addr_t addr = pSecH->i12_15_virtualAddr;
          if (NULL != get_l2())
          {
            for (int i=0;i<size_in_u32;++i)
            {
              //std::cout << "write:" << to_hex_str(raw_u32[i]) << "\n";
              //get_l2()->mem_write_word(addr+i*4,raw_u32[i]);
              get_l2()->mem_load_word(addr+i*4,raw_u32[i]);

              //word_t tmp = get_l2()->mem_read_word(addr+4*i);
              //byte_t b = get_l2()->mem_read_byte(addr+4*i);
            }

            // mem write protect/detect
            // xxx protect by physical addr
            if(SEC_HAS_FLAG(pSecH->u40_43_flags,SYTP_TEXT))
            {
              md_addr_t phy_addr = pSecH->i8_11_physicalAddr;
              MemRange *mr = new MemRange(phy_addr, size_in_u32*4);
              m_pCore->get_mem_prot_list().push_back(mr);
            }
          }
        }
        else
        {
          throw new COFF_Parse_Error;
        }

        /*
        std::cout << pSecH->realName << "\n";
        std::cout << to_hex_str(pos) << "\n";
        std::cout << to_hex_str(sec_len) << "\n";
        std::cout << to_hex_str(pSecH->i8_11_physicalAddr) << "\n";
        std::cout << to_hex_str(pSecH->u40_43_flags) << "\n";
        */
        //system("pause");
    }
  }

  dwarf_parse_debug_info_section();
}

void COFF_parser::read_debug_abbrev_raw_info(COFF_sectionHeader* pSecH)
{
  // read raw data in memory
  fpos_t fpos;
  fpos = pSecH->i20_23_fpRawData;
  fsetpos(m_pFIn,&fpos);

  m_pcDebugAbbrevRaw = new char[pSecH->i16_19_size + 1];
  memset(m_pcDebugAbbrevRaw,0,pSecH->i16_19_size + 1);
  if(pSecH->i16_19_size == fread(m_pcDebugAbbrevRaw,1,pSecH->i16_19_size,m_pFIn))
  {
    std::cout << ".debug_abbrev read OK\n";
  }
  else
  {
    throw new COFF_Parse_Error;
  }
}

void COFF_parser::read_debug_info_raw_info(COFF_sectionHeader* pSecH)
{
  fpos_t pos;
  pos = pSecH->i20_23_fpRawData;
  fsetpos(m_pFIn,&pos);

  m_pcDebugInfoRaw = new char[pSecH->i16_19_size + 1];
  memset(m_pcDebugInfoRaw,0,pSecH->i16_19_size + 1);
  if(pSecH->i16_19_size == fread(m_pcDebugInfoRaw,1,pSecH->i16_19_size,m_pFIn))
  {
    std::cout << ".debug_info read OK\n";
  }
  else
  {
    throw new COFF_Parse_Error;
  }
}

void COFF_parser::dwarf_parse_debug_info_section()
{
  assert(m_pSecDebugAbbrev);
  assert(m_pSecDebugInfo);
  
  char* debug_abbrev_pos = m_pcDebugAbbrevRaw;
  char* end_of_debug_abbrev = m_pcDebugAbbrevRaw + m_pSecDebugAbbrev->i16_19_size; // end address of this section

  char* debug_info_pos = m_pcDebugInfoRaw;
  char* end_of_debug_info = m_pcDebugInfoRaw + m_pSecDebugInfo->i16_19_size;

  // indent for print tree info
  int level = 0;

  // compilation unit header
  word_t unit_len = read_uint(debug_info_pos,m_bReverse);
  ushort dwarf_v = read_ushort(debug_info_pos,m_bReverse);
  word_t offset_in_debug_abbrev = read_uint(debug_info_pos,m_bReverse);
  byte size_in_bytes_of_address = read_char(debug_info_pos);

  // parse the first entry
  unsigned code = decode_unsigned_LEB128(debug_info_pos);
  std::cout << "code entry:" << code <<"\n";

  // find the code in debug_abbrev

  /*
  while (pos < end_pos)
  {
    // new entry
    AbbrevEntry *pAbbrevE = new AbbrevEntry;
    
    int diff = pos - m_pcDebugAbbrevRaw;
    int address = diff + pSecH->i20_23_fpRawData;
    unsigned code = decode_unsigned_LEB128(pos);

    if (0 != code)
    {
      pAbbrevE->entryCode = code;
      pAbbrevE->entryTag = decode_unsigned_LEB128(pos);
      pAbbrevE->hasChildren = read_char(pos);

      dw_at_t attrType;
      do 
      {
        attrType.name = decode_unsigned_LEB128(pos);
        attrType.format = decode_unsigned_LEB128(pos);

        if (!attrType.isNull())
        {
          pAbbrevE->vecAttrType.push_back(attrType);
        }
      } while (!attrType.isNull());

      m_mapDwarfAbbrEntryMap.insert(std::make_pair(address,pAbbrevE));

      if (NULL != pLastEntry)
      {
        if (pLastEntry->hasChildren)
        {
          if (NULL == pLastEntry->firstChild)
          {
            pLastEntry->firstChild = pAbbrevE;
            pAbbrevE->parent = pLastEntry;
            level++;
          }
          else
          {
            pLastEntry->firstChild->nextSibling = pAbbrevE;
            pAbbrevE->parent = pLastEntry->parent;
          }
        }
        else
        {
          pLastEntry->nextSibling = pAbbrevE;
          pAbbrevE->parent = pLastEntry->parent;
        }
      }

      std::cout<< "entry code[" << level << "]:" << pAbbrevE->entryCode << 
        "has child?" << pAbbrevE->hasChildren <<"\n";
      pLastEntry = pAbbrevE;
    }
    else   // a null entry
    {

      if (level < 0)
      {
        throw new COFF_Parse_Error;
      }

      level = 0;
      pLastEntry = NULL;

      std::cout << "end a sibling chain\n";

    }
  }
  */

}

void COFF_parser::connect(c6x::Core* core)
{
  m_pCore = core;
}