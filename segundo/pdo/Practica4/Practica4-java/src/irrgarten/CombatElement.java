
package irrgarten;

/**
 *
 * @author juan
 */
abstract class CombatElement {
    
    private float effect;
    private int uses;
    
    public CombatElement(float effect, int uses){
        this.effect = effect;
        this.uses = uses;
    }
    
    protected float produceEffect(){
        
        float output = effect;
        
        if(uses>0)
            uses--;
        else
            output = 0;
        
        return output;
    }
    
    public boolean discard(){
        return Dice.discardElement(uses);
    }
    
    @Override
    public String toString(){
        return "[" + effect + ", " + uses + "]";
    }
}
