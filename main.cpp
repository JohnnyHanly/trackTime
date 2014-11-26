#include<iostream>
#include<fstream>
#include<iomanip>
#include "Racer.h"
#include "BinarySearchTree.h"
#include "HashedDictionary.h"
#include "LinkedList.h"


using namespace std;

bool readFile(string *&stringPtr, string &inputFileName, int &numElem);
bool createHash(HashedDictionary<string, Racer>* dict, string* stringArr, int numElem);



int main()
{
  HashedDictionary<string, Racer>* racerDictionary = new HashedDictionary<string, Racer>();
	string inputFile;
	string inputStr;
	string *stringArr = nullptr;
	int numElem = 0;
	bool boolVar = false;
	int tempCount = 0;

	if(readFile(stringArr, inputFile, numElem))
	  boolVar = createHash

  return 0;
}


bool createHash(HashedDictionary<string, Racer>* dict, string* stringArr, int numElem)
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


// The readFile function has three reference parameters.
// The function saves the filename of the file it opens to the
// reference string parameter (in case saving file on exit needs to be 
// implemented). The function creates a string array of the data 
// contained in the input text file and then sets the reference
// string pointer variable to point to that array. The number of
// elements saved to the string array is saved to the int reference
// parameter. The function returns true if the file is read and false
// if the file fails to open or the string array is empty.
bool readFile(string *&stringPtr, string &inputFileName, int &numElem)
{
	ifstream inFile;
	string readString;
	bool notEmpty = false;
	string *stringArr = new string[MAX_ENTRIES]();
	int i = 0;

	inFile.open("racer.txt");
	if(!inFile)
	{
		cout << "Error opening racer.txt Closing...\n";
		return notEmpty;
	}
	else
		inputFileName = "racer.txt";
	while(getline(inFile, readString) && i < MAX_ENTRIES)
	{
		stringArr[i] = readString;
		++i;
	}

	if(stringArr[0].empty())
		return notEmpty;
	else
		notEmpty = true;


	stringPtr = stringArr;
	numElem = i;
	return notEmpty;
}
