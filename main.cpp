#include<iostream>
#include<fstream>
#include<iomanip>
#include "Racer.h"
#include "BinarySearchTree.h"
#include "HashedDictionary.h"
#include "LinkedList.h"


using namespace std;

const int MAX_ENTRIES = 200;

bool readFileHash(HashedDictionary<string, Racer>* dict, string *&stringPtr, 
			  string &inputFileName, int &numElem);
void display(Racer &rc);
void displayMenu();
void switchMenu(HashedDictionary<string, Racer>* dict, string inputStr);
void displayStats(HashedDictionary<string, Racer>* dict);

int main()
{
    HashedDictionary<string, Racer>* racerDictionary = new HashedDictionary<string, Racer>();
	string inputFile;
	string inputStr;
	string *stringArr = nullptr;
	int numElem = 0;
	bool boolVar = false;
	int tempCount = 0;

	if(readFileHash(racerDictionary, stringArr, inputFile, numElem))
	{
		racerDictionary->traverse(display);
		while(getline(cin, inputStr))
		{
			if(inputStr.empty())
				cout << "Invalid input, Please enter valid input or press M to show help menu.\n\n";
			else if(inputStr.at(0) != 'Q')
				switchMenu(racerDictionary, inputStr);
			else
				break;
		}
	}
  return 0;
}



void display(Racer &rc)
{
	cout << rc.getName() << endl;
	cout << rc.getIdNum() << endl;
	cout << rc.getCircuitName() << endl;
	cout << rc.getDate() << endl;
	cout << rc.getFinishTime() << endl << endl;
}


// The readFile function has three reference parameters.
// The function saves the filename of the file it opens to the
// reference string parameter (in case saving file on exit needs to be 
// implemented). The function creates a string array of the data 
// contained in the input text file and then sets the reference
// string pointer variable to point to that array. The number of
// elements saved to the string array is saved to the int reference
// parameter. The function returns true if the file is read and false
// if the file fails to open or the string array is empty.
bool readFileHash(HashedDictionary<string, Racer>* dict, string *&stringPtr, 
				  string &inputFileName, int &numElem)
{
	ifstream inFile;
	string readString;
	bool notEmpty = false;
	string *stringArr = new string[MAX_ENTRIES]();
	int i = 0;

	inFile.open("inputRacer.txt");
	if(!inFile)
	{
		cout << "Error opening racer.txt Closing...\n";
		return notEmpty;
	}
	else
		inputFileName = "inputRacer.txt";
	while(getline(inFile, readString) && i < MAX_ENTRIES)
	{
		stringArr[i] = readString;
		Racer *newRacer = new Racer(&stringArr[i]);
		++i;
		if(getline(inFile, readString) && i < MAX_ENTRIES)
		{
			stringArr[i] = readString;
			newRacer->setIdNum(&stringArr[i]);
			++i;
		}
		if(getline(inFile, readString) && i < MAX_ENTRIES)
		{
			stringArr[i] = readString;
			newRacer->setCircuitName(&stringArr[i]);
			++i;
		}
		if(getline(inFile, readString) && i < MAX_ENTRIES)
		{
			stringArr[i] = readString;
			newRacer->setDate(&stringArr[i]);
			++i;
		}
		if(getline(inFile, readString) && i < MAX_ENTRIES)
		{
			stringArr[i] = readString;
			newRacer->setFinishTime(&stringArr[i]);
			++i;
		}
		dict->add(newRacer->getIdNum(), *newRacer);
	}

	if(stringArr[0].empty())
		return notEmpty;
	else
		notEmpty = true;


	stringPtr = stringArr;
	numElem = i;
	return notEmpty;
}


void switchMenu(HashedDictionary<string, Racer>* dict, string inputStr)
{
	switch(inputStr.at(0))
	{
	case 'A' : 
		break;
	case 'D' : dict->traverse(display);
		break;
	case 'P' : 
		{
		int index = 0;
		//dict->specialTraverse(specialDisplay, indexDisplay, index);
		break;
		}
	case 'T' : displayStats(dict);
		break;
	case 'M' : displayMenu();
		break;
	default : cout << "Invalid choice, enter a valid choice or enter 'M' for help menu.\n\n";
	}
}

// the displayMenu function displays the options for the switchMenu function
// which drives the program. Accepts no parameters and returns nothing.
void displayMenu()
{
	cout << "Enter a value as shown below to view data from list of Racers.\n\n";
	cout << "S        : Search the list by racer Name(Case Sensitive).\n";
	cout << "D        : Display the Hashed Table of Racers.\n";
	cout << "P        : Display the Hashed Table in indented form.\n";
	cout << "T        : Show Statistics.\n";
	cout << "M        : Display this Menu.\n";
	cout << "Q        : Quit.\n\n";
}


void displayStats(HashedDictionary<string, Racer>* dict)
{
	int numCollisions = dict->getNumCollisions();
	int numLists = dict->getNumLinkedLists();
	int hashedArraySize = dict->getTableSize();
	int numItems = dict->getNumberOfItems();
	int emptyCount = dict->getNumEmptyElements();
	int numItemsInLongest = 0;
	int longestIndex = dict->getLongestIndex(numItemsInLongest);

	cout << "There were " << numCollisions << " collisions making the hash table.\n";
	cout << "There are " << numLists << " Linked Lists in the hash table.\n";
	cout << "The Load Factor was " << hashedArraySize-emptyCount << "/" << hashedArraySize << endl;
	cout << "The average number of nodes per Linked List is " << static_cast<float>(numCollisions)/numLists << endl;
	cout << "The longest Linked List is at Index " << longestIndex
		<< " with " << (numItemsInLongest-1) << " nodes in the list." << endl;
}