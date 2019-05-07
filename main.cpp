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

using namespace TestSuite;
using namespace std;


template < typename T >
T& hello( T arr[], int start, int finish, int source = T())
{
  T sigma = source ;  
  cout << "Source value: " << sigma << endl ;
  
  for ( int i = start ; i <= finish ; i++ )
       sigma += arr[i]                    ;   
  
  return sigma ;
}   

int main( int argc, char** argv ) 
{
  int arr[5] = { 1, 2, 3, 4, 5} ;
  cout << "Result: " 
       << hello<int> (arr, 1, 3)
       << endl ;
  return 0;
}
