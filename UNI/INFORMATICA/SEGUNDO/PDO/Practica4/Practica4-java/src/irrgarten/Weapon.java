
package irrgarten;

import irrgarten.Dice;

/**
 *
 * @author juan
 */
public class Weapon {
    private float power;
    private int uses;
    
    Weapon(float power, int uses){
        this.power = power;
        this.uses = uses;
    }
    
    public float attack(){
        float attack;
        if(this.uses > 0){
            attack = power;
            uses--;
        }else 
            attack = 0;
        
        return attack;        
    }
    
    public String toString(){
        return "W[" + power + "," + uses + "]";
    }
    
    public boolean discard(){
        return Dice.discardElement(uses);
    }
}
