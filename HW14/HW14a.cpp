#include <string>
#include <iostream>
using namespace std;

class Base {
public:
   Base( ) { }
   virtual ~Base() { };
   virtual void f1( ) {cout << "B::f1 void" << endl;}
   void f2( ) {cout << "B::f2 void" << endl;}
   void f2(int) {cout << "B::f2 int" << endl;}
   void f3(int) {cout << "B::f3 int" << endl;}
   virtual void callF1( ) {this->f1( );}
private: 
};

class Derived : public Base {
public:
   Derived( ) { }
   virtual ~Derived() { };
   virtual void f1( ) {cout << "D::f1 void" << endl;}
   void f2( ) {cout << "D::f2 void" << endl;}
   virtual void f3(int) {cout << "D::f3 int" << endl;}
   virtual void callF1( ) {this->f1( );}
};

class Derived2 : public Derived {
public:
   Derived2( ) { }
   virtual ~Derived2() { };
   void f3(int) {cout << "D2::f3 int" << endl;}
};

int main(int argc, char * argv[ ]) {
   Base* bP = new Base( );
   Base bO = Base( );
   Derived* dP = new Derived( );
   Derived dO = Derived( );
   Derived2* d2P = new Derived2( );
   Derived2 d2O = Derived2( );

   bP->f1( );//B::f1 void
   bP->f2( );//B ::f2 void
   bP->f2(1);//B::f2 int
   bP->callF1( );//B::f1 void
   bO.f1( );//B::f1 void
   bO.f2( );//B::f2 void
   bO.f2(1);//B::f2 int
   bO.callF1( );//B::f1 void

   bP = dP;
   bO = dO;
   bP->f1( );//D::f1 void
   bP->f2( );//B::f2 void
   bP->f2(1);//B::f2 int
   bP->callF1( );//D::f1 void
   bO.f1( );//B::f1 void
   bO.f2( );//B::f2 void
   bO.f2(1);//B::f2 int
   bO.callF1( );//B::f1 void

   dP->f1( );//D::f1 void
   dP->f2( );//D::f2 void
   // dP->f2(1);doesnt have an int parameter
   dP->callF1( );//D::f1 void
   dO.f1( );//D::f1 void
   dO.f2( );//D::f2 void
   //   dO.f2(1);
   dO.callF1( );//D::f1 void

   bP = d2P;
   dP = d2P;
   bO = d2O;
   dO = d2O;

   bP->f3(1);//B::f3 int
   dP->f3(1);//D2::f3 int
   d2P->f3(1);//D2::f3 int
   bO.f3(1);//B::f3 int
   dO.f3(1);//D::f3 int
   d2O.f3(1);//D2::f3 int


  string b = "Ryan";
  string n = "AKC";
  string ex;
  ex = n.append(b);
  cout<< ex <<endl;
}
