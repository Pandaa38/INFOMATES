
package irrgarten;

import irrgarten.UI.TextUI;
import irrgarten.controller.Controller;


/**
 *
 * @author juan
 */
public class Test {
    
    public static void main ( String [ ] args ) {
        
        final int N_PLAYERS = 1;

        TextUI vista = new TextUI();
        
        Game juego = new Game(N_PLAYERS);
        Controller controlador = new Controller(juego, vista);

        controlador.play();
    }
    
}
