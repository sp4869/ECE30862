public class D1 extends B {

   public D1( ) { }

   public static void f1( ) {System.out.println("D1 f1");}
   public void f3( ) {System.out.println("D1 f3");}
   private static void f4( ) {System.out.println("D1 f4");}

   public void f5( ) {System.out.println("D1 f5");}
   private void f6( ) {System.out.println("D1 f6");}

 //  public void d1Caller( ) {f1( ); f2( );
 //  f3( ); f4( ); f5( ); f6( );}//f2 is not declared,was declared as private in the previous class so it will not extend
   }

