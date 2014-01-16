#ifndef COFF_DEF_HPP
#define COFF_DEF_HPP

#include <exception>
#include <string>
#include <sstream>

//macros
#define COFF_HEADER_LEN 22
#define COFF_OPTION_HEADER_LEN 28
#define COFF_SECTION_HEADER_LEN 48
#define COFF_SYMBOL_TABLE_ENTRY_LEN 18

#define ELEM_NUM(ary) (sizeof(ary)/sizeof(0[ary]))

// section flag
#define SYTP_TEST(flag,type) ((flag & type) != 0)

typedef struct sytp_t{
  int type;
  const char* abbrev;
  const char* info;
}sytp_t;

//typedefs
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;

class COFF_Parse_Error : std::exception{};

typedef struct  
{
  union{
    char c0_7_name[9];
    int fp; // pointer to StrT
  } n;
  bool bShortName;
} COFF_name;


class COFF_header  
{
public:
  ushort versionID;
  ushort numOfSecHeaders;
  int timeStamp;            // when created
  int addressOfST;  // File pointer; contains the symbol table's starting address
  int numOfEntryST; // Number of entries in the symbol table
  ushort optionHeaderLen; // 0 or 28 bytes
  ushort flags;
  ushort targetID; // magic number

  int numOfSymbol;
  int numOfAuxSymbolEntry;
  std::string to_s();

  COFF_header():numOfSymbol(0),numOfAuxSymbolEntry(0){}

  inline bool has_option_header()
  {
    return 0 != optionHeaderLen;
  }
};

class COFF_optionHeader
{
public:
  short s0_1_magic;
  short s2_3_versionStamp;
  int   i4_7_exeCodeSizeInBytes;
  int   i8_11_initializedDataSizeInBytes;
  int   i12_15_uninitializedDataSizeInBytes;
  int   i16_19_entryPoint;
  int   i20_23_beginningAddrOfExeCode;
  int   i24_27_beginningAddrOfinitializedData;

  std::string to_s();
};

class COFF_sectionHeader
{
public:
  COFF_name name;
  
  int  i8_11_physicalAddr;
  int  i12_15_virtualAddr;
  int  i16_19_size;  // bytes for C6000
  int  i20_23_fpRawData;  // file pointer to raw data
  int  i24_27_fpRelocEntries; // file pointer to relocation entries
  int  i28_31_reserved;
  uint u32_35_numOfRelocEntries;
  uint u36_39_numOfLineNumberEntries; // reserved for C6000
  uint u40_43_flags;
  ushort us44_45_reserved;
  ushort u46_47_memPageNumber;  // memory page number

  uint iFilePos;
  uint id;
  bool bFPName; // name is pointer to ST
  std::string realName;

  std::string to_s();

  std::string flag_info();
};

class ST_entry
{
public:
  ST_entry():isSpecailSymbol(false){}

  COFF_name name;
  int i8_11_value;
  short s12_13_secNumberDefinedIn;
  ushort us14_15_reserved;
  char c16_storageClass;
  char c17_numOfAuxEntries;  // 0 or 1

  int iAux0_3_secLength; // section length
  ushort usAux4_5_numOfRelocEntries;
  ushort usAux6_7_numOfLineNumberEntries;
  char cAux8_17_notUsed[10];

  bool bFPName; // name is pointer to ST
  bool isSpecailSymbol;
  bool hasAuxEntry;
  std::string realName;
  int id;
  unsigned long address;

  std::string to_s();
};

class StringTable_entry
{
public:
  StringTable_entry(std::string& str,int id, int diff):_str(str),_id(id),_diff(diff){}
  std::string _str;
  int _id;
  int _diff;

  std::string to_s();
};

inline ushort read_ushort(char*& pAddress, bool bReverse = false)
{
  byte b1 = *pAddress++;
  byte b2 = *pAddress++;
  ushort u;
  if(bReverse)
  {
    u = (b2 << 8) | b1;
  }
  else
  {
    u = (b1 << 8) | b2;
  }
  return u;
}

inline short read_short(char*& pAddress, bool bReverse = false)
{
  return (short)read_ushort(pAddress,bReverse);
}

inline int read_int(char*& pAddress, bool bReverse = false)
{
  byte b1 = *pAddress++;
  byte b2 = *pAddress++;
  byte b3 = *pAddress++;
  byte b4 = *pAddress++;

  int i;
  if(bReverse)
  {
    i = (b4 << 24) | (b3 << 16) | (b2 << 8) | b1;
  }
  else
  {
    i = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
  }
  return i;
}

inline uint read_uint(char*& pAddress, bool bReverse = false)
{
  return (uint)read_int(pAddress,bReverse);
}

inline char read_char(char*& pAddress)
{
  return *pAddress++;
}

inline void read_buf(char*& pAddress, char* dst, int num)
{
  int num_to_cpy = num;
  while (!*pAddress)
  {
    pAddress++;
    num_to_cpy--;
  }

  if (num_to_cpy > 0)
  {
    memset(dst,0,num+1);
    memcpy(dst,pAddress,num_to_cpy);
  }

  pAddress += num_to_cpy;
}

template <class T>
inline std::string hex_str(T val)
{
  static char buf[256];
  sprintf_s(buf,256,"0x%08x",val);
  return std::string(buf);
}

template <class T>
inline std::string hex_str_short(T val)
{
  static char buf[256];
  sprintf_s(buf,256,"0x%04x",val);
  return std::string(buf);
}

inline std::string hex_str_c(char c)
{
  static char buf[16];
  sprintf_s(buf,16,"0x%02x",c);
  return std::string(buf);
}

typedef enum sec_flag_t{
  SYTP_REG = 0x0,
  SYTP_DSECT = 0x1,
  SYTP_NOLOAD = 0x2,
  SYTP_GROUP = 0x4,
  SYTP_PAD = 0x8,
  SYTP_COPY = 0x10,
  SYTP_TEXT = 0x20,
  SYTP_DATA = 0x40,
  SYTP_BSS  = 0x80,
  SYTP_BLOCK = 0x1000,
  SYTP_PASS = 0x2000,
  SYTP_CLINK = 0x4000,
  SYTP_VECTOR = 0x8000,
  SYTP_PADDED = 0x10000
}sec_flag_t;

#define SEC_HAS_FLAG(flag,flag_t) \
  (((flag) & (flag_t)) != 0)


#endif