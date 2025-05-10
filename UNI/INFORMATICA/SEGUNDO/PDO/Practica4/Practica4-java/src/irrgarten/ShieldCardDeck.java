
package irrgarten;

/**
 *
 * @author juan
 */
public class ShieldCardDeck extends CardDeck<Shield>{
    
    @Override
    protected void addCards(){
        for(int i=0; i < ShieldCardDeck.TAM_MAX; i++){
            this.addCard(new Shield(Dice.shieldPower(), Dice.usesLeft()));
        }
    }
}
