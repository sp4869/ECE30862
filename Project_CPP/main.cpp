#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <vector>
#include "Object.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "Container.hpp"
#include "Creature.hpp"
#include "Trigger.hpp"
#include "Condition.hpp"
#include "rapidxml.hpp"

#define FILE "sample.txt.xml"

using namespace rapidxml;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
//genaral functions
vector<string> split(const string &txt, char ch);
Item* inventory_find_item(list<Item*> inventory, string name);
Item* itemvec_find(vector<Item*> Item_vec, string name);
Container* containervec_find(vector<Container*> container_vec, string name);
Creature* creaturevec_find(vector<Creature*> creature_vec, string name);
Room* roomlist_find(const list<Room*>& room_list, string name);
list<Trigger*> extract_triggers(Room*& cur_room);
//construct the map
list<Room*> create_map(xml_document<>& doc, vector<Item*>& item_vec,
                       vector<Container*>& container_vec, vector<Creature*>& creature_vec);
Room* create_room(xml_node<> *attr_node);
Item* create_item(xml_node<> *attr_node);
Container* create_container(xml_node<> *attr_node);
Creature* create_creature(xml_node<> *attr_node);
Trigger create_trigger(xml_node<> *attr_node);
//user input check
void checkinput(string input, bool& run, Room*& cur_room, list<Room*>& room_list,
                const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                list<Item*>& inventory, const vector<Creature*>& creature_vec);
int tryset_pos(string input, Room* &cur_room);
int tryset_i(string input,list<Item*>& inventory, Room* &cur_room);
int tryopen(string input, bool& run, const vector<Container*>& container_vec, Room* &cur_room);
int tryread(string input, const list<Item*>& inventory);
int tryput(string input, list<Item*>& inventory, Room* &cur_room);
int tryturn_on(string input, bool& run, Room*& cur_room, list<Room*>& room_list,
               const vector<Item*>& item_vec, const vector<Container*>& container_vec,
               list<Item*>& inventory, const vector<Creature*>& creature_vec);
int tryattack(string input, bool& run, Room*& cur_room, list<Room*>& room_list,
              const vector<Item*>& item_vec, const vector<Container*>& container_vec,
              list<Item*>& inventory, const vector<Creature*>& creature_vec);
//behind scenes command check
int tryadd(string input, const list<Room*>& room_list,const vector<Item*>& item_vec,
           const vector<Container*>& container_vec, const vector<Creature*>& creature_vec);
int trydelete(string input, list<Room*>& room_list);
int tryupdate(string input, const list<Room*>& room_list,const vector<Item*>& item_vec,
              const vector<Container*>& container_vec, const vector<Creature*>& creature_vec);
int try_gameover(string input, bool& run);
//trigger functions
bool check_override_command(string input, bool& run, Room*& cur_room, list<Room*>& room_list,
                            const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                            list<Item*>& inventory, const vector<Creature*>& creature_vec);
bool check_condition(vector<Condition> conditions, const list<Room*>& room_list,
                     const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                     list<Item*>& inventory, const vector<Creature*>& creature_vec);
void execute_actions(vector<string> actions, bool& run, Room*& cur_room, list<Room*>& room_list,
                     const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                     list<Item*>& inventory, const vector<Creature*>& creature_vec);
void execute_prints(vector<string> prints);
bool check_trigger_activation(bool& run, Room*& cur_room,  list<Room*>& room_list,
                              const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                              list<Item*>& inventory, const vector<Creature*>& creature_vec);
list<Trigger*> extract_alltriggers(list<Room*>& room_list, const vector<Item*>& item_vec,
                                   const vector<Container*>& container_vec,
                                   const vector<Creature*>& creature_vec);

int main () {
	
    string input; //input command by user from console
    bool run = 1; //if the game is running
    bool overide = 0;
    list<Room*> room_list;
    vector<Item*> item_vec;
    vector<Container*> container_vec;
    vector<Creature*> creature_vec;
    list<Item*> inventory;
    
    
    xml_document<> doc;    // character type defaults to char
    std::ifstream t(FILE);
    std::stringstream buf;
    buf << t.rdbuf();
    string s = buf.str();
    doc.parse<0>(&s.at(0));
    
    room_list = create_map(doc, item_vec, container_vec, creature_vec);
    Room* cur_room = room_list.front();
    //cout << cur_room->get_name() << endl;
    cout << cur_room->get_description() << endl;
    
    while (run) {
        
        std::getline(cin, input);
        overide = check_override_command(input, run, cur_room, room_list,
                                    item_vec, container_vec, inventory, creature_vec);
       
        if (!overide) {
            checkinput(input, run, cur_room, room_list,
                       item_vec, container_vec, inventory, creature_vec);
        }
        
        bool activated = true;
        while (activated) {
            activated = check_trigger_activation(run, cur_room, room_list, item_vec,
                                                 container_vec,inventory, creature_vec);
        }
    }
	return 0;
	
}

