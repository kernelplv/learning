/* @kernelplv 
 * Замена подстроки в текстовом файле 
 * без создания нового файла.
 */
 
#include <iostream>
#include "Test.h"
#include "Suite.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "LTools.h"

/* #include <boost/filesystem;
 * using namespace boost::filesystem;
 * g++ -std=c++17
 * -lboost_filesystem (linker option)
 * MinGW has a bug with filesystem library c++17
 */
 
using namespace TestSuite;
using namespace std;


int main( int argc, char** argv ) {
       
    string ifle( argv[1] ) ; //input file
    string tmpl( argv[2] ) ; //template
    string targ( argv[3] ) ; //target 
    
    if (tmpl.size() == 0 or targ.size() == 0)
       { 
         cout << "empty template or target strings! terminate!";
         return 0;
       }
    
    cout << "args: " 
         << ifle 
         << " " 
         << targ 
         << " " 
         << tmpl 
         << endl; 
    
    fstream file_stream (ifle, fstream::binary | fstream::in | fstream::out) ;
     string        line                                                      ;
  
    if ( file_stream.is_open() ) 
       {
                       bool     first_line = true                                    ;
              unsigned long    before_read = 0                                       ;
               const string        endline = LTools::getLineTerminators(file_stream) ;    
         const unsigned int END_LINE_BYTES = endline.size()                          ; //* LF(U+000A) or CR(U+000D) invisible symbols               
   
         do 
         {
           before_read = file_stream.tellg()                        ;
           line = LTools::readline( file_stream, endline.back() )   ;
              
           cout << "Line: " 
                << line 
                << " replaced by: " 
                << endl ;
                   
           int changes = LTools::sreplace( line, tmpl, targ, false) ;
           while (changes > 0) 
                 { 
                   LTools::fextend(file_stream)                     ;        //* extend file by one symbol
                   changes--                                        ;
                 }
           while (changes < 0)
                 { 
                   LTools::ftruncate(file_stream, END_LINE_BYTES)   ;        //* filling the space formed after truncation of the line
                   changes++                                        ;        //* i really don't like it 
                 }
                 
           if ( first_line )
              { 
                file_stream.clear()                ;  
                file_stream.seekp(0)               ;
                first_line = false                 ; 
              }
           else 
                file_stream.seekp(before_read + 0) ;                       //* + CR and LF simbols..its very dangerous

           LTools::writeline(file_stream, line, before_read) ;
           file_stream.flush()                               ;

           cout << "Line: " 
                << line
                << endl ;
             
         } while( file_stream ) ;    
       }
    else
         cout << "File can't be opened.. terminate!" << endl ;
       
    file_stream.close()  ;

    return 0;
}
