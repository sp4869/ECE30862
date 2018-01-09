#ifndef Mammal_H
#define Mammal_H
#include <iostream>
#include <string>
using namespace std;

class Mammal {
private:
       int legs;
public:
       Mammal(int a);
      ~Mammal();
       
      //irtual void getlegs();
      int getlegs();
};


#endif /* BASE_H */