list<Room*> create_map(xml_document<> &doc, vector<Item*>& item_vec,
                       vector<Container*>& container_vec,vector<Creature*>& creature_vec) {
    xml_node<> *node = doc.first_node()->first_node();//level :room
    xml_node<> *f_node = node; //start of node for level :room
    list<Room*> room_list;
    
    //level 1:construct object
    while (node) { //create all objects
        if ((string)node->name() == "room") {
            room_list.push_back(create_room(node->first_node()));
        }
        else if ((string)node->name() == "item") {
            item_vec.push_back(create_item(node->first_node()));
        }
        else if ((string)node->name() == "container") {
            container_vec.push_back(create_container(node->first_node()));
        }
        else if ((string)node->name() == "creature") {
            creature_vec.push_back(create_creature(node->first_node()));
        }
        
        node = node->next_sibling();
    }
    
    //level 2:construct relations
    node = f_node;
    xml_node<> *attr_node = NULL;
    xml_node<> *b_node; // border node
    string direction;
    string room_name;
    auto it_room = room_list.begin();
    auto it_container = container_vec.begin();
    
    while (node) {
        attr_node = node->first_node();
        
        //1.add sub stuff to the room(item, border, container, creature)
        if ((string)node->name() == "room") {
            while (attr_node) {
                if ((string)attr_node->name() == "item") {//add item to the room
                    (*it_room)->add_item(item_vec, attr_node->value());
                }
                else if ((string)attr_node->name() == "container") {//add container to the room
                    (*it_room)->add_container(container_vec, attr_node->value());
                }
                else if ((string)attr_node->name() == "border") {//add border to the room
                    b_node = attr_node->first_node();
                    while (b_node) {
                        if ((string)b_node->name() == "direction") {
                            direction.assign(b_node->value());
                        }
                        else if ((string)b_node->name() == "name") {
                            room_name.assign(b_node->value());
                        }
                        b_node = b_node->next_sibling();
                    }
                    (*it_room)->add_border(room_list, direction, room_name);
                }
                else if ((string)attr_node->name() == "creature") {//add creature to the room
                    (*it_room)->add_creature(creature_vec, attr_node->value());
                }
                
                attr_node = attr_node->next_sibling();
            }
            
            it_room++;
        }
        
        //2.add sub stuff to the container(item)
        else if ((string)node->name() == "container") {
            while (attr_node) {
                if ((string)attr_node->name() == "item") {//add item to the room
                    (*it_container)->add_item(item_vec, attr_node->value());
                }
                attr_node = attr_node->next_sibling();
            }
            
            it_container++;
        }
        
        node = node->next_sibling();
    }
    
    return room_list;
}

Room* create_room(xml_node<> *attr_node) {
    string name;
    string description;
    string type;
    list<Trigger> triggers;
    string status;
    
    while (attr_node) {
        if ((string)attr_node->name() == "name") {
            name = name.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "description") {
            description = description.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "type") {
            type = type.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "trigger") {
            triggers.push_back(create_trigger(attr_node));
        }
        else if ((string)attr_node->name() == "status") {
            status = status.assign(attr_node->value());
        }
        /*
        else {
            cout << attr_node->name() << endl;
        }*/
        
        attr_node = attr_node->next_sibling();
    }
    
    return new Room(name, description, type, triggers, status);
    
}

Item* create_item(xml_node<> *attr_node) {
    string name;
    string status;
    string description;
    string writing;
    vector<string> turn_on_prints;
    vector<string> turn_on_actions;
    list<Trigger> triggers;
    xml_node<> *turnon_node;
    
    while (attr_node) {
        if ((string)attr_node->name() == "name") {
            name = name.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "writing") {
            writing = writing.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "status") {
            status = status.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "description") {
            description = description.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "trigger") {
            triggers.push_back(create_trigger(attr_node));
        }
        else if ((string)attr_node->name() == "turnon") {
            turnon_node = attr_node->first_node();
            while (turnon_node) {
                if ((string)turnon_node->name() == "print") {
                    turn_on_prints.push_back(turnon_node->value());
                }
                else if ((string)turnon_node->name() == "action") {
                    turn_on_actions.push_back(turnon_node->value());
                }
                turnon_node = turnon_node->next_sibling();
            }
        }
        attr_node = attr_node->next_sibling();
    }
    
    return new Item(name, description, writing, status, turn_on_prints, turn_on_actions, triggers);
}

