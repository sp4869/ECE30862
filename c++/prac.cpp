#include<iostream>
#include<string>
using namespace std;

class human{

private:
  int age;
  int getAge(){
    return (age - 5);
  }
public:
  string name;
  //  human(){
  //  cout << "called" << endl;
  // }
  void display()
  {
    cout<< getAge() << endl;
  }
  void setAge(int value) {
    age = value;
  }
};

human::human(){
 cout << "called"<<endl;
}
//void human::display(){
// cout<< name <<endl;

//}
int main(){
  // human a;
   //human * ptr = new human();//returns adddress of human
  // ptr->name = "crap";
  // a.display();
  // ptr->setAge(25);
  // ptr->display();
  return 1;
}
