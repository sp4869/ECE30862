//
//  Item.hpp
//  Zork
//
//  Created by Zhizhe on 11/26/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

#include <string>
#include <vector>
#include <iostream>
#include "Object.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;

class Item:public Object {
private:
    string description;
    string writing;
    vector<string> turn_on_prints;
    vector<string> turn_on_actions;
    //list<Trigger*> triggers;
    
public:
    Item(string name, string description, string writing,
         string status, vector<string> turn_on_prints, vector<string> turn_on_actions,
         list<Trigger> triggers):Object(name, triggers, status) {
        this->description = this->description.assign(description);
        this->writing = this->writing.assign(writing);
        this->status = this->status.assign(status);
        this->turn_on_prints = turn_on_prints;
        this->turn_on_actions = turn_on_actions;
    }
    ~Item();
    
    //turn on functions
    vector<string> get_actions() {
        return turn_on_actions;
    }
    vector<string> get_prints() {
        return turn_on_prints;
    }
    
    string get_writing() {
        return this->writing;
    }
};






#endif /* Item_hpp */
