/* @kernelplv 
 * Замена подстроки в текстовом файле 
 * без создания нового файла.
 * Поддержка          */
 
#include <iostream>
#include "Test.h"
#include "Suite.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>

/* #include <boost/filesystem;
 * using namespace boost::filesystem;
 * g++ -std=c++17
 * -lboost_filesystem (linker option)
 */
 
using namespace TestSuite;
using namespace std;

unsigned int OS_CRorLF() 
{
  #if (defined __linux__)
      return 1; //LF
  #else
  #if (defined __WIN32__)
      return 2; //CRLF
  #else
  #if (defined __MACOS__)
      return 1; //CR
  #else
      return 0;
  #endif
  #endif
  #endif
}

void rstr(string& s) {
    reverse(s.begin(),s.end());
}


void toline(string& s) {
    for (char& c : s) {
        c = tolower(c);
    }
}


int sreplace( string&     str      ,
         const string    tmpl = " ",
         const string    trgt = "_",
                 bool protect = true ) 
{
    string aftercut ("")                           ;
    string   buffer ( str.substr(0, tmpl.size()) ) ;
    string     targ = trgt                         ;
      bool      End = false                        ;
      auto       it = str.begin() + tmpl.size()    ;

    if ( protect and targ.size() != tmpl.size() )
                 targ.resize( tmpl.size(), ' ') ;

    while ( not End ) 
    {
      if ( it >= str.end() )
                End = true ;
                
      if ( buffer != tmpl ) 
         {
           aftercut += buffer.front() ;
           buffer.erase(0, 1)         ;
           buffer += *it              ;
          
           if ( End ) 
              { 
                while ( buffer.size() > 1 )                    //* 1 because the last character of buffer(string) is NULL('\0').
                      { 
                        aftercut += buffer.front() ;
                        buffer.erase(0, 1)         ;
                      }
              }
           else 
                it++ ; 
         }
      else 
         {
           aftercut += targ                     ;
           buffer = string(it,it + tmpl.size()) ;
           it += tmpl.size()                    ;
         }
    }
    
    int resized = aftercut.size() - str.size() ;
            str = aftercut                     ;
            
    return resized ;
    
}
class test_rstr : public Test {
    string s;
public:
    test_rstr() : s(string("12345")) {};
    void run() {
        rstr(s);
        test_(s == "54321");
    }
};

void fextend(fstream& fs, char c = ' ')
{
  if( not fs.is_open() ) return;
  
  long lastReadPos = fs.tellg() ;
  char        buff = '\0'       ;
  long           T = 1          ;
  
  fs.seekp(0, ios::end) ; 
  
  for (                           ;
        lastReadPos < fs.tellp()  ;
        T++                       ) 
      {
        fs.seekp(   -(T), ios::end ) ;
        fs.clear()                   ;
        buff = fs.peek()             ;
        fs.seekp( -(T-1), ios::end ) ;    
        fs.clear()                   ;
        fs << buff                   ;
      }
}

void ftruncate(fstream& fs)
{
  if( not fs.is_open() ) return;
  
  long lastReadPos = fs.tellg()    ;
  char        buff = '\0'          ;
  long           T = lastReadPos   ;
  
  fs.seekp(T) ; 
  \
  for (              ;
        not fs.eof() ;
        T++          ) 
      {
        fs.seekp(T)       ;
        buff = fs.peek()  ;
        fs.seekp( T - 1 ) ;
        fs << buff        ;
      } 
  fs.clear()                ;
  fs.seekp(-1, ios::end)    ;
  fs << ' '                 ;
  fs.seekg(lastReadPos - OS_CRorLF())  ; 
}

    //todo github connect and anytime save-version  
int main( int argc, char** argv ) {
       
    string ifle( argv[1] ) ; //input file
    string tmpl( argv[2] ) ; //template
    string targ( argv[3] ) ; //target 
    
    if (tmpl.size() == 0 or targ.size() == 0)
       { cout << "empty template or target strings! terminate!";
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
     string        line                                    ;
  
    if ( file_stream.is_open() ) 
       {
                       bool     first_line = true        ;
              unsigned long    before_read = 0           ;
         const unsigned int END_LINE_BYTES = OS_CRorLF() ;                 //LF(U+000A) or CR(U+000D) invisible symbols
   
         do 
         {
           file_stream.sync()                ;
           before_read = file_stream.tellg() ;
           file_stream >> line               ; 
              
           cout << "Line: " 
                << line 
                << " replaced by: " 
                << endl                      ;
                   
           int changes = sreplace( line, tmpl, targ, false) ;
           while (changes > 0) 
                 { fextend(file_stream)                     ;              //* extend file by one symbol
                   changes--                                ;
                 }
           while (changes < 0)
                 { ftruncate(file_stream)                   ;              //* filling the space formed after truncation of the line
                   changes++                                ;              //* i really don't like it 
                 }
                 
           if ( first_line )
              { 
                file_stream.seekp(0)                            ;
                first_line = false                              ; 
              }
           else 
                file_stream.seekp(before_read + END_LINE_BYTES) ;                 //* CR and LF simbols..its very dangerous

//           if ( file_stream.eof() ) 
//              {                                                                 //* last chance to write last line to file
////                file_stream.clear()                             ;             //* dangerous too                                                       
////                file_stream.seekp(before_read + END_LINE_BYTES) ;
////                file_stream << line                             ;
////                file_stream.setstate(ios_base::eofbit)          ;
//              }
//           else
           file_stream << line ;
           file_stream.flush() ;
           cout << "Line: " 
                << line
                << endl        ;
             
         } while( not file_stream.eof() ) ;    
       }
    else
         cout << "File can't be opened.. terminate!" << endl ;
       
    file_stream.close()  ;

    return 0;
}
