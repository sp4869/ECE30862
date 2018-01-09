#include <iostream>
using namespace std;
class X 
{
  public:
  int j;
  X(int i) : j(i) { }

  //X(const X& other) {
  //if ( this != &other ) j = -other.j;
  //}

  ~X() { }
};

int main() 
{
  X x1(2);
  X x2 = x1;
  cout << x1.j;
  cout << " " << x2.j << endl;
  return 0;
}
