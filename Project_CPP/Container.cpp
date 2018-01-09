//
//  Container.cpp
//  Zork
//
//  Created by Zhizhe on 11/27/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#include "Container.hpp"


void Container::add_item(vector<Item*> item_vec, string item) {
    auto it = item_vec.begin();
    while (it != item_vec.end()) {
        if ((*it)->get_name() == item) {
            this->items.push_back((*it));
            break;
        }
        it++;
    }
    
}

bool Container::check_accept(string item) {
    if (accept.size() == 0) {
        return true;
    }
    auto it = accept.begin();
    while (it != accept.end()) {
        if ((*it) == item) {
            return true;
        }
        it++;
    }
    return false;
    
}

Item* Container::find_itemp(string name) {
    auto it = items.begin();
    while (it != items.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}