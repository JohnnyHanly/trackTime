//racer.h
#include <time.h>
#include <stdio.h> 
#include  <string>


/*
toDo

verify date input data
get rid of racer.cpp, its redundant and isn't compatible with templates
can you delete the file? The function defs will go in the header file. -steven
*/ 

using namespace std;
struct raceProfile
{
	string name;
	string driverID; 
	string circuitName;
	struct tm date;
};
// this is a rough draft for object data for the racer

class racer
{
private:
	//singly linked list that serves as hash table.
	//each node has a pointer to a second linked list
	//with overflow pointing at the head. 
	struct node
	{
		node* next;
		node* overflow;
	};
	int hashCount, objCount, empty;
	node* head;
public:
	racer();
	~racer();
	void buildHashTable( int MAX_SIZE );
};

void racer::buildHashTable( int MAX_SIZE )
{
	node* newNode;
	node* cur = head;
	empty = MAX_SIZE;
	for(int i = 0;i < MAX_TABLE; i++)
	{
		newNode = new node;
		cur->next = newNode;
		cur = newNode;
		cur->taken = false;
		cur->next = NULL;
		
		//sentinel for overflow in each node
		cur->overflow = new node;
		cur->overflow->next = NULL;
		++count;
	}
}


//c_tor
racer::racer()
{
	//first entry is a sentinel node
	head = new node;
	head->next = NULL;
	head->prev = NULL;
	head->overflow = NULL;
	objCount = 0;
}

racer::~racer()
{
	//d_tor
}
