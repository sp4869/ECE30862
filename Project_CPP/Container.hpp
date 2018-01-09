//
//  Container.hpp
//  Zork
//
//  Created by Zhizhe on 11/27/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#ifndef Container_hpp
#define Container_hpp

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include "Item.hpp"
#include "Object.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::list;

class Container:public Object {
private:
    string description;
    vector<string> accept;
    list<Item*> items;
    int state;
    
public:
    Container(string name, string description, string status,
              vector<string> accept, list<Trigger> triggers):Object(name, triggers, status), state(0) {
        this->description = this->description.assign(description);
        this->status = this->status.assign(status);
        this->accept = accept;
    }
    ~Container();
    
    void add_item(vector<Item*> item_vec, string item);
    bool check_accept(string item);
    Item* find_itemp(string name);
    list<Item*>* get_items_incontainer() {
        return &items;
    }
    void open() {
        state = 1;
    }
    int get_state() {
        return state;
    }
};



#endif /* Container_hpp */
