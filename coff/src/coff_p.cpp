#include <iostream>
#include "coff/inc/coff_parser.hpp"

using namespace std;
/*
int main(int argc,char** argv){
  if(argc < 2){
    cout << "need file path" << endl;
    system("pause");
    return 1;
  }

  const char* file_path = argv[1];
  cout << file_path << "\n";

  COFF_parser *p_coffParser = new COFF_parser(file_path);
  try
  {
    p_coffParser->parse();
  }
  catch (COFF_Parse_Error* e)
  {
    e;
    cout << "parse error" << "\n";
  }


  delete p_coffParser;

  system("pause");
}
*/