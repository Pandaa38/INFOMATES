
package irrgarten;

/**
 *
 * @author juan
 */
public class Monster {
    
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
        
        row = -1; col = -1;
    }
    
    public boolean isDead(){ 
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
    void gotWounded(){
        health--;
    }
    boolean defend(float receivedAttack){
        throw new UnsupportedOperationException();
    }
}
