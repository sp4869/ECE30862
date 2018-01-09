//
//  Condition.hpp
//  Zork
//
//  Created by Zhizhe on 12/5/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#ifndef Condition_hpp
#define Condition_hpp

#include <string>
#include <vector>
#include <iostream>
#include <list>

using std::string;
using std::cout;
using std::endl;
using std::list;
using std::vector;

class Condition {
private:
    string object;
    string status;
    string has;
    string owner;

public:
    Condition(string object, string status, string has, string owner) {
        this->object = this->object.assign(object);
        this->status = this->status.assign(status);
        this->has = this->has.assign(has);
        this->owner = this->owner.assign(owner);
    }
    //~Condition();
    string get_status(){
        return this->status;
    }
    string get_object(){
        return this->object;
    }
    string get_has(){
        return this->has;
    }
    string get_owner(){
        return this->owner;
    }
};

#endif /* Condition_hpp */
