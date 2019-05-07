#include "LTools.h"

void LTools::writeline(fstream& s, const string line, const long start = -1 )
{  
  if ( not s.is_open() )
     {
       cout << "writeline: file not opened!" << endl ; 
       return ;
     } 
  
  bool lastWrite = false           ;
  if ( !s ) lastWrite = true       ;
  if ( start >= 0 ) 
     {
       s.clear()      ;                                           //* if trancate func set eof
       s.seekp(start) ;
     }
                                                       
  for ( char c : line )
      {
        s.put( c ) ;
        s.flush()  ;
      }
      
  if ( lastWrite ) s.setstate( ios::badbit) ;                     //* eof insufficient reason to break the loop "while(stream)" O_o wtf?
}

string LTools::readline(fstream& s, const char endline = '\n')
{
  if ( not s.is_open() )
     {
       cout << "readline: file not opened!" << endl ; 
       return "" ;
     } 
     
    char buff = 'G' ;   
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

string LTools::getLineTerminators(fstream& s)
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
  cout << s.tellg() <<" " << s.tellp() ;
  
  return CRLF ;        
}
void LTools::rstr(string& s) 
{
  reverse( s.begin(),s.end() ) ;
}

void LTools::toline(string& s) 
{
  for (char& c : s) 
      {
        c = tolower(c) ;
      }
}
int LTools::sreplace( string&     str      ,
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
          
           if ( End ) 
              { 
                while ( buffer.size() > 0 )                    //* 1 because the last character of buffer(string) is NULL('\0').
                      { 
                        aftercut += buffer.front() ;
                        buffer.erase(0, 1)         ;
                      }
              }
           else 
                {
                  buffer += *it ;
                  it++          ;
                }
         }
      else 
           {
             aftercut += targ ;
             buffer.clear()   ;

             unsigned int count = 0 ;
             for ( ; it < str.end() and count < tmpl.size()
                   ; it++, count++                        )
                 {
                   buffer += *it ;
                 }
             count = 0              ;
           }
    }
    
    int resized = aftercut.size() - str.size() ;
            str = aftercut                     ;
            
    return resized ;
    
}

/* Shifts characters one by one to the end of the file. 
 * Starting at the end of file                       */
void LTools::fextend(fstream& fs)
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
        fs.put(buff)                 ;
      }
  fs.seekg(lastReadPos);
}

/* Shift of characters to the current position of the read / write pointer. 
 * A space is added to the end to keep the file at the same size.
 * One call - one character shift.
 */
void LTools::ftruncate(fstream& fs, const unsigned int endlinesize = 1)
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
       
  fs.seekp(T) ; 
  
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
  fs.seekg(lastReadPos - 1)            ; 
}
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
