#include <iostream>
#include <random>
#include <ctime>
#include <cstring>

class InsertionSort
{
  InsertionSort() = delete ;
  
 public:
  int* A    ;
  int  size ;
  
  InsertionSort(int* I, const int size)   ;
  //~InsertionSort()                      ;
  
  friend int* operator<<(int* I, InsertionSort nA) ;
  friend int* operator>>(InsertionSort nA, int* I) ;
};

InsertionSort::InsertionSort(int* I, const int size)
{
  this->size = size ;  
  A = new int[size]{0} ;
  
  std::copy(I, I + size, A);
  
  int* F = A            ;
  int* L = A + size - 1 ;
  for (; F < L ; F++ )
      {
        int* j = F + 1; 
        while ( *j < *(j - 1) and j > A)
        {
            std::swap( *j, *(j - 1) );
            j--;
        }
      }  
}

int* operator<< (int* I, InsertionSort nA)
{
  std::copy(nA.A, nA.A + nA.size, I);

  return nA.A ;
}

int* operator>> (InsertionSort nA, int* I)
{
  std::copy(nA.A, nA.A + nA.size, I);
  
  return nA.A;
}

int main(int argc, char** argv)
{
    const int size = 8 ;
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
    
    
    
    A << InsertionSort(A, size);
    
    std::cout << "end with:   [ " ;
    
    for (int i = 0; i < size ; i++)
    {
      std::cout << A[i] << " " ;
    }
    
    std::cout << "]" << std::endl ;
    
    return 0 ;
}