
package irrgarten;

import irrgarten.Dice;

/**
 *
 * @author juan
 */
public class Shield {
    private float protection;
    private int uses;
    
    Shield(float power, int uses){
        this.protection = power;
        this.uses = uses;
    }
    
    public float protect(){
        float protect;
        if(this.uses > 0){
            protect = protection;
            uses--;
        }else 
            protect = 0;
        
        return protect;        
    }
    
    public String toString(){
        return "S[" + protection + "," + uses + "]";
    }
    
    public boolean discard(){
        return Dice.discardElement(uses);
    }
}
