#ifndef _ITEM_H
#define _ITEM_H
#include<iostream>
#include <vector>
#include <string>
#include "Triggers.h"

using std::vector;
using std::string;

using namespace std;

class Item
{
public:
	Item();

	void setName(string newName);
	void setDescription(string newDescription);
	void setStatus(string newStatus);
	void setWriting(string newWriting);
	void setIsOn(string);
	void addTriggers(Triggers*);
	void setPrint(string);
	void addAction(string);
	
	
	vector<string> getActions();
	string getName();
	string getDescription();
    string getStatus();	
	string getWriting();
	string getIsOn();
	vector<Triggers*> getTriggers();
	string getPrint();
	
private:
	string name;
	string description;
	string status;
	string writing;
	string print;
	string on;
	vector <string> actions;
	int onFlag;
	vector <Triggers*> triggers;
};
#endif
