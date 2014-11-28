#include<iostream>
#include<fstream>
#include<iomanip>
#include "Racer.h"
#include "BinarySearchTree.h"
#include "HashedDictionary.h"
#include "LinkedList.h"


using namespace std;

const int MAX_ENTRIES = 200;
const int MAX_NAME = 17;
const int MAX_ID = 8;
const int MAX_CIRCUIT = 15;
const int MAX_DATE = 10;
const int MAX_FINISH = 7;

bool readFileHash(HashedDictionary<string, Racer>* dict, string *&stringPtr, 
			  string &inputFileName, int &numElem);
//bool createTree(HashedDictionary<string, Racer>* dict, BinarySearchTree<Racer>* tree);
bool isName(string str);
bool isId(string str);
bool isCircuit(string str);
bool isDate(string str);
bool isTime(string str);

void addRacer(HashedDictionary<string, Racer>* dict, BinarySearchTree<Racer>* tree,
			  string *stringArr, int &numElem);
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
			if(inputStr[0] == 'A')
				addRacer(racerDictionary, racerTree, stringArr, numElem);
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
		cout << "Error opening inputRacer.txt Closing...\n";
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

bool isName(string str)
{
	int i = 0;
	while(i < str.length())
	{
		if(!isalpha(str.at(i)) && !isspace(str.at(i)))
			return false;
		++i;
	}
	return true;
}

bool isId(string str)
{
	int i = 0;
	while(i < str.length())
	{
		if(i == 0)
		{
			if(!isalpha(str.at(i)))
				return false;
		}
		else
		{
			if(!isdigit(str.at(i)))
				return false;
		}
		++i;
	}
	return true;
}

bool isCircuit(string str)
{
	int i = 0;
	while(i < str.length())
	{
		if(!isalpha(str.at(i)) && !isspace(str.at(i)))
			return false;
		++i;
	}
	return true;
}

bool isDate(string str)
{
	int i = 0;
	while(i < str.length())
	{
		if(i == 2 || i == 5)
		{
			if(str.at(i) != '/')
				return false;
		}
		else
		{
			if(!isdigit(str.at(i)))
				return false;
		}
		++i;
	}
	return true;
}

bool isTime(string str)
{
	int i = 0;
	while(i < str.length())
	{
		if(i == str.length()-3)
		{
			if(str.at(i) != '.')
				return false;
		}
		else
		{
			if(!isdigit(str.at(i)))
				return false;
		}
		++i;
	}
	return true;
}



void addRacer(HashedDictionary<string, Racer>* dict, BinarySearchTree<Racer>* tree,
			  string *stringArr, int &numElem)
{
	Racer *newRacer;
	int i = numElem;
	if(numElem+5 > MAX_ENTRIES)
	{
		cout << "SORRY, THE LIST IS TOO FULL. DELETE A RACER TO MAKE ROOM.\n";
		return;
	}
	cout << "INPUT FORMAT:\n"
		"NAME    : 17 CHAR MAX, FIRST LAST.\n"
		"  ID    : 8 CHAR MAX.\n"
		"CIRCUIT : 15 CHAR MAX.\n"
		"DATE    : MM/DD/YYY.\n"
		"FIN TIME: TIME TO FINISH RACE IN SECONDS TO 2 DECIMAL PLACES.\n";
	cout << "Enter the name of the racer to add:\n";
	getline(cin, stringArr[i]);
	if(stringArr[i].length() > MAX_NAME)
	{
		cout << "NAME TOO LONG, PRESS A TO TRY AGAIN.\n";
		stringArr[i].clear();
		return;
	}
	else if(!isName(stringArr[i]))
	{
		cout << "INVALID NAME, PRESS A TO TRY AGAIN.\n";
		stringArr[i].clear();
		return;
	}
	else
	{
		newRacer = new Racer(&stringArr[i]);
		++i;
	}
	cout << "Enter the ID number of the racer:\n";
	getline(cin, stringArr[i]);
	if(stringArr[i].length() > MAX_ID)
	{
		cout << "ID NUMBER TOO LONG, PRESS A TO TRY AGAIN.\n";
		while(i >= numElem)
		{
			stringArr[i].clear();
			--i;
		}
		delete newRacer;
		return;
	}
	else if(!isId(stringArr[i]))
	{
		cout << "INVALID ID NUMBER, PRESS A TO TRY AGAIN.\n";
		while(i >= numElem)
		{
			stringArr[i].clear();
			--i;
		}
		delete newRacer;
		return;
	}
	else
	{
		newRacer->setIdNum(&stringArr[i]);
		++i;
	}
	cout << "Enter the Circuit name of the race:\n";
	getline(cin, stringArr[i]);
	if(stringArr[i].length() > MAX_CIRCUIT)
	{
		cout << "CIRCUIT NAME TOO LONG, PRESS A TO TRY AGAIN.\n";
		while(i >= numElem)
		{
			stringArr[i].clear();
			--i;
		}
		delete newRacer;
		return;
	}
	else if(!isCircuit(stringArr[i]))
	{
		cout << "INVALID CIRCUIT NAME, PRESS A TO TRY AGAIN.\n";
		while(i >= numElem)
		{
			stringArr[i].clear();
			--i;
		}
		delete newRacer;
		return;
	}
	else
	{
		newRacer->setCircuitName(&stringArr[i]);
		++i;
	}
	cout << "Enter the date of the race:\n";
	getline(cin, stringArr[i]);
	if(stringArr[i].length() > MAX_DATE)
	{
		cout << "DATE TOO LONG, PRESS A TO TRY AGAIN.\n";
		while(i >= numElem)
		{
			stringArr[i].clear();
			--i;
		}
		delete newRacer;
		return;
	}
	else if(!isDate(stringArr[i]))
	{
		cout << "INVALID DATE, PRESS A TO TRY AGAIN.\n";
		while(i >= numElem)
		{
			stringArr[i].clear();
			--i;
		}
		delete newRacer;
		return;
	}
	else
	{
		newRacer->setDate(&stringArr[i]);
		++i;
	}
	cout << "Enter the racer's finish time.\n";
	getline(cin, stringArr[i]);
	if(stringArr[i].length() > MAX_FINISH)
	{
		cout << "TIME TOO LONG, PRESS A TO TRY AGAIN.\n";
		while(i >= numElem)
		{
			stringArr[i].clear();
			--i;
		}
		delete newRacer;
		return;
	}
	else if(!isTime(stringArr[i]))
	{
		cout << "INVALID TIME, PRESS A TO TRY AGAIN.\n";
		while(i >= numElem)
		{
			stringArr[i].clear();
			--i;
		}
		delete newRacer;
		return;
	}
	else
	{
		newRacer->setFinishTime(&stringArr[i]);
		++i;
	}
	numElem = i;
	dict->add(*(newRacer->getIdNum()), *newRacer);
	tree->insert(*newRacer);
}




void switchMenu(HashedDictionary<string, Racer>* dict, BinarySearchTree<Racer>* tree, string inputStr)
{
	switch(inputStr[0])
	{
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
		"A ADD A NEW RACER TO THE LIST\n"
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

