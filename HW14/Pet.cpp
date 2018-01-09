#include <iostream>
#include "canine.h"
#include "Pet.h"
#include <string>
using namespace std;
Pet::~Pet(){}
Pet::Pet(){}
void Pet::breed(){
  string b = "Ryan";
  string n = "AKC";
  string ex;
  ex = n.append(b);
  cout<< ex <<endl;
}
