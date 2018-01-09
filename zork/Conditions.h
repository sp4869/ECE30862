#ifndef CONDITIONS_H_
#define CONDITIONS_H_
#include "Owner.h"
#include <string>


using namespace std;

class Conditions{ 
public:
	Conditions();
	void setOwner(string);
	void setStatus(string);
	void setHas(string);
	void setObject(string);
	
	string getOwner();
	string getStatus();

	
	
private:
	string status;
	string owner;
	string object;
	string has;
};
#endif
