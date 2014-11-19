#include<iostream>
#include "racer.h"

using namespace std;

int main()
{
  //size of hash table
  const int TABLE_SIZE = 10;
  
  racer* driver1 = new racer;
  racer->buildHashTable( TABLE_SIZE );

  return 0;
}
