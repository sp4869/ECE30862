#include <string>
#include <iostream>
class B {
public:
B( ) { }
 void m1( ) {std::cout << "B::m1" << std::endl;}
  virtual void m2( ) {
std::cout << "B::m2" << std::endl;
}
private:
virtual void m3( ) {
std::cout << "B::m3" << std::endl;
}
virtual void m4( ) {
std::cout << "B::m4" << std::endl;
}
};
class D1 : public B {
public:
D1( ) { }
~D1( ) { };
 void m1( ) {
std::cout << "D1::m1" << std::endl;
}
 void m2( ) {
std::cout << "D1::m2" << std::endl;
}
private:
virtual void m3( ) {
std::cout << "D1::m3" << std::endl;
}
virtual void m4( ) {
std::cout << "D1::m4" << std::endl;
}
};
class D2 : public D1 {
public:
D2( ) { };
~D2( ) { };
void m1( ) {
std::cout << "D2::m1" << std::endl;
}
virtual void m2( ) {
std::cout << "D2::m2" << std::endl;
}
private:
void m3( ) {
std::cout << "D2::m3" << std::endl;
}
virtual void m4( ) {
std::cout << "D2::m4" << std::endl;
}
};
int main(int argc, char * argv[ ]) {
// reminder: D1 d1; uses 0 arg const. for D1
B b; B* bP = &b; B& bR = b;
D1 d1; D1* d1P = &d1; D1& d1R = d1;
D2 d2; D2* d2P = &d2; D2& d2R = d2;
//d1.m1( ); // Q1
//d1R.m4( ); // Q2
bP = d1P; bR = d1R; b = d1;
//b.m1( ); // Q3
//b.m2( ); // Q4
bP->m1( ); // Q5
//bP->m2( ); // Q6
//bR.m2( ); // Q7
B& bR2 = d1;
bR2.m1();
bR2.m2( ); // Q8
d1P = d2P;
B& bR3 = d2R;
d1P->m1( ); // Q9
d1P->m2( ); // Q10
bR3.m1( ); // Q11
bR3.m2( ); // Q12
}
