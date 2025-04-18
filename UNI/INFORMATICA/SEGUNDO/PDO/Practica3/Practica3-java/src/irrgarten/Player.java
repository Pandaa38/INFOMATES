
package irrgarten;

import java.util.ArrayList;

/**
 *
 * @author juan
 */
public class Player {
    private static final int MAXWEAPONS = 2;
    private static final int MAXSHIELDS = 3;
    private static final int INITIALHEALTH = 10;
    private static final int HITS2LOSE = 3;
    
    private String name;
    private char number;
    private float intelligence;
    private float strength;
    private float health;
    private int row;
    private int col;
    private int consecutiveHits = 0;
    
    private ArrayList<Weapon> weapons;
    private ArrayList<Shield> shields;
    
    Player(char number, float intelligence, float strength){
        
        //ATRIBUTOS
        name = "Player#" + number;
        this.number = number;
        this.intelligence = intelligence;
        this.strength = strength;
        
        health = INITIALHEALTH;
        consecutiveHits = 0;
        
        //ARRAYLISTS
        weapons = new ArrayList<Weapon>();
        shields = new ArrayList<Shield>();        
    }
    public void resurrect(){
        
        //Limpiar arrays
        weapons.clear();
        shields.clear();
        
        //Restaurar atributos
        health = INITIALHEALTH;
        resetHits();
    }
    public int getRow(){
        return row;
    }
    public int getCol(){
        return col;
    }
    public char getNumber(){
        return number;
    }
    public void setPos(int row, int col){
        this.row = row;
        this.col = col;       
    }
    public boolean dead(){
        return health == 0;
    }
    public Directions move(Directions direction, ArrayList<Directions> validMoves){
        throw new UnsupportedOperationException();
        //PRACTICA 3 **************************************
    }
    public float attack(){
        return sumWeapons() + strength;
    }
    public boolean defend(float receivedAttack){
        return manageHit(receivedAttack);
    }
    public void receiveReward(){
        //PRACTICA 3 **************************************
    }
    public String toString() {
    return name + ": \n\t" + 
           "Inteligencia = " + intelligence + 
           "\n\tFuerza = " + strength + 
           "\n\tVida = " + health + 
           "\n\tPos = (" + row + ", " + col + ")";
    }
    
    //PRIVATE-------------------------
    private void receiveWeapon(Weapon w){
        //PRACTICA 3 **************************************
    }
    private void receiveShield(Shield s){
        //PRACTICA 3 **************************************
    }
    private Weapon newWeapon(){
        Weapon w = new Weapon(Dice.weaponPower(), Dice.usesLeft());
        return w;
    }
    private Shield newShield(){
        Shield s = new Shield(Dice.shieldPower(), Dice.usesLeft());
        return s;
    }
    private float sumWeapons(){
        float sum = 0;
        for(Weapon w : weapons){
            sum += w.attack();
        }
        return sum;
    }
    private float sumShields(){
        float sum = 0;
        for(Shield s : shields){
            sum += s.protect();
        }
        return sum;
    }
    private float defensiveEnergy(){
        return sumShields() + this.intelligence;
    }
    private boolean manageHit(float receivedAttack){
        boolean lose;
        
        if(defensiveEnergy() < receivedAttack){
            gotWounded();
            incConsecutiveHits();
        }
        else
            resetHits();
        
        if(consecutiveHits == HITS2LOSE || dead()){
            resetHits();
            lose = true;
        }
        else 
            lose = false;
        
        return lose;
    }
    private void resetHits(){
        this.consecutiveHits = 0;
    }
    private void gotWounded(){
        this.health--;
    }
    private void incConsecutiveHits(){
        this.consecutiveHits++;
    }
    
    
}
