
/* Secondary tools created in the learning process
*/ 

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class LTools
{
  LTools() = delete                            ;
 ~LTools() = delete                            ;
  LTools( LTools const & ) = delete            ;
  LTools& operator=( LTools const & ) = delete ;
public:
  static   void writeline(fstream& s, const string line, const long start ) ;
  static string readline(fstream& s, const char endline )                   ;
  static string getLineTerminators(fstream& s)                              ;
  static   void rstr(string& s)                                             ;
  static   void toline(string& s)                                           ;
  static    int sreplace( string& str, const string tmpl,                   \
                          const string trgt, bool protect )                 ;
  static   void fextend(fstream& fs)                                        ;
  static   void ftruncate(fstream& fs, const unsigned int endlinesize )     ;
                          
};

unsigned int OS_CRorLF();


