
public class Fireball extends Creature{
	private double speed;
	private int N = 10;
	public Fireball(Animation left, Animation right,Animation deadLeft, Animation deadRight)
	    {
	        super(left, right, deadLeft, deadRight);
	    }
    public double getspeed(){
    	return speed;
    }
    public void shoot(float x,float y,int direction){
    	this.setX(x);
    	this.setY(y);
    	setspeed(direction);
    	
    }
    public void setspeed(int val){
    	speed = val;
    	
    }
    public void updatefirball(){
    	//Take difference in position
    	//No of fireballs exceed N then he will inactive for 1 second.
        //this.setstate = dead     
    }
}

