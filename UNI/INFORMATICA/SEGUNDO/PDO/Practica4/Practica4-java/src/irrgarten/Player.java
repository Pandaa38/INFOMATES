
package irrgarten;

import java.util.ArrayList;

/**
 *
 * @author juan
 */
public class Player extends LabyrinthCharacter{
    private static final int MAXWEAPONS = 2;
    private static final int MAXSHIELDS = 3;
    private static final int INITIALHEALTH = 10;
    private static final int HITS2LOSE = 3;
    
    private int consecutiveHits = 0;
    private char number;
    
    private ArrayList<Weapon> weapons;
    private ArrayList<Shield> shields;
    
    private WeaponCardDeck weaponCardDeck;
    private ShieldCardDeck shieldCardDeck;
    
    public Player(char number, float intelligence, float strength){
        
        super("Player#" + number, intelligence, strength, INITIALHEALTH);
        
        //ATRIBUTOS
        this.number = number;
        consecutiveHits = 0;
        
        //ARRAYLISTS
        weapons = new ArrayList<Weapon>();
        shields = new ArrayList<Shield>();     
        
        //DECKS
        weaponCardDeck = new WeaponCardDeck();
        shieldCardDeck = new ShieldCardDeck();
    }
    public Player(Player other){
        
        super(other);
        
        this.number = other.number;
        this.consecutiveHits = other.consecutiveHits;
        
        weapons = new ArrayList<Weapon>(other.weapons);
        shields = new ArrayList<Shield>(other.shields);
    }
    public void resurrect(){
        
        //Limpiar arrays
        weapons.clear();
        shields.clear();
        
        //Restaurar atributos
        this.setHealth(INITIALHEALTH);
        resetHits();
    }
    
    public char getNumber(){ return number; }
    
    public Directions move(Directions direction, ArrayList<Directions> validMoves){
        int size = validMoves.size();
        boolean contained = validMoves.contains(direction);
        
        Directions direct;
        
        if(size > 0 && !contained){
            direct = validMoves.get(0);
        }else
            direct = direction;
        
        return direct;
    }
    @Override
    public float attack(){
        return sumWeapons() + this.getStrength();
    }
    @Override
    public boolean defend(float receivedAttack){
        return manageHit(receivedAttack);
    }
     public void receiveReward(){
        // Weapons rewards
        int wReward = Dice.weaponsReward();
        for (int i=0; i<wReward; i++)
            this.receiveWeapon(this.newWeapon());
        
        // Shields rewards
        int sReward = Dice.shieldsReward();
        for (int i=0; i<sReward; i++)
            this.receiveShield(this.newShield());
        
        this.setHealth(Dice.healthReward() + this.getHealth());

    }
    @Override 
    public String toString(){
        String toReturn=super.toString();
        toReturn+="\n\tGolpes consecutivos = " + this.consecutiveHits;
        
        // Bucles para mostrar con un formato determinado el array de
        // armas y escudos del jugador
        String toWeapons="[";
        int tamWeapons=this.weapons.size();
        for(int i=0; i<tamWeapons-1; i++){
            toWeapons+=this.weapons.get(i).toString()+", ";
        }
        if (tamWeapons>0)
            toWeapons+=this.weapons.get(tamWeapons-1);
        toWeapons+="]";
        
        String toShields="[";
        int tamShields=this.shields.size();
        for(int i=0; i<tamShields-1; i++){
            toShields+=this.shields.get(i).toString()+", ";
        }
        if (tamShields>0)
            toShields+=this.shields.get(tamShields-1);
        toShields+="]";
        
        // Definimos el formato final para el toString
        toReturn+="\n\tw:" + toWeapons+"\n\tsh:"+toShields;
        
        return toReturn;
    }
    
    //PRIVATE-------------------------
    private void receiveWeapon(Weapon w){
        for (int i=0; i<weapons.size(); i++){
            if (weapons.get(i).discard()){
                weapons.remove(i);
                i--;
            }
        }

        // Añadimos el escudo al jugador si cabe
        if (weapons.size() < MAXWEAPONS)
            weapons.add(w);
    }
    private void receiveShield(Shield s){
        for (int i=0; i<shields.size(); i++){
            if (shields.get(i).discard()){
                shields.remove(i);
                i--;
            }
        }

        // Añadimos el escudo al jugador si cabe
        if (shields.size() < MAXSHIELDS)
            shields.add(s);
    }
    private Weapon newWeapon(){
        Weapon w = new Weapon(Dice.weaponPower(), Dice.usesLeft());
        return w;
    }
    private Shield newShield(){
        Shield s = new Shield(Dice.shieldPower(), Dice.usesLeft());
        return s;
    }
    protected float sumWeapons(){
        float sum = 0;
        for(Weapon w : weapons){
            sum += w.attack();
        }
        return sum;
    }
    protected float sumShields(){
        float sum = 0;
        for(Shield s : shields){
            sum += s.protect();
        }
        return sum;
    }
    protected float defensiveEnergy(){
        return sumShields() + this.getIntelligence();
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
    private void incConsecutiveHits(){
        this.consecutiveHits++;
    }    
}
