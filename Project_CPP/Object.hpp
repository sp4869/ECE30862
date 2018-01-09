//
//  Object.hpp
//  Zork
//
//  Created by Zhizhe on 12/5/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include "Trigger.hpp"

using std::string;
using std::cout;
using std::endl;
using std::list;
using std::vector;

class Object {
private:
    string name;
    list<Trigger> triggers;
    
public:
    string status;
    Object(string name,list<Trigger> triggers,
           string status):name(name), triggers(triggers), status(status) {}
    //~Object();
    list<Trigger*> get_triggers();
    //check status;
    string get_name(){
        return this->name;
    }
};

#endif /* Object_hpp */
