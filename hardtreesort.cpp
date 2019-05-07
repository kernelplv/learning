#include <iostream>
#include <random>
#include <ctime>
#include <cstring>

class bintree
{
      int   val ;
  bintree*  lhd ;
  bintree*  rhd ; 
  
  size_t& Count() { static size_t c = 0 ;
                    return c            ; }
                    
  bintree( const bintree& )  = delete ;
  
  public:
  bintree(int v = 0) 
  {
    val = v       ;
    lhd = nullptr ;
    rhd = nullptr ;
    ++Count()     ;
  }
  ~bintree() { --Count() ; }
  
  void push(int v)
  {       
    if ( v < val and !lhd)
       lhd = new bintree(v) ;
    else 
    if ( v < val and lhd )
       lhd->push(v) ;
    else
    if ( !rhd )
       rhd = new bintree(v) ;
    else
    if ( rhd )
       rhd->push(v) ; 
  }
  void extractTo(int*& dest)
  {
    static int* O = ( new int[Count()] ) + Count()*sizeof(int) ;
  
    if ( rhd )
       rhd->extractTo(dest) ;
          
    *O = val ; 
     O--     ; 
     
     
    if ( lhd )
       lhd->extractTo(dest) ;  
    
    if ( Count() == 1 )
       {
         O++ ;
         delete[] dest ;
         std::swap(dest, O) ;
       }
        
    delete this ;
  }
};

class TreeSort
{
  TreeSort() = delete ;
  
 public:
  int* A    ;
  int  size ;
  
  TreeSort(int* I, const int size)   ;
  //~TreeSort()                      ;
  
  friend int* operator<<(int* I, TreeSort nA) ;
  friend int* operator>>(TreeSort nA, int* I) ;
};

TreeSort::TreeSort(int* I, const int size)
{
  this->size = size ;  
  A = new int[size]{0} ;
  
  std::copy(I, I + size, A);
  
      int*    F = A                   ;
      int*    L = A + size - 1        ;
  bintree* tree = new bintree( A[0] ) ;
  
  for ( int i = 1 ; i < size ; i++ )
      {
        tree->push( A[i] ) ;
      }
  
  tree->extractTo(A) ;

}

int* operator<< (int* I, TreeSort nA)
{
  std::copy(nA.A, nA.A + nA.size, I);

  return nA.A ;
}

int* operator>> (TreeSort nA, int* I)
{
  std::copy(nA.A, nA.A + nA.size, I);
  
  return nA.A;
}

int main(int argc, char** argv)
{
    const int size = 16 ;
    std::default_random_engine      rengine( (unsigned int)time(nullptr) ) ;
    std::uniform_int_distribution<> rangerand(0, 10)                       ;
    rangerand(rengine)                                                     ;  
              
    int* A = new int[size];
    for (int i = 0 ; i < size ; i++)
    {
      A[i] = rangerand(rengine) ;
    }
    
    std::cout << "start with: [ " ;
    
    for (int i = 0; i < size ; i++)
    {
      std::cout << A[i] << " "    ;
    }
    
    std::cout << "]" << std::endl ;
    
    
    
    A << TreeSort(A, size);
    
    std::cout << "end with:   [ " ;
    
    for (int i = 0; i < size ; i++)
    {
      std::cout << A[i] << " " ;
    }
    
    std::cout << "]" << std::endl ;
    
    return 0 ;
}