Container* create_container(xml_node<> *attr_node) {
    string name;
    string status;
    string description;
    vector<string> accept;
    list<Trigger> triggers;
    
    while (attr_node) {
        if ((string)attr_node->name() == "name") {
            name = name.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "status") {
            status = status.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "description") {
            description = description.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "accept") {
            accept.push_back(attr_node->value());
        }
        else if ((string)attr_node->name() == "trigger") {
            triggers.push_back(create_trigger(attr_node));
        }
        attr_node = attr_node->next_sibling();
    }
    
    return new Container(name, description, status, accept, triggers);
}

Creature* create_creature(xml_node<> *attr_node) {
    string name;
    string status;
    string description;
    vector<string> vulnerability;
    list<Trigger> triggers;
    vector<Condition> conditions;
    vector<string> actions;
    vector<string> prints;
    
    while (attr_node) {
        if ((string)attr_node->name() == "name") {
            name = name.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "status") {
            status = status.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "description") {
            description = description.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "vulnerability") {
            vulnerability.push_back(attr_node->value());
        }
        else if ((string)attr_node->name() == "attack") {
            xml_node<> *attack_node = attr_node->first_node();
            while (attack_node) {
                if ((string)attack_node->name() == "condition") {
                    xml_node<> *condition_node = attack_node->first_node();
                    string object;
                    string status;
                    string has;
                    string owner;
                    while (condition_node) {
                        if ((string)condition_node->name() == "object") {
                            object = condition_node->value();
                        }
                        else if ((string)condition_node->name() == "status") {
                            status = condition_node->value();
                        }
                        else if ((string)condition_node->name() == "has") {
                            has = condition_node->value();
                        }
                        else if ((string)condition_node->name() == "owner") {
                            owner = condition_node->value();
                        }
                        condition_node = condition_node->next_sibling();
                    }
                    conditions.push_back(Condition(object, status, has, owner));
                }
                else if ((string)attack_node->name() == "action") {
                    actions.push_back(attack_node->value());
                }
                else if ((string)attack_node->name() == "print") {
                    prints.push_back(attack_node->value());
                }
                attack_node = attack_node->next_sibling();
            }
        }
        else if ((string)attr_node->name() == "trigger") {
            triggers.push_back(create_trigger(attr_node));
        }
        attr_node = attr_node->next_sibling();
    }
    
    return new Creature(name, status, description, vulnerability,
                        conditions, actions, prints, triggers);
    
}

Trigger create_trigger(xml_node<> *attr_node) {
    string type;
    string command;
    vector<Condition> conditions;
    vector<string> actions;
    vector<string> prints;
    attr_node = attr_node->first_node();
    while (attr_node) {
        if ((string)attr_node->name() == "type") {
            type = type.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "command") {
            command = command.assign(attr_node->value());
        }
        else if ((string)attr_node->name() == "condition") {
            xml_node<> *condition_node = attr_node->first_node();
            string object;
            string status;
            string has;
            string owner;
            while (condition_node) {
                if ((string)condition_node->name() == "object") {
                    object = condition_node->value();
                }
                else if ((string)condition_node->name() == "status") {
                    status = condition_node->value();
                }
                else if ((string)condition_node->name() == "has") {
                    has = condition_node->value();
                }
                else if ((string)condition_node->name() == "owner") {
                    owner = condition_node->value();
                }
                condition_node = condition_node->next_sibling();
            }
            conditions.push_back(Condition(object, status, has, owner));
        }
        else if ((string)attr_node->name() == "action") {
            actions.push_back(attr_node->value());
        }
        else if ((string)attr_node->name() == "print") {
            prints.push_back(attr_node->value());
        }
        attr_node = attr_node->next_sibling();
    }
    
    return Trigger(type, command, conditions, actions, prints);
    
}

void checkinput(string input, bool& run, Room*& cur_room, list<Room*>& room_list,
                const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                list<Item*>& inventory, const vector<Creature*>& creature_vec) {
    int captured = 0;
    captured = tryset_pos(input, cur_room);
    if (!captured) {
        captured = tryset_i(input,inventory,cur_room);
    }
    if (!captured) {
        captured = tryopen(input, run, container_vec, cur_room);
    }
    if (!captured) {
        captured = tryread(input, inventory);
    }
    if (!captured) {
        captured = tryput(input, inventory, cur_room);
    }
    if (!captured) {
        captured = tryturn_on(input, run, cur_room, room_list, item_vec,
                              container_vec, inventory, creature_vec);
    }
    if (!captured) {
        captured = tryattack(input, run, cur_room, room_list, item_vec,
                              container_vec, inventory, creature_vec);
    }
    //...........can not be utilized by user, just test..........
    /*if (!captured) {
        captured = tryadd(input, room_list, item_vec, container_vec, creature_vec);
    }
    if (!captured) {
        captured = trydelete(input, room_list);
    }
    if (!captured) {
        captured = tryupdate(input,room_list, item_vec, container_vec, creature_vec);
    }
    if (!captured) {
        captured = try_gameover(input, run);
    }*/
    if(!captured && input.length() != 0) {
        cout << "Error" << endl;
    }
}

