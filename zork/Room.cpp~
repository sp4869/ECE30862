#include "Room.h"



void Room::setName(string newName)
{
name = newName;
}

void Room::setDescription(string newDescription)
{
description = newDescription;
}

void Room::setStatus(string newStatus)
{
status = newStatus;
}

void Room::setType(string newType)
{
type = newType;
}

void Room::addBorder(string dir, string borderRoom)
{
  Border* newBorder = new Border();
 newBorder->direction = dir;
 newBorder->name = borderRoom;
 borders.push_back(newBorder);
}

void Room::addItem(Item* newItem)
{
items.push_back(newItem);
}



void Room::deleteItem(string passed)
{
  for(int i = 0; i < items.size(); i++)
    {
      if(items[i]->getName() == passed)
	{
	  items.erase(items.begin() + i);
	  return;
	}
    }
    //cout << "Error" << endl;
 
}

void Room::addContainer(Container* newContainer){
  (this->containers).push_back(newContainer);
}



void Room::addCreature(Creature* newCreature){
  (this->creatures).push_back(newCreature);
}



void Room::addTriggers(Triggers* newTriggers){
  (this->triggers).push_back(newTriggers);
}

void Room::deleteBorder(string input) {
   for (int i = 0; i < borders.size(); i++) {
     if (borders[i]->name == input) {
       borders.erase(borders.begin() + i);
     }
   }
  
  
}

Item * Room::take(string input) {
  vector<Item *>::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++ )
    {
	if ((*itr)->getName() == input)
	{
	  return (*itr);
	}
    }
  return NULL; 
}

string Room::getName()
{
  return name;
}

string Room::getDescription()
{
  return description;
}

string Room::getStatus()
{
  return status;
}
string Room::getType()
{
  return type;
}
vector<Item*> Room::getItems()
{
  return items;
}
string Room::getBorderName(string dir){
  string temp = "nonexistant";
  for(int i = 0; i < borders.size(); i++)
  {
    if(borders[i]->direction == dir)
      {
	temp = borders[i]->name;
      }
  } 
  return temp;
}
string Room::getCreature(string dir){
  string temp = "nonexistant";
  for(int i = 0; i < creatures.size(); i++)
  {
    if(creatures[i]->name == dir)
      {
	temp = creatures[i]->name;
      }
  } 
  return temp;
}


vector<Container*> Room::getContainers(){
  return containers; 

}
vector<Creature *> Room::getCreatures(){
  return creatures;
}

vector <Triggers*> Room::getTriggers()
{
  return triggers;
}