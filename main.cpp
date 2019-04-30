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
#include "LTools.h"
#include <random>
#include <ctime>
#include <vector>


/* #include <boost/filesystem;
 * using namespace boost::filesystem;
 * g++ -std=c++17
 * -lboost_filesystem (linker option)
 * MinGW has a bug with filesystem library c++17
 */
 
using namespace TestSuite;
using namespace std;

template<typename> class tipizer;

template<typename BoxType, class Typizer = tipizer<BoxType>, int tsize = 10>
class VectorUser
{
  vector<BoxType> v ;
  
 public:
  VectorUser()
  { 
    default_random_engine      rengine( (unsigned int)time(nullptr) ) ;
    uniform_int_distribution<> rangerand(-10, 10)                     ;
    rangerand(rengine)                                                ;     //* First number it is FAKE, constant FAKE. why? a dont know..
    
    for ( int t = tsize ; t > 0 ; t-- )
         v.push_back(rangerand(rengine)) ;
  }
  typename vector<BoxType>::iterator begin() { return v.begin() ; }
  typename vector<BoxType>::iterator   end() { return v.end()   ; }

  BoxType& operator[](int i) { return v[i] ; }
};

template<typename BoxType>
class VectorUser<BoxType, tipizer<char> >
{
  vector<BoxType> v ;
  
 public:
  VectorUser()
  { 
    default_random_engine      rengine( (unsigned int)time(nullptr) ) ;
    uniform_int_distribution<> rangerand(65, 90)                      ;
    rangerand(rengine)                                                ;     
    
    for ( int t = 10 ; t > 0 ; t-- )
         v.push_back(rangerand(rengine)) ;
         
    cout << "Choose this version of VectorUser by template tipizer<>" << endl ;
  }
  typename vector<BoxType>::iterator begin() { return v.begin() ; }
  typename vector<BoxType>::iterator   end() { return v.end()   ; }

  BoxType& operator[](int i) { return v[i] ; }
};

template<typename BoxType>
class VectorUser<BoxType, tipizer<string> >
{
  vector<char> v ;
  
 public:
  VectorUser()
  { 
    mt19937      rengine( (unsigned int)time(nullptr) ) ;
    uniform_int_distribution<> rangerand(65, 90)                      ;
    rangerand(rengine)                                                ;    
    
    for ( int t = 10 ; t > 0 ; t-- )
         v.push_back( static_cast<char>(rangerand(rengine)) ) ;
         
    cout << "Plain text version of VectorUse." << endl        ;
  }
  typename vector<char>::iterator begin() { return v.begin() ; }
  typename vector<char>::iterator   end() { return v.end()   ; }

  char& operator[](int i) { return v[i] ; }
};

template<typename T>
class typizer
{
 public:
  const bool text = false ;
};

template<>
class typizer<char>
{
 public:
  const bool text = true ;
};

int main( int argc, char** argv ) 
{
  VectorUser<int> V;
  
  for (auto v : V)
       cout << "int Vector: " << v << endl;
  
  VectorUser<int,tipizer<char> > VC;
  
  for (auto v : VC)
       cout << "char Vector: " << static_cast<char>(v) << endl;    
  
  VectorUser<int,tipizer<string> > VT;
  
  for (auto v : VT)
       cout << "text Vector: " << v << endl;       
  return 0;
}