bool check_override_command(string input, bool& run, Room*& cur_room,  list<Room*>& room_list,
                            const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                            list<Item*>& inventory, const vector<Creature*>& creature_vec) {
    if(!input.size()) return 0;
    list<Trigger*> triggers_seen = extract_triggers(cur_room);
    int catched = 0;
    //get trigger with command same as input
    auto it = triggers_seen.begin();
    while (it != triggers_seen.end()) {
        if (input == (*it)->get_command()) {
            //check condition(status, owner),do actions, do print
            int match = check_condition((*it)->get_conditions(), room_list,item_vec, container_vec, inventory, creature_vec);
            if (!match) {
                it++;
                continue;
            }
            execute_prints((*it)->get_prints());
            execute_actions((*it)->get_actions(), run, cur_room, room_list,
                            item_vec, container_vec, inventory, creature_vec);
            if ((*it)->get_type() != "permanent") {
                (*it)->type = "executed";
            }
            catched = 1;
        }
        it++;
    }
    
    return catched;
}

bool check_trigger_activation(bool& run, Room*& cur_room,  list<Room*>& room_list,
                              const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                              list<Item*>& inventory, const vector<Creature*>& creature_vec) {
    list<Trigger*> triggers_seen = extract_alltriggers(room_list, item_vec, container_vec, creature_vec);
    auto it = triggers_seen.begin();
    int catched = 0;
    //get trigger with no command
    while (it != triggers_seen.end()) {
        if (!(*it)->get_command().size()) {
            //check condition(status, owner),do actions, do print
            int match = check_condition((*it)->get_conditions(), room_list,item_vec, container_vec, inventory, creature_vec);//condition matched
            if (!match) {
                it++;
                continue;
            }
            execute_prints((*it)->get_prints());
            execute_actions((*it)->get_actions(), run, cur_room, room_list,
                            item_vec, container_vec, inventory, creature_vec);
            if ((*it)->get_type() != "permanent") {
                (*it)->type = "executed";
            }
            catched = 1;
        }
        it++;
    }
    
    return catched;
}

bool check_condition(vector<Condition> condition_vec, const list<Room*>& room_list,
                     const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                     list<Item*>& inventory, const vector<Creature*>& creature_vec) {
    auto it = condition_vec.begin();
    while (it != (condition_vec).end()) {
        string object = (*it).get_object();
        string status = (*it).get_status();
        string has = (*it).get_has();
        string owner = (*it).get_owner();
        //check owner
        if (has.size()) {
            if (owner == "inventory") {
                if (inventory_find_item(inventory, object)) {
                    if (has == "yes") {it++;continue;}
                    else {
                        return 0;
                    }
                }
                else {
                    if (has == "yes") {
                        return 0;
                    }
                    else {it++;continue;}
                }
            }
            Room* room = roomlist_find(room_list, owner);
            if (room) {
                if (room->find_itemp(object)) {
                    if (has == "yes") {it++;continue;}
                    else {
                        return 0;
                    }
                }
                else if (room->find_conp(object)) {
                    if (has == "yes") {it++;continue;}
                    else {
                        return 0;
                    }
                }
                else if (room->find_creaturep(object)) {
                    if (has == "yes") {it++;continue;}
                    else {
                        return 0;
                    }
                }
                else {
                    if (has == "yes") {
                        return 0;
                    }
                    else {it++;continue;}
                }
            }
            Container* container = containervec_find(container_vec, owner);
            if (container) {
                if (container->find_itemp(object)) {
                    if (has == "yes") {it++;continue;}
                    else {
                        return 0;
                    }
                }
                else {
                    if (has == "yes") {
                        return 0;
                    }
                    else {it++;continue;}
                }
            }
        }
        //check status
        else {
            Room* room = roomlist_find(room_list, object);
            if (room) {
                if (room->status == status) {it++;continue;}
                else {return 0;}
            }
            Item* item = itemvec_find(item_vec, object);
            if (item) {
                if (item->status == status) {it++;continue;}
                else {return 0;}
            }
            Container* container = containervec_find(container_vec, object);
            if (container) {
                if (container->status == status) {it++;continue;}
                else {return 0;}
            }
            Creature* creature = creaturevec_find(creature_vec, object);
            if (creature) {
                if (creature->status == status) {it++;continue;}
                else {return 0;}
            }
            cout << "cao" << endl;
        }
        it++;
    }
    
    return 1;
}

