public class D extends B implements I {

   public D( ) { };

  public void foo(int j) {i = 5;}  // B The i is declared in line 6 of I.java.The error occurs
  //because int j is declared and i.foo requires int i.
  
  //3) i is an instance variable because it is not declared as static and it uses an access modifier.It is declared 
  //outside any method declaration.
  
  //4) There is no error because B.java contains a definition of void foo(short). Since D extends B it is able to
  //access this definition.Interface only accepts abstract.
   public void foo(short s, D d,  double df) {System.out.println("D foo(short, D, double)");}

   public void bar(short s, D d,  double df) {System.out.println("D bar(short, D, double)");}

   public void dPrint( ) {
      System.out.println("i: "+i+", s: "+s);
   }
}
