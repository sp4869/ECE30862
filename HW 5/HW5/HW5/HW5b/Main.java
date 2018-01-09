import java.io.*;

class Main {

   public static void main(String args[]) {
      char c = 0;
      short s = 1;
      int i = 2;
      float f = 0.0f;
      double df = 1.0;

      B b = new B( );
      D d = new D( );

      System.out.println("Direct calls");
      d.foo(d, f); // Error d cannot get converted into any operation
      d.foo(c, d, df);// Error char cannot get converted into short cannot get converted
      d.foo(df);// prints B:foo(double).
      d.foo(i); // int gets converted to float. B:foo(float)
      d.foo( );//error not defined
      d.foo(i, d, df);//Error.int cannot get converted into short.
      d.foo(c, b, f); //"B:foo(int, B, float)". Char gets converted into int
      d.foo(f); //prints D:foo(float).
      d.foo(c); //prints D:foo(float)
      d.foo(s, d, df); //prints B:foo(short, B, double)
      d.foo(i, d);//error int cannot get converted to short

      System.out.println("b.caller");//b.caller
      b.caller( ); // foo(d,f) is an error becasue d cannot get converted
      //foo(c,d,df) is an error because char cannot get convered into short
      //foo(s) - //B:foo(short)
      //foo(i); //int can get converted to double. B:foo(double)  
   
   }  
   
   
}
