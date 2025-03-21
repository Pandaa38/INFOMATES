
package irrgarten;

import java.util.ArrayList;

/**
 *
 * @author juan
 */
public class Game {
    private static final int MAXROUNDS = 10;
    
    private int currentPlayerIndex;
    private String log;
    
    private ArrayList<Player> players;
    private ArrayList<Monster> monsters;
    
    private Player currentPlayer;
    private Labyrinth labyrinth;
    
    Game(int nplayers){
        // Definimos casilla de salida
        int exitRow=Dice.randomPos();
        int exitCol=Dice.randomPos();

        // Inicializamos los vectores de jugadores y monstruos
        this.players=new ArrayList<>();
        this.monsters=new ArrayList<>();
        
        // Creamos los nplayers y los introducimos en el vector de players
        for(int i=0; i<nplayers; i++)
            this.players.add(new Player(Character.forDigit(i, 10),
                                    Dice.randomIntelligence(), Dice.randomStrength()));
        
                
        // Definimos el jugador que empezará, es decir, el currentPlayer
        this.currentPlayerIndex=Dice.whoStarts(nplayers);
        this.currentPlayer=this.players.get(this.currentPlayerIndex);
        
        // Inicializamos la instancia de laberinto
        this.labyrinth= new Labyrinth(ROWS, COLS, exitRow, exitCol);
        // Se configura con bloques y mosntruos el laberinto
        this.configureLabyrinth();

        // Se distribuyen los jugadores por el laberinto
        this.labyrinth.spreadPlayers(this.players);
        
        // Inicializamos log
        this.log="- Game just started.\n";
    }
    
    public boolean finished(){
        return this.labyrinth.haveAWinner();
    }
    public boolean nextStep(Directions preferredDirection){
        throw new UnsupportedOperationException();
        //PRACTICA 3 -------------------------------------------
    }
    public GameState getGameState(){
        String infoPlayers="";
        String infoMonsters="";
        
        // Formato jugadores
        for (int i=0; i<this.players.size(); i++){
            infoPlayers+="- " + this.players.get(i).toString()+"\n";
        }
        
        // Formato monstruos
        for (int i=0; i<this.monsters.size(); i++){
            infoMonsters+="- " + this.monsters.get(i).toString()+"\n";
        }
        
        // Estado general del juego
        GameState state = new GameState (this.labyrinth.toString(), infoPlayers,
                                infoMonsters, this.currentPlayerIndex, this.finished(), this.log);
        
        return state;
    }
    
    
    
    private void configureLabyrinth(){
        
    }
    private void nextPlayer(){
        this.currentPlayerIndex=(this.currentPlayerIndex+1)%players.size();
        this.currentPlayer=players.get(currentPlayerIndex);
    }
    private Directions actualDirection(Directions preferredDirection){
        throw new UnsupportedOperationException();
        //PRACTICA 3 -------------------------------------------
    }
    private GameCharacter combat(Monster monster){
        throw new UnsupportedOperationException();
        //PRACTICA 3 -------------------------------------------
    }
    private void manageReward(GameCharacter winner){
        throw new UnsupportedOperationException();
        //PRACTICA 3 -------------------------------------------
    }
    private void manageResurrection(){
        throw new UnsupportedOperationException();
        //PRACTICA 3 -------------------------------------------
    }
    private void logPlayerWon() {
        log = log + "El jugador ha ganado el combate.\n";
    }

    private void logMonsterWon() {
        log = log + "El monstruo ha ganado el combate.\n";
    }

    private void logResurrected() {
        log = log + "El jugador ha resucitado.\n";
    }

    private void logPlayerSkipTurn() {
        log = log + "El jugador ha perdido el turno por estar muerto.\n";
    }

    private void logPlayerNoOrders() {
        log = log + "El jugador no ha seguido las instrucciones del jugador humano (no fue posible).\n";
    }

    private void logNoMonster() {
        log = log + "El jugador se ha movido a una celda vacía o no le ha sido posible moverse.\n";
    }

    private void logRounds(int rounds, int max) {
        log = log + "Se han producido " + rounds + " de " + max + " rondas de combate.\n";
    }
}
