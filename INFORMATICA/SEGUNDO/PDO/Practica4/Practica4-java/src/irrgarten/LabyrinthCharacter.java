
package irrgarten;

/**
 *
 * @author juan
 */
abstract class LabyrinthCharacter {
    private final static int INVALID_POS = -1;
    
    private String name;
    
    private float intelligence;
    private float strength;
    private float health;
   
    private int row;
    private int col;
    
    public LabyrinthCharacter(String name, float intelligence, float strength, float health){
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strength;
        this.health = health;
        
        setPos(INVALID_POS, INVALID_POS);
    }
    public LabyrinthCharacter(LabyrinthCharacter other){
        this.name = other.name;
        this.intelligence = other.intelligence;
        this.strength = other.strength;
        this.health = other.health;
        
        setPos(other.row, other.col);
    }
    
    public boolean dead(){
        return health <= 0;
    }
    public int getRow(){ return row;}
    public int getCol(){ return col;}
    
    protected float getIntelligence() { return intelligence; }
    protected float getStrength(){ return this.strength; }
    protected float getHealth(){ return this.health; }
    
    protected void setHealth(float health){
        this.health=health;
    }
    
    public void setPos(int row, int col){
        this.row=row;
        this.col=col;
    }
    
    /**
     * Muestra las características del personaje
     * @return devuelve una cadena con la información del personaje y su posición
     */
    @Override
    public String toString() {
    return name + ": \n\t" + 
           "Inteligencia = " + intelligence + 
           "\n\tFuerza = " + strength + 
           "\n\tVida = " + health + 
           "\n\tPos = (" + row + ", " + col + ")";
    }
    
    
    protected void gotWounded(){
        this.health--;
    }
    
    public abstract float attack();
    public abstract boolean defend (float attack);
}
