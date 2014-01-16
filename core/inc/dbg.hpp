#ifndef CORE_DBG_HPP
#define CORE_DBG_HPP

#include <vector>
#include <string>
#include "common/inc/def.hpp"

BEGIN_NS

class Core;

typedef std::vector<std::string> debug_param_t;

enum dbg_cont_t
{
  DBG_STEP = 0,
  DBG_HOLD = 1,
  DBG_EXIT = 2
};

class DbgBaseCmd
{
public:
  virtual dbg_cont_t operator()(Core* core,debug_param_t&) = 0;
};

class DbgDummy : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  static inline DbgBaseCmd *get_instance()
  {
    return &dbgdummy;
  }
  static DbgDummy dbgdummy;

private:
  DbgDummy(){}
  
};

class DbgHelp : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgHelp(){}
};

class DbgShowGenRegs : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgShowGenRegs(){}
};

class DbgShowContext : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgShowContext(){}
};

class DbgStep : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgStep(){}
};

class DbgGo : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgGo(){}
}; 

class DbgSetBreakPoint : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgSetBreakPoint(){}
}; 

class DbgListBreakPoint : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgListBreakPoint(){}
}; 

class DbgRemoveBreakPoint : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgRemoveBreakPoint(){}
}; 

class DbgDumpWord : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgDumpWord(){}
}; 

class DbgDumpString : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgDumpString(){}
}; 

class DbgListSymbol : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgListSymbol(){}
}; 

class DbgSetTraceFlag : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgSetTraceFlag(){}
}; 

class DbgSetCycleBreak : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgSetCycleBreak(){}
}; 

class DbgSetSkipJmp : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgSetSkipJmp(){}
}; 

class DbgSetWord : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgSetWord(){}
};

class DbgSetMemTrace : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgSetMemTrace(){}
};

class DbgSetWriteCheck : public DbgBaseCmd
{
public:
  dbg_cont_t operator()(Core* core,debug_param_t&);
  DbgSetWriteCheck(){}
}; 




END_NS

#endif