void execute_actions(vector<string> actions, bool& run, Room*& cur_room, list<Room*>& room_list,
                     const vector<Item*>& item_vec, const vector<Container*>& container_vec,
                     list<Item*>& inventory, const vector<Creature*>& creature_vec) {
    string input;
    auto it = actions.begin();
    while (it != actions.end()) {
        input = (*it);
        int captured = 0;
        captured = tryadd(input, room_list, item_vec, container_vec, creature_vec);
        if (!captured) {
            captured = trydelete(input, room_list);
        }
        if (!captured) {
            captured = tryupdate(input,room_list, item_vec, container_vec, creature_vec);
        }
        if (!captured) {
            captured = try_gameover(input, run);
        }
        if (!captured) {
            checkinput(input, run, cur_room, room_list,
                       item_vec, container_vec, inventory, creature_vec);
        }
        it++;
    }
}

void execute_prints(vector<string> prints) {
    if (prints.size() == 0) return;
    auto it = prints.begin();
    while (it != prints.end()) {
        cout << (*it);
        it++;
    }
    cout << endl;
}

list<Trigger*> extract_triggers(Room*& cur_room) {
    list<Trigger*> triggers_seen;
    triggers_seen.merge((*cur_room).get_triggers());
    list<Item*>* items_inroom = (*cur_room).get_items_inroom();
    
    auto it = (*items_inroom).begin();
    while (it != (*items_inroom).end()) {
        triggers_seen.merge((*it)->get_triggers());
        it++;
    }
    
    list<Container*>* containers_inroom = (*cur_room).get_containers_inroom();
    auto it1 = (*containers_inroom).begin();
    while (it1 != (*containers_inroom).end()) {
        triggers_seen.merge((*it1)->get_triggers());
        it1++;
    }
    
    it1 = (*containers_inroom).begin();
    while (it1 != (*containers_inroom).end()) {
        list<Item*>* item_list = (*it1)->get_items_incontainer();
        auto it2 = (*item_list).begin();
        while (it2 != (*item_list).end()) {
            triggers_seen.merge((*it2)->get_triggers());
            it2++;
        }
        it1++;
    }
    
    list<Creature*>* creatures_inroom = (*cur_room).get_creatures_inroom();
    auto it3 = (*creatures_inroom).begin();
    while (it3 != (*creatures_inroom).end()) {
        triggers_seen.merge((*it3)->get_triggers());
        it3++;
    }
    
    return triggers_seen;
}

list<Trigger*> extract_alltriggers(list<Room*>& room_list, const vector<Item*>& item_vec,
                                   const vector<Container*>& container_vec,
                                   const vector<Creature*>& creature_vec) {
    list<Trigger*> triggers;
    auto it = room_list.begin();
    while (it != room_list.end()) {
        triggers.merge((*it)->get_triggers());
        it++;
    }
    auto it1 = item_vec.begin();
    while (it1 != item_vec.end()) {
        triggers.merge((*it1)->get_triggers());
        it1++;
    }
    auto it2 = container_vec.begin();
    while (it2 != container_vec.end()) {
        triggers.merge((*it2)->get_triggers());
        it2++;
    }
    auto it3 = creature_vec.begin();
    while (it3 != creature_vec.end()) {
        triggers.merge((*it3)->get_triggers());
        it3++;
    }
    
    return triggers;
}

int tryset_pos(string input, Room* &cur_room) {
    int captured = 1;
    Room* room = NULL;
 
    if(input == "n" || input == "north") {
        room = cur_room->get_border(0);
        if (room == NULL) {
            cout << "can't go that way." << endl;
        }
    }
    else if(input == "s" || input == "south") {
        room = cur_room->get_border(1);
        if (room == NULL) {
            cout << "can't go that way." << endl;
        }
    }
    else if(input == "w" || input == "west") {
        room = cur_room->get_border(2);
        if (room == NULL) {
            cout << "can't go that way." << endl;
        }
    }
    else if(input == "e" || input == "east") {
        room = cur_room->get_border(3);
        if (room == NULL) {
            cout << "can't go that way." << endl;
        }
    }
    else {
        captured = 0;
    }
    if (room != NULL) {
        cur_room = room;
        //cout << cur_room->get_name() << endl;
        cout << cur_room->get_description() << endl;
    }
    
    return captured;
 }

