
package irrgarten;

/**
 *
 * @author juan
 */
public class WeaponCardDeck extends CardDeck<Weapon>{
    
    @Override
    protected void addCards(){
        for(int i=0; i < WeaponCardDeck.TAM_MAX; i++){
            this.addCard(new Weapon(Dice.shieldPower(), Dice.usesLeft()));
        }
    }
}
