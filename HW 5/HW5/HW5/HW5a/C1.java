//import java.io.*;

public class C1 extends C0 {

   private int x;
   public int y;
   private float z;
   public Float c;
   

   public C1( ) {
      z = 1.5f;// f is float
      c = new Float(1.5f);//
      
   }
      
   public C1(int x, int yy, float zz) {
      this.x = x;
      y = yy;
      z = zz;

      a = new Integer(x);
      b = new Integer(y);
      c = new Float(zz);
   }

   public float getZ( ) {
      return z;
   }

   public float getC( ) {
      return c.floatValue( );
   }


  // public int getY( ) {
     // return -super.getY( ) + 1;//since y was declared as private it is not accessible.
   //}
}
