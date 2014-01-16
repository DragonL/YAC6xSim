#include "core/inc/edma.hpp"
#include <vector>

BEGIN_NS

#ifdef _WIN32
#define BYTE_CPY(phy_dst,phy_src,byte_cnt) \
      __movsb((byte_t*)phy_dst,(byte_t*)phy_src,byte_cnt);
#else
#define BYTE_CPY(phy_dst,phy_src,byte_cnt) \
      memcpy(phy_dst,phy_src,byte_cnt);
#endif

#define ESRL  0x01A0FFFC
#define ESRH  0x01A0FFBC

#define ERL   0x01A0FFF0
#define EERL  0x01A0FFF4

#define CIERL 0x01A0FFE8
#define CIPRL 0x01A0FFE4

#define CCERL 0x01A0FFEC

#define PaRAM_BASE 0x01A00000
#define PaENTRY_SIZE 24 /* bytes */
#define GET_PAENTRY_ADDR(nr) (PaRAM_BASE + PaENTRY_SIZE*nr)

md_addr_t chlist[4] = {0,0,0,0};
word_t ch_count = 0;

word_t ccrl = 0;

/// ESIZE table
word_t esize_tbl[4] = // in bytes
{
  4,
  2,
  1,
  4 // reserved
};

static void __fastcall code_modify_detect(Core *core,md_addr_t start_addr,word_t word_len)
{
  MemRange *mr;
  Core::mem_prot_list_t::iterator it = core->get_mem_prot_list().begin();
  core->get_ofs() << "EDMA dst:" << to_hex_str(start_addr) << "\n";
  for(; it != core->get_mem_prot_list().end();++it)
  {
    mr = *it;
    if(mr->include(start_addr))
    {
      core->get_ofs() << "CODE MODIFY by EDMA:" << to_hex_str(start_addr) <<
        ",Len:" << to_hex_str(word_len * 4) << "\n";
      core->get_ofs().flush();
      for(int i = 0; i < word_len; ++i)
      {
        core->re_pre_decode_32bit(start_addr + i * 4);
      }
      break;
    }
  }
}

static inline void reload_ch(phy_addr_t dst_ch, phy_addr_t src_ch)
{
  BYTE_CPY(dst_ch,src_ch,24); // 24 bytes
}

