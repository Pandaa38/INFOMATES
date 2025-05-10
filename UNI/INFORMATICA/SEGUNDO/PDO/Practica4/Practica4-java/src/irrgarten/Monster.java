
package irrgarten;

/**
 *
 * @author juan
 */
public class Monster extends LabyrinthCharacter{
    
    private static final int INITIALHEALTH = 5;
    
    Monster(String name, float intelligence, float strenght){
        super(name, intelligence, strenght, INITIALHEALTH);
    }
    
    @Override
    public float attack(){
        return Dice.intensity(this.getStrength());
    }
    
    @Override
    public boolean defend(float receivedAttack){
        
        boolean isDead = dead();
        if(!isDead){
            if(Dice.intensity(this.getIntelligence()) < receivedAttack){
                gotWounded();
                isDead = dead();
            }
        }
        return isDead;
    }
}
