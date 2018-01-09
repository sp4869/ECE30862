class Main {

   public static void main(String args[]) {

      String[ ] labels = {"Long", "Int", "Long Clone", "Int Clone"};

      MyList [ ] mlArray = new MyList[4];

      MyList tmp = new LongList(null, 0);

      for (int i = 1; i < 11; i++) {
         tmp = new LongList((LongList) tmp, i);
      }
      mlArray[0] = tmp;

      tmp = new IntList(null, 0);
      for (int i = 1; i < 11; i++) {
         tmp = new IntList((IntList) tmp, i);
      }
      mlArray[1] = tmp;

      // put the clones into mlArray
      try {
         mlArray[2] = (MyList) mlArray[0].clone( );
         mlArray[3] = (MyList) mlArray[1].clone( );
      } catch (java.lang.CloneNotSupportedException e) {System.out.println("clone exception: "+e);}

      for (int list = 0; list < 4; list++) {
         System.out.println("");
         System.out.println(labels[list]);
         MyList ml = mlArray[list];
         while (ml != null) {
            ml.printNode( );
            System.out.println( );
            ml = ml.next( );
         }
      }
   }
}
