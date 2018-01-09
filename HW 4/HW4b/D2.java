public class D2 extends D1 {

   public D2( ) { }

   public static void f1( ) {System.out.println("D2 f1");}
   public void f3( ) {System.out.println("D2 f3");}
   private static void f4( ) {System.out.println("D2 f4");}

   public void f5( ) {System.out.println("D2 f5");}
   public void f7( ) {System.out.println("D2 f7");}

   public void d2Caller( ) {f1( ); f2( );
   f3( ); f4( ); f5( ); f6( );f7( );//f2 and f6 are not declared in this class and are private in previous ones.
   }
}