int tryset_i(string input,list<Item*>& inventory, Room* &cur_room) {
    if (input == "i" || input == "inventory") {
        cout << "Inventory: ";
        if (inventory.size() == 0) {
            cout << "empty" << endl;
            return 1;
        }
        auto it = inventory.begin();
        cout << (*it)->get_name();
        while (it != inventory.end()) {
            it++;
            if (it != inventory.end()) {
                cout << ", " <<(*it)->get_name();
            }
        }
        cout << endl;
        return 1;
    }
    
    vector<string> strs = split(input, ' ');
    list<Item*>* items_inroom = cur_room->get_items_inroom();
    list<Container*>* containers_inroom = cur_room->get_containers_inroom();
    if (strs.size() != 2) {
        return 0;
    }
    if (strs[0] == "take") {
        auto it = (*items_inroom).begin();
        while (it != (*items_inroom).end()) {
            if ((*it)->get_name() == strs[1]) {
                inventory.push_back(*(it));
                it = (*items_inroom).erase(it);
                //......also remove the item in the container
                auto it1 = (*containers_inroom).begin(); //another iterator for container in room
                while (it1 != (*containers_inroom).end()) {
                    list<Item*>* items_con = (*it1)->get_items_incontainer();
                    auto it_con = (*items_con).begin();
                    while (it_con != (*items_con).end()) {
                        if ((*it_con)->get_name() == strs[1]) {
                            (*items_con).erase(it_con);
                            it1 = (*containers_inroom).end();
                            break;
                        }
                        it_con++;
                    }
                    it1++;
                }
                //......
                cout << "Item " << strs[1] << " added to inventory." << endl;
                return 1;
            }
            it++;
        }
        if (it == (*items_inroom).end()) {
            cout << "No " << strs[1] << " can be taken." << endl;
        }
        return 1;
    }
    else if (strs[0] == "drop") {
        auto it = inventory.begin();
        while (it != inventory.end()) {
            if ((*it)->get_name() == strs[1]) {
                (*items_inroom).push_back(*(it));
                it = inventory.erase(it);
                cout << strs[1] << " dropped." << endl;
                return 1;
            }
            it++;
        }
        if (it == inventory.end()) {
            cout << "No " << strs[1] << " can be dropped." << endl;
        }
        return 1;
    }
    else {
        return 0;
    }
}

int tryread(string input, const list<Item*>& inventory) {
    vector<string> strs = split(input, ' ');
    if (strs.size() != 2) {
        return 0;
    }
    if (strs[0] == "read") {
        auto it = inventory.begin();
        while (it != inventory.end()) {
            if ((*it)->get_name() == strs[1]) {
                if ((*it)->get_writing().length() != 0) {
                    cout << (*it)->get_writing() << endl;
                }
                else {
                    cout << "Nothing written." << endl;
                }
                return 1;
            }
            it++;
        }
        if (it == inventory.end()) {
            cout << "No " << strs[1] << " can be read." << endl;
        }
        return 1;
        
    }else {
        return 0;
    }
}

int tryput(string input, list<Item*>& inventory, Room* &cur_room) {
    vector<string> strs = split(input, ' ');
    if (strs[0] != "put" || strs.size() != 4) {
        return 0;
    }
    if (strs[3] == "i" || strs[3] == "inventory") {
        if ((*cur_room).find_itemp(strs[1])) {
            inventory.push_back((*cur_room).find_itemp(strs[1]));
            cout << "Item " << strs[1] << " added to inventory." << endl;
            return 1;
        }
        else {
            cout << "Can not put " << strs[1] << " in inventory." << endl;
            return 1;
        }
    }
    Item* item = inventory_find_item(inventory, strs[1]);
    if (item) {
        Container* container = (*cur_room).find_conp(strs[3]);
        if (container) {
            if (!(*container).check_accept(strs[1])) {
                cout << "Item " << strs[1] << " can not be added to " << strs[3] << "." << endl;
                return 1;
            }
            list<Item*>* item_l = (*container).get_items_incontainer();
            (*item_l).push_back(item);
            if (container->get_state()) {
                ((*cur_room).get_items_inroom())->push_back(item);
            }
            inventory.remove(item);
            cout << "Item " << strs[1] << " added to " << strs[3] << "." << endl;
            return 1;
        }
        else {
            cout << "No " << strs[3] << " in this room." << endl;
            return 1;
        }
    }
    else {
        cout << "No " << strs[1] << " in inventory." << endl;
        return 1;
    }
    
    
    return 0;
}


