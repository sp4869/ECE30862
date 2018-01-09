//
//  Object.cpp
//  Zork
//
//  Created by Zhizhe on 12/5/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#include "Object.hpp"

list<Trigger*> Object::get_triggers() {
    list<Trigger*> t;
    auto it = triggers.begin();
    while (it != triggers.end()) {
        if ((*it).get_type() == "executed") {
            it = triggers.erase(it);
        }
        else {
            t.push_back(&(*it));
            it++;
        }
    }
    return t;
}