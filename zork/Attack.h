#ifndef ATTACK_H_
#define ATTACK_H_
#include <string>
#include <iostream>
#include <vector>


using namespace std;


class Attack {
public:
  Attack();
  void setPrint(string);
  void setObject(string);
  void setStatus(string);
  void addAction(string);
  
  string getPrint();
  string getObject();
  string getStatus();
  vector<string> getActions();

 private:
  string status;
  string object;
  string print;
  vector <string> actions;
  
  
};
#endif