int tryopen(string input, bool& run, const vector<Container*>& container_vec, Room* &cur_room) {
    if (input == "open exit") {
        if (cur_room->get_type() == "exit") {
            cout << "Game Over" << endl;
            run = 0;
        }
        else {
            cout << "Can not open exit." << endl;
        }
        return 1;
    }
    
    vector<string> strs = split(input, ' ');
    if (strs.size() != 2) {
        return 0;
    }
    list<Container*>* containers_inroom = cur_room->get_containers_inroom();
    list<Item*>* items_inroom = cur_room->get_items_inroom();
    if (strs[0] == "open") {
        auto it = (*containers_inroom).begin();
        while (it != (*containers_inroom).end()) {
            if ((*it)->get_name() == strs[1]) {
                (*it)->open();
                if ((*it)->get_items_incontainer()->size() == 0) {
                    cout << (*it)->get_name() << " is empty." << endl;
                    return 1;
                }
                //open container
                cout << strs[1] << " contains ";
                list<Item*>* items_con = (*it)->get_items_incontainer();
                auto it_con = (*items_con).begin();
                int found = 0;
                auto it_room = (*items_inroom).begin();
                while (it_room != (*items_inroom).end()) {
                    if ((*it_room)->get_name() == (*it_con)->get_name()) {
                        found = 1;
                    }
                    it_room++;
                }
                if (!found) {
                    (*items_inroom).push_back(*(it_con));
                }
                cout << (*it_con)->get_name();
                //(*items_con).erase(it_con);
                while (it_con != (*items_con).end()) {
                    it_con++;
                    if (it_con != (*items_con).end()) {
                        int found = 0;
                        auto it_room = (*items_inroom).begin();
                        while (it_room != (*items_inroom).end()) {
                            if ((*it_room)->get_name() == (*it_con)->get_name()) {
                                found = 1;
                            }
                            it_room++;
                        }
                        if (!found) {
                            (*items_inroom).push_back(*(it_con));
                        }
                        cout << ", " << (*it_con)->get_name();
                        //(*items_con).erase(it_con);
                    }
                }
                cout << "." << endl;
                return 1;
            }
            it++;
        }
        if (it == (*containers_inroom).end()) {
            cout << "No " << strs[1] << " can be open." << endl;
        }
        return 1;
    }
    
    
    return 0;
}

int tryturn_on(string input, bool& run, Room*& cur_room, list<Room*>& room_list,
              const vector<Item*>& item_vec, const vector<Container*>& container_vec,
              list<Item*>& inventory, const vector<Creature*>& creature_vec) {
    vector<string> strs = split(input, ' ');
    if (strs[0] != "turn" || strs[1] != "on" || strs.size() != 3) {
        return 0;
    }
    Item* item = inventory_find_item(inventory, strs[2]);
    if (item) {
        if (item->get_actions().size() || item->get_prints().size()) {
            cout << "You activate the " << strs[2] << "." << endl;
            execute_prints(item->get_prints());
            execute_actions(item->get_actions(), run, cur_room, room_list,
                            item_vec, container_vec, inventory, creature_vec);
        }
        else {
            cout << strs[2] << " has no turn on effect." << endl;
        }
    }
    else {
        cout << "Item " << strs[2] << " not in inventory." << endl;

    }
    
    
    return 1;
}

int tryattack(string input, bool& run, Room*& cur_room, list<Room*>& room_list,
               const vector<Item*>& item_vec, const vector<Container*>& container_vec,
               list<Item*>& inventory, const vector<Creature*>& creature_vec) {
    vector<string> strs = split(input, ' ');
    if (strs[0] != "attack" || strs.size() != 4) {
        return 0;
    }
    Creature* creature = cur_room->find_creaturep(strs[1]);
    Item* item = inventory_find_item(inventory, strs[3]);
    if (creature) {
        vector<string> vuls = creature->get_vuls();
        if (item) {
            int found_vul = 0;
            auto it = vuls.begin();
            while (it != vuls.end()) {
                if ((*it) == item->get_name()) {
                    found_vul = 1;
                    break;
                }
                it++;
            }
            if (found_vul) {
                cout << "You assault the " << strs[1] << " with the " << strs[3] << "." << endl;
                int match = check_condition(creature->get_conditions(), room_list, item_vec,
                                            container_vec, inventory, creature_vec);//condition matched
                if (match) {
                    execute_prints(creature->get_prints());
                    execute_actions(creature->get_actions(), run, cur_room, room_list,
                                    item_vec, container_vec, inventory, creature_vec);
                }
                else {
                    cout << "But looks like no evident effect." << endl;
                }
            }
            else {
                cout << strs[1] << " is not afraid of " << strs[3] << "." << endl;
            }
        }
        else {
            cout << "No item " << strs[3] << " in inventory." << endl;
        }
    }
    else {
        cout << "No creature " << strs[1] << " in this room." << endl;
    }
    
    return 1;
}

