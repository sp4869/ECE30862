//import java.io.*;

public class C0 {

   public Integer a;
   public Integer b;
   private int x;
   private int y;

   public C0( ) {
      this.x = 0;
      y = 0;

      a = new Integer(0);//a = 0
      b = new Integer(0);//b = 0
   }
      
   public C0(int x, int yy) {
      this.x = x;
      y = yy;

      a = new Integer(x);// a = 1
      b = new Integer(y);// y =2
   }

   public int getA( ) {
      return -a.intValue( );
   }

   public int getB( ) {
      return -b.intValue( );
   }

   public int getX( ) {
      return -x;
   }

   private int getY( ) {//should be made public to access y in the main
      return -y;
   }
}
