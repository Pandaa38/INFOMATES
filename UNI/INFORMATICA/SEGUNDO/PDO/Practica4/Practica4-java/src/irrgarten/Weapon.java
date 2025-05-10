
package irrgarten;

/**
 *
 * @author juan
 */
public class Weapon extends CombatElement {
    public Weapon(float power, int uses){
        super(power, uses);
    }
    
    public float attack(){
        return this.produceEffect();
    }
    
    @Override
    public String toString(){
        String thisClass = "W";
        return thisClass + super.toString();
    }
}