int tryadd(string input, const list<Room*>& room_list,const vector<Item*>& item_vec,
           const vector<Container*>& container_vec, const vector<Creature*>& creature_vec) {
    vector<string> strs = split(input, ' ');
    if (((strs[0] != "Add") && (strs[0] != "add")) ||strs.size() != 4) {
        return 0;
    }
    Item* item = itemvec_find(item_vec, strs[1]);
    if (item) {
        Container* container = containervec_find(container_vec, strs[3]);
        if (container) {
            list<Item*>* item_l = (*container).get_items_incontainer();
            (*item_l).push_back(item);
            //cout << "Item " << strs[1] << " added to " << strs[3] << "." << endl;
            return 1;
        }
        else {
            Room* room = roomlist_find(room_list, strs[3]);
            if (room) {
                list<Item*>* item_l = (*room).get_items_inroom();
                (*item_l).push_back(item);
                //cout << "Item " << strs[1] << " added to " << strs[3] << "." << endl;
                return 1;
            }
        }
    }
    else {
        Creature* creature = creaturevec_find(creature_vec, strs[1]);
        if (creature) {
            Room* room = roomlist_find(room_list, strs[3]);
            if (room) {
                list<Creature*>* creature_l = (*room).get_creatures_inroom();
                (*creature_l).push_back(creature);
                //cout << "Creature " << strs[1] << " appeared in " << strs[3] << "." << endl;
                return 1;
            }
        }
        //add container to room
        else {
            Container* container = containervec_find(container_vec, strs[1]);
            if (container) {
                Room* room = roomlist_find(room_list, strs[3]);
                if (room) {
                    list<Container*>* container_l = (*room).get_containers_inroom();
                    (*container_l).push_back(container);
                    //cout << "Container " << strs[1] << " added to " << strs[3] << "." << endl;
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

int trydelete(string input, list<Room*>& room_list) {
    vector<string> strs = split(input, ' ');
    if (((strs[0] != "Delete") && (strs[0] != "delete")) ||strs.size() != 2) {
        return 0;
    }
    Room* room = roomlist_find(room_list, strs[1]);
    if (room) {
        auto it = room_list.begin();
        while (it != room_list.end()) {
            (*it)->delete_border(room);
            it++;
        }
        return 1;
    }
    auto it = room_list.begin();
    while (it != room_list.end()) {
        int deleted = 0;
        deleted = (*it)->delete_item(strs[1]);
        if (deleted) {
            return 1;
        }
        deleted = (*it)->delete_con(strs[1]);
        if (deleted) {
            return 1;
        }
        deleted = (*it)->delete_item_incons(strs[1]);
        if (deleted) {
            return 1;
        }
        deleted = (*it)->delete_creature(strs[1]);
        if (deleted) {
            return 1;
        }
        it++;
    }
    
    return 0;
}

int tryupdate(string input, const list<Room*>& room_list,const vector<Item*>& item_vec,
              const vector<Container*>& container_vec, const vector<Creature*>& creature_vec) {
    vector<string> strs = split(input, ' ');
    if (((strs[0] != "Update") && (strs[0] != "update")) ||strs.size() != 4) {
        return 0;
    }
    Room* room = roomlist_find(room_list, strs[1]);
    if (room) {
        room->status = strs[3];
        return 1;
    }
    Item* item = itemvec_find(item_vec, strs[1]);
    if (item) {
        item->status = strs[3];
        return 1;
    }
    Container* container = containervec_find(container_vec, strs[1]);
    if (container) {
        container->status = strs[3];
        return 1;
    }
    Creature* creature = creaturevec_find(creature_vec, strs[1]);
    if (creature) {
        creature->status = strs[3];
        return 1;
    }
    
    return 0;
}

int try_gameover(string input, bool& run) {
    if (input == "Game Over") {
        cout << "Victory!" << endl;
        run = 0;
        return 1;
    }
    
    return 0;
}

//.............................................................................
vector<string> split(const string &txt, char ch) {
    unsigned long pos = txt.find(ch);
    unsigned long iPos = 0; //initial pos
    vector<string> strs;

    while(pos != -1) {
        strs.push_back(txt.substr(iPos, pos - iPos));
        iPos = pos + 1;
        
        pos = txt.find(ch, iPos);
    }

    strs.push_back(txt.substr(iPos, txt.size()-iPos));
    
    return strs;
}

Item* inventory_find_item(const list<Item*> inventory, string name) {
    auto it = inventory.begin();
    while (it != inventory.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}

Item* itemvec_find(vector<Item*> Item_vec, string name) {
    auto it = Item_vec.begin();
    while (it != Item_vec.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}

Container* containervec_find(vector<Container*> container_vec, string name) {
    auto it = container_vec.begin();
    while (it != container_vec.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}

Creature* creaturevec_find(vector<Creature*> creature_vec, string name) {
    auto it = creature_vec.begin();
    while (it != creature_vec.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}

Room* roomlist_find(const list<Room*>& room_list, string name) {
    auto it = room_list.begin();
    while (it != room_list.end()) {
        if ((*it)->get_name() == name) {
            return (*it);
        }
        it++;
    }
    return 0;
}

