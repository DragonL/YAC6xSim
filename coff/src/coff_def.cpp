#include "common/inc/def.hpp"
#include "coff/inc/coff_def.hpp"

USING_NS

sytp_t sytp_lst[14] = {
  {0x0,"STYP_REG","Regular section (allocated, relocated, loaded)"},
  {0x1,"STYP_DSECT","Dummy section (relocated, not allocated, not loaded)"},
  {0x2,"STYP_NOLOAD","Noload section (allocated, relocated, not loaded)"},
  {0x4,"STYP_GROUP","Grouped section (formed from several input sections). C6000:Reserved"},
  {0x8,"STYP_PAD","Padding section (loaded, not allocated, not relocated). C6000:Reserved"},
  {0x10,"STYP_COPY","Copy section (relocated, loaded, but not allocated; relocation entries are processed normally)"},
  {0x20,"STYP_TEXT","Section contains executable code"},
  {0x40,"STYP_DATA","Section contains initialized data"},
  {0x80,"STYP_BSS","Section contains uninitialized data"},
  {0x1000,"STYP_BLOCK","Alignment used as a blocking factor."},
  {0x2000,"STYP_PASS","Section should pass through unchanged."},
  {0x4000,"STYP_CLINK","Section requires conditional linking"},
  {0x8000,"STYP_VECTOR","Section contains vector table. Applies to C6000 only."},
  {0x10000,"STYP_PADDED","section has been padded.  Applies to C6000 only."}
};

static const char* yes_or_no(bool yes)
{
  if (yes)
  {
    return "YES";
  }
  else
  {
    return "NO";
  }
}

std::string COFF_header::to_s()
{
  std::stringstream ss;
  char buf[256];

  ss << "Header Info:\n";

  // version ID
  sprintf_s(buf,256,"0x%04x",versionID);
  ss << " version ID: " << buf << "\n";

  ss << " Number Of Section Headers: " << numOfSecHeaders << "\n";

  // time stamp
  sprintf_s(buf,256,"0x%08x",timeStamp);
  ss << " (TODO)Time Stamp: " << buf << "\n";

  ss << " Start address of symbol table: " << to_hex_str(addressOfST) << "\n";

  ss << " Number of entries in the symbol table: " << numOfEntryST << "\n";
  ss << "   - Number of symbol:" << numOfSymbol << "\n";
  ss << "   - Number of auxiliary symbol entries:" << numOfAuxSymbolEntry << "\n";

  ss << " Has option header? : " << yes_or_no(optionHeaderLen>0) << "\n";

  sprintf_s(buf,256,"0x%04x",flags);
  ss << " (TODO)Flags: " << buf << "\n";

  ss << " Target ID: ";
  switch (targetID)
  {
  case 0x97:
    ss << "TMS470";
    break;
  case 0x98:
    ss << "TMS320C5400";
    break;
  case 0x99:
    ss << "TMS320C6000";
    break;
  case 0x9C:
    ss << "TMS320C5500";
    break;
  case 0x9D:
    ss << "TMS320C2800";
    break;
  case 0xA0:
    ss << "MSP430";
    break;
  case 0xA1:
    ss << "TMS320C5500+";
    break;
  default:
    ss << "Unknown";
  }
  sprintf_s(buf,256,"(0x%04x)",targetID);
  ss << buf << "\n-----\n";
  return ss.str();
}

std::string COFF_optionHeader::to_s()
{
  std::stringstream ss;
  char buf[256];

  buf;
  //ss << " Optional Header Info:\n";

  //ss << "TODO" << "\n";

  return ss.str();
}

std::string COFF_sectionHeader::to_s()
{
  std::stringstream ss;

  ss << "Section[" << id << "] ";

  /*
  if(!name.bShortName)
  {
    ss << "(TODO)" << hex_str(name.n.fp) << "\n";
  }
  else
  {
    ss << name.n.c0_7_name << "\n";
  }
  */

  ss << realName << "\n";

  ss << "  Pos in .out:" << to_hex_str(iFilePos) << "\n";
  ss << "  Physical Address:" << to_hex_str(i8_11_physicalAddr) << "\n";
  ss << "  Virtual Address:" << to_hex_str(i12_15_virtualAddr) << "\n";
  ss << "  Size(bytes):" << to_hex_str(i16_19_size) << "\n";
  ss << "  File pointer to raw data:" << to_hex_str(i20_23_fpRawData) << "\n";
  ss << "  File pointer to relocation entries:" << to_hex_str(i24_27_fpRelocEntries) << "\n";
  //ss << "  Reserved:" << hex_str(i12_15_virtualAddr) << "\n";

  ss << "  Number of relocation entries:" << u32_35_numOfRelocEntries << "\n";
  //ss << "  Reserved:" << hex_str(u36_39_numOfLineNumberEntries) << "\n";
  //ss << "  (TODO)Flags:" << hex_str(u40_43_flags) << "\n";
  ss << flag_info();

  //ss << "  Reserved:" << hex_str(us44_45_reserved) << "\n";
  ss << "  Memory page number:" << u46_47_memPageNumber << "\n";

  ss << "-----\n";

  return ss.str();
}


std::string COFF_sectionHeader::flag_info()
{
  std::stringstream ss;

  int alignment = 1 << ((u40_43_flags >> 8) & 0xf);
  ss << "  Flags:" << hex_str_short(u40_43_flags) << "\n"
     << "    - alignment:" << alignment << "\n";

  for (int i = 0; i < ELEM_NUM(sytp_lst);i++)
  {
    if (SYTP_TEST(u40_43_flags,sytp_lst[i].type))
    {
      ss << "    - " << sytp_lst[i].abbrev << " | " << sytp_lst[i].info << "\n";
    }
  }

  return ss.str();
}

std::string ST_entry::to_s()
{
  std::stringstream ss;

  ss << "Symbol[" << id << "] " << "<" << to_hex_str(address) << ">";

  ss << realName << "\n";

  ss << "  Value:" << to_hex_str(i8_11_value) << "\n";
  ss << "  Section number of the symbol:" << s12_13_secNumberDefinedIn << "\n";
  ss << "  Reserved:" << to_hex_str(us14_15_reserved) << "\n";
  ss << "  Storage class:" << hex_str_c(c16_storageClass) << "\n";
  ss << "  Has auxiliary entry?:" << yes_or_no(hasAuxEntry) << "\n";

  if(hasAuxEntry)
  {
    ss << "  Auxiliary entry:" << "\n";
    ss << "    - Section length:" << to_hex_str(iAux0_3_secLength) << "\n";
    ss << "    - Number of relocation entries:" << usAux4_5_numOfRelocEntries << "\n";
    ss << "    - Number of line number entries:" << usAux6_7_numOfLineNumberEntries << "\n";
  }

  ss << "-----\n";

  return ss.str();
}