#include<iostream>
#include<fstream>
#include<iomanip>
#include "Racer.h"

using namespace std;

bool readHash(HashedDictionary<string, Racer>* dict, string &inputFIleName, int &numElem);



int main()
{
  //size of hash table
  //const int TABLE_SIZE = 10; this will be in the hash table adt file
  
  //racer* driver1 = new racer;
  //racer->buildHashTable( TABLE_SIZE );

  return 0;
}


bool readHash(HashedDictionary<string, Racer>* dict, string &inputFIleName, int &numElem)
{
  bool created = false;
  bool inserted = false;
  int i = 0;
  int stringIterator = 0;
  int newDate;
  string newName;
  
}
// too tired... will fk w/ it tomorrow, the wording for this assignment 
// says we have to save to dynamic memory and then assign value to the hash...
// will have to ask specifics.
