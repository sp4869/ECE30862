//
//  Creature.hpp
//  Zork
//
//  Created by Zhizhe on 11/28/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#ifndef Creature_hpp
#define Creature_hpp

#include <string>
#include <vector>
#include <iostream>
#include "Object.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;

class Creature:public Object {
private:
    string description;
    vector<string> vulnerability;
    vector<Condition> conditions;
    vector<string> actions;
    vector<string> prints;
    
public:
    Creature(string name, string status, string description,
             vector<string> vulnerability, vector<Condition> conditions,
             vector<string> actions, vector<string> prints,
             list<Trigger> triggers):Object(name, triggers, status) {
        this->status = this->status.assign(status);
        this->description = this->description.assign(description);
        this->vulnerability = vulnerability;
        this->conditions = conditions;
        this->actions = actions;
        this->prints = prints;
    }
    ~Creature();
    vector<string> get_vuls() {
        return vulnerability;
    }
    vector<Condition> get_conditions() {
        return conditions;
    }
    vector<string> get_actions() {
        return actions;
    }
    vector<string> get_prints() {
        return prints;
    }

};




#endif /* Creature_hpp */
