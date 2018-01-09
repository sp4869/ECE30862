//
//  Trigger.hpp
//  Zork
//
//  Created by Zhizhe on 12/4/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#ifndef Trigger_hpp
#define Trigger_hpp

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include "Condition.hpp"

using std::string;
using std::cout;
using std::endl;
using std::list;
using std::vector;

class Trigger {
private:
    string command;
    vector<Condition> conditions;
    vector<string> actions;
    vector<string> prints;
    
public:
    string type;
    Trigger(string type, string command, vector<Condition> conditions,
            vector<string> actions, vector<string> prints) {
        this->type = this->type.assign(type);
        this->command = this->command.assign(command);
        this->conditions = conditions;
        this->actions = actions;
        this->prints = prints;
    }
    //~Trigger();
    string get_type() {
        return type;
    }
    string get_command() {
        return command;
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

#endif /* Trigger_hpp */
