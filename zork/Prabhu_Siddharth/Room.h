#ifndef _ROOM_H
#define _ROOM_H
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Creature.h"
#include "Triggers.h"
#include "Container.h"
using std::vector;
using std::string;

using namespace std;

class Room {
typedef struct _border
{
  string direction;
  string name;
}Border;

public:
  Room()
  {
    name = "";
    description = "";
    status = "";
    type = "";
    bordersIndex = 0;
  };
  
  
  void setName(string newName);
  void setDescription(string newDescription);
  void setStatus(string newStatus);
  void setType(string newType);
  void addBorder(string newDirection, string newName);
  void addItem(Item* newItem);
  void addContainer(Container*);
  void addCreature(Creature*);
  void addTriggers(Triggers*);
  void deleteItem(string);
  void deleteBorder(string);
  Item * take(string);
  string getName();
  string getDescription();
  string getStatus();
  string getType();
  string getBorderName(string);
  string getCreature(string);
  vector <Border*> getBorders();
  vector<Item*> getItems();  
  vector<Container*> getContainers();
  vector<Creature*> getCreatures();
  vector <Triggers*> getTriggers(); 
  vector<Border*> borders;
  
  
private:
  vector<Item*> items;
  vector<Creature*> creatures;
  vector<Triggers*> triggers;
  vector<Container*> containers;
  
  string description;
  string name;
  string type;
  string status;
  int bordersIndex;
};
#endif