//1. only support lower 32 channel : ERL
void EDMA::cc_proc(Core *core)
{
  L2MemCtroller *l2mc = core->get_l2();

  //xxx ESRL
  word_t esrl = l2mc->mem_read_word(ESRL);
  if(esrl != 0)
  {
    word_t esrl_mask = 0x1;
    if(ch_count < 4)
    {
      for(word_t i = 0; i < 32;++i)
      {
        if(esrl & esrl_mask)
        { // event channel i
          md_addr_t pa_addr = GET_PAENTRY_ADDR(i);
          chlist[ch_count++] = pa_addr;
          if(ch_count > 4)
          {
            break;
          }
          //clear the bit in esrl
          esrl &= ~esrl_mask;
        }
        if(esrl == 0)
        {// no more request
          break;
        }
        esrl_mask <<= 1;
      }
    }

    //clear ESRL
    l2mc->mem_write_word(ESRL,0);
  }

  //xxx ESRH
  word_t esrh = l2mc->mem_read_word(ESRH);
  if(esrh != 0)
  {
    word_t esrh_mask = 0x1;
    if(ch_count < 4)
    {
      for(word_t i = 32; i < 64;++i)
      {
        if(esrh & esrh_mask)
        { // event channel i
          md_addr_t pa_addr = GET_PAENTRY_ADDR(i);
          chlist[ch_count++] = pa_addr;
          if(ch_count > 4)
          {
            break;
          }
          //clear the bit in esrl
          esrh &= ~esrh_mask;
        }
        if(esrh == 0)
        {// no more request
          break;
        }
        esrh_mask <<= 1;
      }
    }

    //clear ESRH
    l2mc->mem_write_word(ESRH,0);
  }

  /* xxx support ERL/ERH later
  */
  word_t erl = l2mc->mem_read_word(ERL);
  if(erl != 0)
  {
    word_t eerl = l2mc->mem_read_word(EERL);
    erl &= eerl;
    if(erl != 0)
    {
      word_t esrl_mask = 0x1;
      core->get_ofs() << "!!ERL:" << to_hex_str(erl) << "\n";
      if(ch_count < 4)
      {
        for(word_t i = 0; i < 32;++i)
        {
          if(esrl & esrl_mask)
          { // event channel i
            md_addr_t pa_addr = GET_PAENTRY_ADDR(i);
            chlist[ch_count++] = pa_addr;
            if(ch_count > 4)
            {
              break;
            }
            //clear the bit in esrl
            esrl &= ~esrl_mask;
          }
          if(esrl == 0)
          {// no more request
            break;
          }
          esrl_mask <<= 1;
        }
      }
    }

    //xxx.FIXME. we clear ERL here
    l2mc->mem_write_word(ERL,0);
  }

  if(ccrl != 0)
  {
    word_t ccrl_mask = 0x1;
#ifdef EDMA_DBG
    core->get_ofs() << "CCRL :" << to_hex_str(ccrl) << "\n";
#endif
    if(ch_count < 4)
    {
      for(word_t i = 0; i < 32;++i)
      {
        if(ccrl & ccrl_mask)
        { // event channel i
          ccrl &= ~ccrl_mask;
          md_addr_t pa_addr = GET_PAENTRY_ADDR(i);
          word_t j = 0;
          for(; j < ch_count; ++j)
          {
            if(chlist[j] == pa_addr)
            {
              break;
            }
          }
          if(j >= ch_count)
          {
            chlist[ch_count++] = pa_addr;
#ifdef EDMA_DBG
            core->get_ofs() << "ADD a chain :" << i << "\n";
#endif
          }
          if(ch_count > 4)
          {
            break;
          }
        }
        if(ccrl == 0)
        {// no more request
          break;
        }
        ccrl_mask <<= 1;
      }
    }
    ccrl = 0; // clear 
  }

  if(ch_count == 0)
  {
    return;
  }

  // process each channel
  word_t ch_count_after = ch_count;
  for(word_t i = 0; i < ch_count; ++i)
  {// only support FS==1,2DS==0,2DD==0,PRI ignored
    md_addr_t pa = chlist[i];
    word_t opt = l2mc->mem_read_word(pa);
    word_t src = l2mc->mem_read_word(pa+4);
    word_t cnt = l2mc->mem_read_word(pa+8);
    word_t dst = l2mc->mem_read_word(pa+12);
    word_t idx = l2mc->mem_read_word(pa+16);
    word_t SUM = get_uint(opt,24,2);
    word_t DUM = get_uint(opt,21,2);

    word_t tcc = get_uint(opt,16,4);
    word_t tccm = get_uint(opt,13,2);
    tcc |= tccm << 4;

    word_t atcc = get_uint(opt,5,6);

    //TMP
    word_t rld = l2mc->mem_read_word(pa+20);

#ifdef EDMA_DBG
    core->get_ofs() << "[" << i << "]" << "EDMA proc src:" << to_hex_str(src) <<
      ",dst:" << to_hex_str(dst) << ",cnt:" << to_hex_str(cnt) << "\n";
    core->get_ofs() << "OPT:" << to_hex_str(opt) << 
      ",PA addr:" << to_hex_str(pa) << ",RLD:" << to_hex_str(rld) << "\n";
    core->get_ofs() << "IDX:"<< to_hex_str(idx) << "\n";
    core->get_ofs() << "SUM:" << SUM << "\n";
    core->get_ofs() << "DUM:" << DUM << "\n";
    core->get_ofs() << "TCCINT:" << get_uint(opt,20,1) << "," <<
      "TCC:" << to_hex_str(tcc) << "\n";
    core->get_ofs() << "ATCCINT:" << get_uint(opt,12,1) << "," <<
      "ATCC:" << to_hex_str(atcc) << "\n";
    core->get_ofs().flush();
#endif

    if(opt == 0)
    { // xxx only check opt here
      chlist[i] = NULL;
      ch_count_after--;
      break;
    }

    // transfer a frame
    word_t FRMCNT,ELECNT,FRMIDX,ELEIDX;
    FRMCNT = cnt >> 16;
    ELECNT = cnt & 0xFFFF;
    FRMIDX = idx >> 16;
    ELEIDX = idx & 0xFFFF;
    word_t ESIZE = get_uint(opt,27,2);

    // transfer a frame
    word_t ELESIZE = esize_tbl[ESIZE];
    word_t byte_cnt = ELECNT * ELESIZE;

    if(SUM == 0x3 || DUM == 0x3)
    {
      word_t src_in_frame = src;
      word_t dst_in_frame = dst;
      for(int i = 0; i < ELECNT; ++i)
      {
        phy_addr_t phy_src = l2mc->get_phy_addr(src_in_frame);
        phy_addr_t phy_dst = l2mc->get_phy_addr(dst_in_frame);
        BYTE_CPY(phy_dst,phy_src,ELESIZE);

        switch (SUM)
        {
        case 0x3:
          src_in_frame += ELEIDX;
          break;
        case 0x2:
          src_in_frame -= ELESIZE;
          break;
        case 0x1:
          src_in_frame += ELESIZE;
          break;
        default:
          break;
        }
        switch (DUM)
        {
        case 0x3:
          dst_in_frame += ELEIDX;
          break;
        case 0x2:
          dst_in_frame -= ELESIZE;
          break;
        case 0x1:
          dst_in_frame += ELESIZE;
          break;
        default:
          break;
        }
      }
    }
    else
    {
      phy_addr_t phy_src = l2mc->get_phy_addr(src);
      phy_addr_t phy_dst = l2mc->get_phy_addr(dst);
      BYTE_CPY(phy_dst,phy_src,byte_cnt);
    }
    //code_modify_detect(core,dst,byte_cnt >> 2);

    
    if(FRMCNT == 0) // transfer complete
    {
      if(opt & 0x2)
      { // LINK
        // check LINK first
        word_t rld = l2mc->mem_read_word(pa+20);
        md_addr_t link_addr = (rld & 0xFFFF) | 0x01A00000;
        phy_addr_t dst_ch_addr = l2mc->get_phy_addr(pa);
        phy_addr_t src_ch_addr = l2mc->get_phy_addr(link_addr);
        reload_ch(dst_ch_addr,src_ch_addr);
      }


      // final TR use TCC here
      // TCC process
      if(get_uint(opt,20,1))
      {
        word_t ciprl = 1 << tcc;
        word_t old_ciprl = l2mc->mem_read_word(CIPRL);
        word_t cierl = l2mc->mem_read_word(CIERL);
        
        if(ciprl & cierl) // OK generate EDMA_INT event
        { // EDMA_INT to cpu
          core->signal_evt(8); 
          //old_ciprl |= ciprl;
        }
        else
        { // clear pending in CIPRL
          //old_ciprl &= ~ciprl;
        }
        // xxx write CIPRL
        old_ciprl |= ciprl;
        l2mc->mem_load_word_xendian(CIPRL,old_ciprl);

        // get CCERL
        word_t ccsl = 1 << tcc;
        word_t ccerl = l2mc->mem_read_word(CCERL);
        if(ccsl & ccerl)
        { // set chain
          ccrl |= ccsl;
        }
      }


      // do not link remove it
      //if((opt & 0x2) == 0)

    }
    else
    {
      // update src/dst addr
      switch (SUM)
      {
      case 0:
        break;

      case 1:
        src += byte_cnt;
        break;

      case 2:
        src -= byte_cnt;
        break;

      case 3:
        src += FRMIDX;
        break;

      default:
        break;
      }

      switch (DUM)
      {
      case 0:
        break;

      case 1:
        dst += byte_cnt;
        break;

      case 2:
        dst -= byte_cnt;
        break;

      case 3:
        dst += FRMIDX;
        break;

      default:
        break;
      }
      l2mc->mem_write_word_xendian(pa+4,src);
      l2mc->mem_write_word_xendian(pa+12,dst);

      FRMCNT--;
      cnt = (FRMCNT << 16) | ELECNT;
      l2mc->mem_write_word_xendian(pa+8,cnt);

      // ATCC here
      if(get_uint(opt,12,1))
      {
        word_t ciprl = 1 << atcc;
        word_t old_ciprl = l2mc->mem_read_word(CIPRL);
        word_t cierl = l2mc->mem_read_word(CIERL);
        
#ifdef EDMA_DBG
        core->get_ofs() << "CIPRL:" << to_hex_str(old_ciprl) << "\n";
        core->get_ofs() << "CIERL:" << to_hex_str(cierl) << "\n";
#endif
        if(ciprl & cierl) // OK generate EDMA_INT event
        { // EDMA_INT to cpu
          core->signal_evt(8); 
          //old_ciprl |= ciprl;
        }
        else
        { // clear pending in CIPRL
          //old_ciprl &= ~ciprl;
        }
        // xxx write CIPRL
        old_ciprl |= ciprl;
        l2mc->mem_load_word_xendian(CIPRL,old_ciprl);
#ifdef EDMA_DBG
        core->get_ofs() << "CIPRL:" << to_hex_str(old_ciprl) << "\n";
        core->get_ofs() << "ATCC:" << to_hex_str(atcc) << "\n";
#endif

        // get CCERL
        word_t ccsl = 1 << atcc;
        word_t ccerl = l2mc->mem_read_word(CCERL);
        if(ccsl & ccerl)
        { // set chain
          ccrl |= ccsl;
        }
      }
    }

    // remove all the time
      { 
        chlist[i] = NULL;
        ch_count_after--;
      }
  }

  if(ch_count != ch_count_after)
  { // move active to the hole
    if(chlist[2] == NULL)
    {
      chlist[2] = chlist[3];
      chlist[3] = NULL;
    }
    if(chlist[1] == NULL)
    {
      chlist[1] = chlist[2];
      chlist[2] = chlist[3];
      chlist[3] = NULL;
    }
    if(chlist[0] == NULL)
    {
      chlist[0] = chlist[1];
      chlist[1] = chlist[2];
      chlist[2] = chlist[3];
      chlist[3] = NULL;
    }
    ch_count = ch_count_after;
  }

#ifdef EDMA_DBG
  core->get_ofs() << "ch_count:" << ch_count << "\n";
  core->get_ofs().flush();
#endif
}


END_NS