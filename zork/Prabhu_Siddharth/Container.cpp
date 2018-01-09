#include "Container.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Container::Container()
{
}
void Container::setName(string newName)
{
  name = newName;
}

void Container::setDescription(string newDescription)
{
  this->description = newDescription;
}
void Container::setStatus(string newStatus)
{
  status = newStatus;
}
void Container::setSatisfyCondition(string newCondition)
{
    this->condition = newCondition;
}
void Container::addItem(Item* newItem)
{
  items.push_back(newItem);
}
void Container::addTriggers(Triggers* newTrigger){
  (this->triggers).push_back(newTrigger);
}
void Container::setAccept(string newAccept){
  accept = newAccept;
}
void Container::addAction(string newAction)
{
  actions.push_back(newAction);
}
void Container::deleteItem(string passed)
{
  for(int i = 0; i < items.size() ; i++)
    {
      if(items[i]->getName() == passed)
	{
	  //cout << "deleted: " << passed << endl;
	  items.erase(items.begin() + i);
	}
    }
}


string Container::getName()
  {
    return name;
  }
string Container::getDescription() 
  {
    return description;
  }
string Container::getStatus()
  {
    return status;
  }
  string Container::getSatisfyCondition()
  {
    return condition;
  }
  string Container::getAccept(){
  return accept;
}
vector<Item*> Container::getItems()
{
  return items;
}
Item* Container::getItem(string target)
{
  int i = 0;
  for(i = 0; i < items.size(); i++ )
    {
      if(items[i]->getName() == target)
	{
	  return items[i];
	}
    }
}
vector<Triggers*> Container::getTriggers(){
  return triggers;
}
vector<string> Container::getActions()
{
  return actions;
}



