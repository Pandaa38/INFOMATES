
package irrgarten;

/**
 *
 * @author juan
 */
public class Monster {
    
    private static final int INITIALHEALTH = 5;
    
    private String name;
    private float intelligence;
    private float strenght;
    private float health;
    private int row;
    private int col;
    
    Monster(String name, float intelligence, float strenght){
        this.name = name;
        this.intelligence = intelligence;
        this.strenght = strenght;
        this.health = INITIALHEALTH;
        
        setPos(-1, -1);
    }
    
    public boolean dead(){ 
        return health == 0;
    }
    public float attack(){
        return Dice.intensity(strenght);
    }
    public void setPos(int row, int col){
        this.row = row;
        this.col = col;
    }
    public String toString(){
        String to_s = name + ": \n\t" + "Inteligencia = " + intelligence
                + "\n\tFuerza = " + strenght + "\n\tVida = " + health +
                "\n\t Pos = (" + row +", " + col + ")";
        
        return to_s;        
    }
    private void gotWounded(){
        health--;
    }
    boolean defend(float receivedAttack){
        
        boolean isDead = dead();
        if(!isDead){
            float defensiveEnergy = Dice.intensity(intelligence);
            if(defensiveEnergy < receivedAttack){
                gotWounded();
                isDead = dead();
            }
        }
        return isDead;
    }
}
