
package irrgarten;

/**
 *
 * @author juan
 */
public class Shield extends CombatElement{
        
    public Shield(float protection, int uses){
        super(protection, uses);
    }
    
    public float protect(){
        return this.produceEffect();
    }
    
    @Override
    public String toString(){
        String thisClass = "S";
        return thisClass + super.toString();
    }
}
