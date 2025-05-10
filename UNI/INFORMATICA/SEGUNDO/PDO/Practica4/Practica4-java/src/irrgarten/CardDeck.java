
package irrgarten;

import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author juan
 */
abstract class CardDeck<T extends CombatElement> {
    
    protected static final int TAM_MAX = 50;
    
    private ArrayList<T> cardDeck;
    
    public CardDeck(){
        cardDeck = new ArrayList<>();
    }
    
    protected abstract void addCards();
    
    protected void addCard(T card){
        cardDeck.add(card);
    }
    public T nextCard(){
        if(cardDeck.size()<=0){
            addCards();
            Collections.shuffle(cardDeck);
        }
        T selected = cardDeck.get(0);
        cardDeck.remove(0);
        return selected;
    }
    
}
