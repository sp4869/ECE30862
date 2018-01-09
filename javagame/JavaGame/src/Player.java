
/**
    The Player.
*/
public class Player extends Creature {

    private static final float JUMP_SPEED = -.95f;
    private int health = 20;
   
    // private int maxHealth;
   // private int fire;
   // private int maxFire;
   // private boolean firing; 
 //   private int fireballDamage;

    private boolean onGround;
    public Player(Animation left, Animation right,
        Animation deadLeft, Animation deadRight)
    {
        super(left, right, deadLeft, deadRight);
    }


    public void collideHorizontal() {
        setVelocityX(0);
    }
   
  /*  public int getHealth(){
    	return health;
    }
    public int getmaxHealth(){
    	return maxHealth;
    }
    public int getFire(){
    	return fire;
    }
    public int getmaxFire(){
    	return maxFire;
    }
    public void setFiring(){
    	firing = true;
    }
    */
    
    public void collideVertical() {
        // check if collided with ground
        if (getVelocityY() > 0) {
            onGround = true;
        }
        setVelocityY(0);
    }


    public void setY(float y) {
        // check if falling
        if (Math.round(y) > Math.round(getY())) {
            onGround = false;
        }
        super.setY(y);
    }


    public void wakeUp() {
        // do nothing
    }


    /**
        Makes the player jump if the player is on the ground or
        if forceJump is true.
    */
    public void jump(boolean forceJump) {
        if (onGround || forceJump) {
            onGround = false;
            setVelocityY(JUMP_SPEED);
        }
    }
    
    //public void shoot(){
    	
   // }
    public void sethealth(int val){
         
    	health += val;
    	if (health > 40)
    	 {
    		  health = 40;
    	 }
    	if (health < 0)
    	{
    		health = 0;
    	}
           
    }
    
    public float getMaxSpeed() {
        return 0.5f;
    }

}
