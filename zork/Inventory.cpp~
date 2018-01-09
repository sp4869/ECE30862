#include "Inventory.h"

Inventory::Inventory()
{}

void Inventory::getItems() const
{
  if (items.size() == 0)
  {
    cout << "Empty" << endl;
    return;
  }
  string temp;
  std::list<Item *>::const_iterator itr;
  for ( itr = items.begin(); itr != items.end(); ++itr )
    {
        temp = (*itr)->getName();
	cout << temp << ", ";
    }
	//code this shit
}

void Inventory::drop(string input_vector,Room * current_room)
{
  std::list<Item * >::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++ )
    {
	if ((*itr)->getName() == input_vector)
	{
	  cout << input_vector << " dropped" << endl;
	  current_room->addItem(*itr);
	  itr = items.erase(itr);
	  return;
	}
    }
  
  return;
}

void Inventory::read(string input)
{
  std::list<Item * >::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++ )
    {
	if ((*itr)->getName() == input)
	{
	  cout << (*itr)->getWriting() << endl;
	  return;
	}
    }
    cout << "Error" << endl;
    return; 
}


bool Inventory::put(Item * item)
{
      items.push_back(item);
      return true;
 
}

bool Inventory::hasa(string item) 
{
  std::list<Item * >::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++ )
    {
	if ((*itr)->getName() == item) {
	  return true;
	}
    }
    return false;
}

Item * Inventory::getItem(string name) {
  std::list<Item * >::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++ )
    {
	if ((*itr)->getName() == name) {
	  return (*itr);
	}
    }
    return NULL;
}

void Inventory::removeItem(string item_name) 
{
  std::list<Item * >::iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++ )
    {
	if ((*itr)->getName() == item_name)
	{
	  itr = items.erase(itr);
	  return;
	}
    } 
  
  return;
}
  

