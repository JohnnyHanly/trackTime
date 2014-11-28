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
bool createTree(HashedDictionary<string, Racer>* dict, BinarySearchTree<Racer>* tree);
void display(Racer &rc);
void printLabels();
void displayIndent(int &indent);
void addToTree(Racer &rc, BinarySearchTree<Racer> *&tree);
void displayMenu();
void switchMenu(HashedDictionary<string, Racer>* dict, BinarySearchTree<Racer>* tree, string inputStr);
void displayStats(HashedDictionary<string, Racer>* dict);
void searchByName(BinarySearchTree<Racer>* tree);
void searchById(HashedDictionary<string, Racer>* dict);

int main()
{
    HashedDictionary<string, Racer>* racerDictionary = new HashedDictionary<string, Racer>();
	BinarySearchTree<Racer>* racerTree = new BinarySearchTree<Racer>();
	string inputFile;
	string inputStr = " ";
	string *stringArr = nullptr;
	int numElem = 0;
	bool boolVar = false;
	int tempCount = 0;
	
	if(readFileHash(racerDictionary, stringArr, inputFile, numElem))
	{
		racerDictionary->traverse(addToTree, racerTree);
		while(inputStr[0] != 'Q')
		{
			cout << "[CIS22C@racer]$ ";
			getline(cin, inputStr);
			if (inputStr[0] == 'Q')
				break;
			switchMenu(racerDictionary, racerTree, inputStr);
		}
	}
	
	
  return 0;
}



void display(Racer &rc)
{
	cout << setw(17);
	cout << left << *(rc.getName());
	cout << setw(10) << *(rc.getIdNum());
	cout << setw(16) << *(rc.getCircuitName());
	cout << setw(11) << *(rc.getDate());
	cout << setw(8) << *(rc.getFinishTime()) << endl;
}

void printLabels()
{
	cout << setw(17);
	cout << left << "NAME";
	cout << setw(10) << "ID NUMBER";
	cout << setw(15) << "CIRCUIT NAME";
	cout << setw(11) << "DATE";
	cout << setw(8) << "FIN TIME" << endl;
}

void displayIndent(int &indent)
{
	cout << setw(2*indent) << right << indent << ' ';
}

void addToTree(Racer &rc, BinarySearchTree<Racer> *&tree)
{
	tree->insert(rc);
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
		dict->add(*(newRacer->getIdNum()), *newRacer);
	}

	if(stringArr[0].empty())
		return notEmpty;
	else
		notEmpty = true;


	stringPtr = stringArr;
	numElem = i;
	return notEmpty;
}


void switchMenu(HashedDictionary<string, Racer>* dict, BinarySearchTree<Racer>* tree, string inputStr)
{
	switch(inputStr[0])
	{
	case 'A' : 
		break;
	case 'D' : printLabels();
		dict->traverse(display);
		break;
	case 'F' : searchById(dict);
		break;
	case 'I': tree->preOrder(display, displayIndent, 1);
		break;
	case 'P' : printLabels();
		tree->inOrder(display);
		break;
	case 'T' : displayStats(dict);
		break;
	case 'M' : displayMenu();
		break;
	case 'S': searchByName(tree);
		break;
	default:
		cout << "Usage: Enter M for available commands\n\n";
	}
}

// the displayMenu function displays the options for the switchMenu function
// which drives the program. Accepts no parameters and returns nothing.
void displayMenu()
{
	cout << "-----HELP MENU-----\n" <<
		"S SEARCH USING RACER NAME (case sensitive)\n"
		"F SEARCH USING RACER ID NUMBER(8 CHARACTERS)\n"
		"D DISPLAY HASHED TABLE OF RACERS\n"
		"P DISPLAY DRIVERS IN ALPHABETICAL ORDER(FIRST NAME)\n"
		"T SHOW HASH TABLE STATISTICS\n"
		"I DISPLAY DRIVERS IN INDENTED TREE FORM\n"
		"M SHOW THIS MENU (BUT YOU ALREADY KNOW THAT)\n"
		"Q EXIT PROGRAM (GOODBYE)\n";
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

	/*
	cout << "There were " << numCollisions << " collisions making the hash table.\n";
	cout << "There are " << numLists << " Linked Lists in the hash table.\n";
	cout << "The Load Factor was " << hashedArraySize-emptyCount << "/" << hashedArraySize << endl;
	cout << "The average number of nodes per Linked List is " << static_cast<float>(numCollisions)/numLists << endl;
	cout << "The longest Linked List is at Index " << longestIndex
		<< " with " << (numItemsInLongest-1) << " nodes in the list." << endl;
*/

	cout << "\n---------HASH TABLE STATISTICS---------\n\n";
	
	//smaller the barsize, the longer the graph. lol
	int barSize = 4;
	cout << "  HASH TABLE LOAD FACTOR       : ";
	float load = float(hashedArraySize - emptyCount) / float(hashedArraySize) * 100;
	cout << "[";
	float progress = load / barSize;
	float max = hashedArraySize / barSize;
	for (int i = 0; i < progress; i++)
	{
		cout << '#';
	}
	for (int i = 1; i < max; i++)
	{
		cout << '-' << '-';
	}
	cout << "] " << load << '%' << endl;
	
	cout << "  EMPTY SPACES                 : " << emptyCount << "\n";
	cout << "  HASH TABLE SIZE              : " << hashedArraySize << "\n";
	cout << "  TOTAL NUMBER OF ITEMS        : " << numItems << "\n";
	cout << "  NUMBER OF COLLISIONS         : " << numCollisions << "\n";
	cout << "  NUMBER OF LINKED LISTS       : " << numLists << "\n";
	cout << "  LARGEST LINKED LIST          : " << numItemsInLongest - 1 << "\n";
	cout << "  INDEX OF LARGEST LINKED LIST : " << longestIndex << "\n";
	cout << "  AVERAGE LINKED LISTS         : " << float(numItems) / float(hashedArraySize - emptyCount) << "\n\n";
	
}

void searchByName(BinarySearchTree<Racer> *tree)
{
	Racer *searchRacer;
	Racer foundRacer;
	string tempStr;


	cout << "\nPlease enter the name of the racer you are looking for(17 char max)\n";
	getline(cin, tempStr);
	//cin.ignore();
	if(tempStr.length() > 17)
	{
		cout << "17 characters maximum! Press S to try again.\n";
		return;
	}
	searchRacer = new Racer(&tempStr);
	if(tree->getEntry(*searchRacer, foundRacer))
	{
		cout << "\nRACER FOUND!\n";
		display(foundRacer);
	}
	else
		cout << "\nRACER NOT FOUND!\n";
	delete searchRacer;
}


void searchById(HashedDictionary<string, Racer>* dict)
{
	ListNode<string, Racer>* nodePtr;
	string searchString;
	cout << "Please enter the ID number that you are searching for(8 char max).\n"; 
	getline(cin, searchString);
	if(searchString.length() > 8)
	{
		cout << "ID NUMBERS ARE 8 CHAR MAX!\n";
		return;
	}
	nodePtr = dict->getItem(searchString);
	if(nodePtr)
	{
		cout << "RACER FOUND!\n";
		display(nodePtr->getValue());
	}
	else
		cout << "NO RACER FOUND WITH THAT ID.\n";

}