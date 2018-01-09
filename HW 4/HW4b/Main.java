public class Main {

   public static void main(String[] args) {

      B b = new B( );
      D1 d1 = new D1( );
      D2 d2 = new D2( );

      System.out.println("Base and b calls");
      B.f1( ); //it will print B1 f1
    //  B.f2( );//it is an error because it is declared as private 
      b.f1( );// prints B f1 .Declared as static so call using class B and not instance b 
    //  b.f2( );//error ,private function.
      b.f3( ); //will print B f3
    //  b.f4( ); //error,private function
     // b.f5( ); //This will be an error .f5 is not declared in B.java
      b.bCaller( );//will print B f1,B f2,B f3,B f4.
      System.out.println(" ");//prints empty line

      System.out.println("D1 and d1 calls");
      D1.f1( ); //prints D1 f1
      //D1.f2( );//error,not declared. 
      d1.f1( );//prints D1 f1 .static function use D 
     // d1.f2( );//error because it is not declared and is a private function 
      d1.f3( ); //prints D1 f3.
     // d1.f4( );//it is an error because it is declared as private 
      d1.f5( ); // it will print D1 f5.
     // d1.f6( );//this will be an error because it is a private function 
     // d1.f7( );//this will be an error because it is not declared
 //     d1.d1Caller( );//will be an error because f2 is called and it is not defined in the class.
      System.out.println(" "); //prints empty line
     
      System.out.println("d1.bCaller");//d1.bcaller
      d1.bCaller( );// this will have an error because f2 is not defined in d1.java.
      System.out.println(" ");//prints empty line

      System.out.println("D2 and d2 calls");
      D2.f1( ); //this will print D2 f1
   //   D2.f2( );//this is an error it is a private function in B.java 
      d2.f1( );//this is static function and will print D2 f1
     // d2.f2( );//error this is a private function in B.java 
      d2.f3( ); //this will print D2 f3
     // d2.f4( );//error,this is a private function in B.java
      d2.f5( ); //this will print D2 f5
     // d2.f6( );//error because it is a private function in D1 
      d2.f7( ); //it will print D2 f7.
      d2.d2Caller( );//this will have an error because f2 and f6 are not defined.
      System.out.println(" ");//prints empty lines
    }
}

