//racer.h
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
	};
public:
	void insertName(string nameInput);
	void insertCircuit(string circuitInput);
	void insertId(string inputId);
	void inserDate(tm input);
	void insertLap(tm lapInput);
	void deleteLap(int lapNumber);
};