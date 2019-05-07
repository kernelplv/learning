#include <iostream>
#include <random>
#include <ctime>
#include <cstring>
#include <set>

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
  
  int* F = A            ;
  int* L = A + size - 1 ;
  std::multiset<int> t  ;
  for (; F < L ; F++ )
      {
        t.insert(*F);
      }
  F = A ;
  for ( int v : t )
      {
        *F = v ;
         F++   ;
      }
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