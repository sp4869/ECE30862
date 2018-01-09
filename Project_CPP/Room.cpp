//
//  Room.Cpp
//  Zork
//
//  Created by Zhizhe on 11/23/15.
//  Copyright © 2015 Zhizhe Zhang. All rights reserved.
//

#include "Room.hpp"

void Room::add_border(list<Room *> room_list, string direction, string roomname) {
    auto it = room_list.begin();
    Room* room = NULL;
    while (it != room_list.end()) {
        if ((*it)->get_name() == roomname) {
            room = (*it);
            break;
        }
        it++;
    }
    if (direction == "north") {
        borders[0] = room;
    }
    if (direction == "south") {
        borders[1] = room;
    }
    if (direction == "west") {
        borders[2] = room;
    }
    if (direction == "east") {
        borders[3] = room;
    }
}

void Room::add_item(vector<Item*> item_vec, string item) {
    auto it = item_vec.begin();
    while (it != item_vec.end()) {
        if ((*it)->get_name() == item) {
            this->items.push_back((*it));
            break;
        }
        it++;
    }
}

void Room::add_container(vector<Container*> container_vec, string container) {
    auto it = container_vec.begin();
    while (it != container_vec.end()) {
        if ((*it)->get_name() == container) {
            this->containers.push_back((*it));
            break;
        }
        it++;
    }
}

void Room::add_creature(vector<Creature*> creature_vec, string creature) {
    auto it = creature_vec.begin();
    while (it != creature_vec.end()) {
        if ((*it)->get_name() == creature) {
            this->creatures.push_back((*it));
            break;
        }
        it++;
    }
}

Item* Room::find_itemp(string name) {
    auto it = items.begin();
    while (it != items.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}

Container* Room::find_conp(string name) {
    auto it = containers.begin();
    while (it != containers.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}

Item* Room::find_itemp_incons(string name) {
    auto it = containers.begin();
    while (it != containers.end()) {
        list<Item*>* item_list = (*it)->get_items_incontainer();
        auto it1 = (*item_list).begin();
        while (it1 != (*item_list).end()) {
            if ((*it1)->get_name() == name) {
                return (*it1);
            }
            it1++;
        }
        it++;
    }
    return 0;
}

Creature* Room::find_creaturep(string name) {
    auto it = creatures.begin();
    while (it != creatures.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}

int Room::delete_item(string name) {
    auto it = items.begin();
    while (it != items.end()) {
        if ((*it)->get_name() == name) {
            items.erase(it);
            return 1;
        }
        it++;
    }
    return 0;
}

int Room::delete_con(string name) {
    auto it = containers.begin();
    while (it != containers.end()) {
        if ((*it)->get_name() == name) {
            containers.erase(it);
            return 1;
        }
        it++;
    }
    return 0;
}

int Room::delete_item_incons(string name) {
    auto it = containers.begin();
    while (it != containers.end()) {
        list<Item*>* item_list = (*it)->get_items_incontainer();
        auto it1 = (*item_list).begin();
        while (it1 != (*item_list).end()) {
            if ((*it1)->get_name() == name) {
                (*item_list).erase(it1);
                return 1;
            }
            it1++;
        }
        it++;
    }
    return 0;
}

int Room::delete_creature(string name) {
    auto it = creatures.begin();
    while (it != creatures.end()) {
        if ((*it)->get_name() == name) {
            creatures.erase(it);
            return 1;
        }
        it++;
    }
    return 0;
}

void Room::delete_border(Room* room) {
    if (borders[0] == room) {
        borders[0] = NULL;
    }
    else if (borders[1] == room) {
        borders[1] = NULL;
    }
    else if (borders[2] == room) {
        borders[2] = NULL;
    }
    else if (borders[3] == room) {
        borders[3] = NULL;
    }
}
