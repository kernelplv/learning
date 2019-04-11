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

/* #include <boost/filesystem;
 * using namespace boost::filesystem;
 * g++ -std=c++17
 * -lboost_filesystem (linker option)
 * MinGW has a bug with filesystem library c++17
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
void writeline(fstream& s, const string line)
{  
  if ( not s.is_open() )
     {
       cout << "writeline: file not opened!" << endl ; 
       return ;
     } 
  
  bool lastWrite = false          ;
  if ( s.eof() ) lastWrite = true ;
  
  s.clear() ;                                                     //* if trancate func set eof
  for ( char c : line )
      {
        s.put( c ) ;
        s.flush()  ;
      }
  if ( lastWrite ) s.setstate( ios::badbit) ;                     //* eof insufficient reason to break the loop "while(stream)" O_o wtf?
}
string readline(fstream& s, const char endline = '\n')
{
  if ( not s.is_open() )
     {
       cout << "readline: file not opened!" << endl ; 
       return "" ;
     } 
     
    char buff = '\0' ;   
  string line = ""   ;
  
  while ( s and buff != endline)
        {
          buff = s.get() ;
          if (not s) 
             {
               s.setstate(ios::eofbit) ;  
               return line             ;                          //* in example if read endOFfile symbol
             }
          line += buff   ;
        }
  
  return line ;
}

string getLineTerminators(fstream& s)
{
  string        CRLF = ""    ;  
    bool CR_detected = false ;
  
  if ( not s.is_open() )
     {
       cout << "getLineTerminators: file not opened!" << endl ; 
       return "" ;
     }
     
  long gpos = s.tellg() ;
  char buff = '\0'      ;
  
  while ( not s.eof() ) 
        {
          buff = s.get(); 
          if ( buff != '\n' and CR_detected ) 
                                      break ;
          if ( buff == '\r' and not CR_detected )                                         //*ohh my god windows...
             {                 
               CRLF += buff       ;
               CR_detected = true ;
             }
          if ( buff == '\n' ) CRLF += buff ;
          
          
        }
  s.clear()     ;
  s.seekg(gpos) ;
  cout << s.tellg() <<" " << s.tellp();
  return CRLF ;
        
}

void rstr(string& s) 
{
  reverse(s.begin(),s.end());
}


void toline(string& s) 
{
  for (char& c : s) 
      {
        c = tolower(c) ;
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
class test_rstr : public Test 
{
  string s;
public:
  test_rstr() : s(string("12345")) {};
  void run() 
  {
    rstr(s);
    test_(s == "54321");
  }
};


/* Shifts characters one by one to the end of the file. 
 * Starting at the end of file                       */
void fextend(fstream& fs)
{
  if( not fs.is_open() ) return;
  
  long lastReadPos = fs.tellg() ;
  char        buff = '\0'       ;
  long           T = 1          ;
  
  fs.seekp(0, ios::end) ; 
  
  for (; lastReadPos < fs.tellp() ; T++ ) 
      {
        fs.seekp(   -(T), ios::end ) ;
        fs.clear()                   ;
        buff = fs.peek()             ;
        fs.seekp( -(T-1), ios::end ) ;    
        fs.clear()                   ;
        fs << buff                   ;
      }
  fs.clear();
}

void ftruncate(fstream& fs, const unsigned int endlinesize = 1)
{
  if( not fs.is_open() ) return;
  
           long lastReadPos = fs.tellg()  ;
  unsigned long   endOfFile = 0           ;    
           char        buff = '\0'        ;
           long           T = lastReadPos ;
    static long        last = 0           ;
  
  fs.seekg(-1, ios::end) ;
  endOfFile = fs.tellg() ;
  fs.seekg(lastReadPos)  ;
  
  if ( lastReadPos < 0 or last )                                               //* If the last line
     { 
       fs.clear() ; 
       if ( not last )
          {
            fs.seekg(-1, ios::end) ;  
            last = fs.tellg()      ; 
          }
       fs.seekp(last) ;
       fs << ' '      ;
       fs.flush()     ;
       last--         ; 
       fs.setstate(ios::eofbit);
       return ;
     }
  else 
       last = 0       ;
       
  fs.seekp(T) ; \
  
  for ( ; fs.tellp() < endOfFile ; T++ ) 
      {
        fs.seekp(T)       ;
        buff = fs.get()   ;
        fs.seekp( T - 1 ) ;
        fs.put(buff)      ;
        fs.flush()        ;
      } 
  fs.clear()                           ;
  fs.seekp(-1, ios::end)               ;
  fs << ' '                            ;
  fs.flush()                           ;
  int tt = fs.tellg();
  fs.seekg(lastReadPos - 1) ; 
}


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
                       bool     first_line = true                            ;
              unsigned long    before_read = 0                               ;
               const string        endline = getLineTerminators(file_stream) ;    
         const unsigned int END_LINE_BYTES = endline.size()                  ;            //* LF(U+000A) or CR(U+000D) invisible symbols               
   
         do 
         {
           before_read = file_stream.tellg()              ;
           line = readline( file_stream, endline.back() ) ;
              
           cout << "Line: " 
                << line 
                << " replaced by: " 
                << endl ;
                   
           int changes = sreplace( line, tmpl, targ, false) ;
           while (changes > 0) 
                 { 
                   fextend(file_stream)                     ;              //* extend file by one symbol
                   changes--                                ;
                 }
           while (changes < 0)
                 { 
                   ftruncate(file_stream, END_LINE_BYTES)   ;              //* filling the space formed after truncation of the line
                   changes++                                ;              //* i really don't like it 
                 }
                 
           if ( first_line )
              { 
                file_stream.clear()                ;  
                file_stream.seekp(0)               ;
                first_line = false                 ; 
              }
           else 
                file_stream.seekp(before_read + 0) ;                       //* CR and LF simbols..its very dangerous

           writeline(file_stream, line) ;
           file_stream.flush() ;

           cout << "Line: " 
                << line
                << endl        ;
             
         } while( file_stream ) ;    
       }
    else
         cout << "File can't be opened.. terminate!" << endl ;
       
    file_stream.close()  ;

    return 0;
}
