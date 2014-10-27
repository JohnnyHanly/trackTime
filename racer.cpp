#include <time.h>
#include <stdio.h> 
#include  <string>


/*
toDo

verify date input data
*/ 

using namespace std;

// this is a rough draft for object data for the racer

class racer
{
private:
	string name; // full name "first last" 
	string driverId; // string numbers and letters "D123456789"
	string circuitName;
	struct tm date; // creates a structure for time using time.h
	struct lapTime
	{
		int counter; // to give the total number of laps. start with lap 1 -> lap n. 
		struct tm lap; // creates time struct for the indipendant laptime
		lapTime * previous;
		lapTime * next;
	}
public:
	void insertName(string nameInput);
	void insertCircuit(string circuitInput);
	void insertId(string inputId);
	void inserDate(tm input);
	void insertLap(tm lapInput);
	void deleteLap(int lapNumber);
}

void insertName(string nameInput)
	{
		this->name = nameInput; // sets the object name to the string name passed.
	}
void insertCircuit(string circuitInput)
{
	this->circuitName = circuitInput;
}
void insertId(string inputId)
{
	this->driverId = inputId;
}
void insertDate(tm input)
{
	this->date = input; // need to verify that this will work
}
void insertLap(tm lapInput)
{
	this->lap = lapInput; // wont work, needs to be able to parse in data, and add to linked list
	this->counter++;// dont forget to make counter larger.
}
void deleteLap(int lapNumber)
{
  // make function to delete the lapnumber given and shift the linked list around.
	this->counter--;	// dont forget to move counter down. 
}
