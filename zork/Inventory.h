#ifndef _INVENTORY_H
#define _INVENTORY_H

#include <list>
using std::list;


#include "Item.h"
#include "Room.h"

class Inventory
{
 public:
  Inventory();
  void getItems() const;
  bool put(Item * item);
  bool hasa(string);
  void read(string);
  void drop(string,Room *);
  void removeItem(string);
  Item * getItem(string);

 private:
  list<Item *> items;
};

#endif