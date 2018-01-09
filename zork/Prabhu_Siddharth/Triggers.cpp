#include "Triggers.h"
#include <iostream>
#include <string>
using namespace std;
void Triggers::setType(string newType){
  this->type=newType;
}
void Triggers::setCondition(string object, string status, string has, string owner) {
  condition = new Conditions();
  
  condition->object = object;
  condition->status = status;
  condition->owner = owner;
  condition->has = has;
  
}
void Triggers::addAction(string newAction){
  (this->actions).push_back(newAction);
}
void Triggers::setPrint(string newPrint){
  this->print = newPrint;
}
void Triggers::setCommand(string newCommand){
  this->command = newCommand;
}

void Triggers::setStatus(string input)
{
  this -> condition->status = input;
  return; 
}


  

string Triggers::getPrint(){
  return print;
}
string Triggers::getCommand(){
  return command;
}
string Triggers::getType(){
  return type;
}

string Triggers::getHas(){
  return condition->has;
}

string Triggers::getObject(){
  return condition->object;
}

string Triggers::getStatus(){
  return condition->status;
}

string Triggers::getOwner(){
  return condition->owner;
}


Conditions* Triggers::getCondition() {
  return condition;
}
vector<string> Triggers::getActions() {
  return actions;
}
