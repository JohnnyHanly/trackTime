// Here is the header file we can use with
// ADT BST and ADT Hashed Dictionary.
// Let us assume that in the input file,
// the data will be in this order
// name, idnumber, circuitname, date, finishtime (one line each)

#ifndef RACER
#define RACER

#include <string>

using namespace std;

class Racer
{
private:
  string* name;
  string* idNum;
  string* circuitName;
  string* date;
  string* finishTime;


public:
  Racer() { name = nullptr; idNum = nullptr; circuitName = nullptr;
    date = nullptr; finishTime = nullptr; }
  Racer(string *newName) { name = newName; idNum = nullptr; circuitName = nullptr;
    date = nullptr; finishTime = nullptr; }
  Racer(string *newName, string *newId) { name = newName; idNum = newId;
    circuitName = nullptr; date = nullptr; finishTime = nullptr; }

  string* getFinishTime() const{ return finishTime; }
  string* getName() const{ return name; }
  string* getIdNum() const { return idNum; }
  string* getCircuitName() const { return circuitName; }
  string* getDate() const { return date;}

  void setFinishTime(string *newTime) { finishTime = newTime; }
  void setName(string *nm) { name = nm; }
  void setIdNum(string *newId) { idNum = newId; }
  void setCircuitName(string *newCircuit) { circuitName = newCircuit; }
  void setDate(string *newDate) { date = newDate; }

  bool operator > (const Racer &right)
  {
    bool status = false;
    if(*name > *(right.getName()))
      status = true;
    return status;
  }
  bool operator < (const Racer &right)
  {
    bool status = false;
    if(*name < *(right.getName()))
      status = true;
    return status;
  }
  const Racer operator=(const Racer &right)
  {
    name = right.getName();
    idNum = right.getIdNum();
    circuitName = right.getCircuitName();
    date = right.getDate();
    finishTime = right.getFinishTime();
    return *this;
  }
};
#endif RACER
