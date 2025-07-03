
package irrgarten;

import java.util.ArrayList;

/**
 *
 * @author juan
 */
public class FuzzyPlayer extends Player{
    public FuzzyPlayer(Player other){
        super(other);
    }
    
    @Override
    public Directions move(Directions direction, ArrayList<Directions> validMoves){
        Directions preference = super.move(direction, validMoves);
        return Dice.nextStep(preference, validMoves, this.getIntelligence());
    }
    @Override
    public float attack(){
        return this.sumWeapons() + Dice.intensity(this.getStrength());
    }
    @Override
    protected float defensiveEnergy(){
        return this.sumShields()+ Dice.intensity(this.getIntelligence());
    }
    @Override
    public String toString(){
        return "(Fuzzy Player) " + super.toString();
    }
}
