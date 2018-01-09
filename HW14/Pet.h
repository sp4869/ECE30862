#ifndef pet_H
#define pet_H
#include <iostream>
#include <string>
using namespace std;

class Pet: public canine{
 public:
  Pet();
 ~Pet();
 virtual void breed();
};
#endif
