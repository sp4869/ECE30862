//import java.io.*;

class Main {

   public static void main(String args[]) {
      C0 c01 = new C0( );
      C0 c02 = new C0(1,2);
      C1 c11 = new C1( );
      C1 c12 = new C1(3, 4, 5.0f);

      System.out.println("c01.a.intValue( ): " + c01.a.intValue( ));//a = 0
      System.out.println("c01.b.intValue( ): " + c01.b.intValue( ));//b = 0
   //   System.out.println("c01.x: " + c01.x);//error because X is private 
     // System.out.println("c01.y: " + c01.y);//error because y is private

      System.out.println("c02.a.intValue( ): " + c02.a.intValue( ));//a = 1
      System.out.println("c02.b.intValue( ): " + c02.b.intValue( ));//b = 2
     // System.out.println("c02.x: " + c02.x);//error because x is private
     // System.out.println("c02.y: " + c02.y);//error because y is private

      System.out.println("c11.a.intValue( ): " + c11.a.intValue( ));//a = 0.extends c0
      System.out.println("c11.b.intValue( ): " + c11.b.intValue( ));//b = 0.extends c0
      System.out.println("c11.c.floatValue(): " + c11.c.floatValue());//c = 1.5
     // System.out.println("c11.x: " + c11.x);//error because x is declared as private
      System.out.println("c11.y: " + c11.y);// y = 0 since C1 extends c0
     // System.out.println("c11.z: " + c11.z);//error,because z is private.

      c01 = c12;
      System.out.println("c12.a.intValue( ): " + c01.a.intValue( ));// a = 3 from C1
      System.out.println("c12.b.intValue( ): " + c01.b.intValue( ));// b = 4 from C1
      System.out.println("c12.c.floatValue(): " + ((C1) c01).c.floatValue());//c = 5.0 from C1
     // System.out.println("c12.x: " + c01.x);//error because x is declared as private in c0
     // System.out.println("c12.y: " + c01.y);//error because y is declared as private.
     // System.out.println("c12.z: " + c01.z);// Z is not declared in C0

      System.out.println("c02.getA( ): " + c02.getA( ));// a = -1 using getb
      System.out.println("c02.getB( ): " + c02.getB( ));//b = -2 using getb
      System.out.println("c02.getX( ): " + c02.getX( ));// x = -1 using the getx
    //  System.out.println("c02.getY( ): " + c02.getY( ));//error because getY is private

      System.out.println("c12.getA( ): " + c01.getA( ));//a = -3 because of getA
      System.out.println("c12.getB( ): " + c01.getB( ));//b = -4 because of getB
      System.out.println("c12.getC( ): " + ((C1) c01).getC( ));//c = 5.0 because of casting C1
      System.out.println("c12.getX( ): " + c01.getX( ));//x = -3 using getX
     // System.out.println("c01.getY( ): " + c01.getY( ));// error because private int getY
     // System.out.println("c01.getZ( ): " + c01.getY( ));//error because y is declared private 
   }
}
