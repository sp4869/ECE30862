#ifndef CREATURE_H_
#define CREATURE_H_
#include <string>
#include <vector>
#include <iostream>
#include "Item.h"
#include "Attack.h"
#include "Triggers.h"

using namespace std;


class Creature {
private:
	vector<string> vulnerability;
	vector<Triggers*> triggers;

	string condition;
	
  	string description;
  	string status;
  	Attack* attack;
  	string satisfy;
	vector<string> actions;


public:
	Creature();
	string name;
	void addAction(string);
	void setName(string newName);
  	void setDescription(string newDescription);	
  	void setStatus(string newStatus);
	void setVulnerability(string newVulnerability);
	void setAttack(Attack* newAttack);
	void addTriggers(Triggers*);
	void setConditionSatisfy(string);
	
	vector<string> getActions();
    string getName();
	string getDescription();
	string getStatus();
	bool getVulnerability(string);
	Attack* getAttack();
	vector<Triggers*> getTriggers();
	string getConditionSatisfy();
};

#endif
