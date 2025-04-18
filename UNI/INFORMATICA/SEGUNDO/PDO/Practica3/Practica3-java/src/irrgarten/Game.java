
package irrgarten;

import java.util.ArrayList;

/**
 *
 * @author juan
 */
public class Game {
    
    // ---------------------- PERSONALIZACIÓN LABERINTO ---------------- 
    // Tamaño del laberinto
    /**
     * Número de filas del laberinto.
     */
    private static final int ROWS=7;
    /**
     * Número de columnas del laberinto.
     */
    private static final int COLS=7;
    

    // Monstruos a incluir
    /**
     * Número de monstruos a incluir en el laberinto.
     */
    private static final int NUM_MONSTERS=5;
    /**
     * Posiciones iniciales de los monstruos en el laberinto.
     */
    private static final int [][] INIT_MONSTERS= {{0,0}, {1,1}, {2,2}, {3,3}, {0,3}};
    
    // Bloques a incluir
    /**
     * Número de bloques a incluir en el laberinto.
     */
    private static final int NUM_BLOCKS=4;
    /**
    * Bloques iniciales a incluir en el laberinto donde el último parámetro indica la longitud.
    */
    private static final Object[][] INIT_BLOCKS = {
        {Orientation.HORIZONTAL, 1, 4, 3},
        {Orientation.VERTICAL, 2, 6, 3},
        {Orientation.HORIZONTAL, 4, 1, 4},
        {Orientation.VERTICAL, 5, 3, 2}
    };
    
    
    // ----------------------- DATOS GAME ------------------------
    private static final int MAXROUNDS = 10;
    
    private int currentPlayerIndex;
    private String log;
    
    private ArrayList<Player> players;
    private ArrayList<Monster> monsters;
    
    private Player currentPlayer;
    private Labyrinth labyrinth;
    
    public Game (int nplayers){
        // Definimos casilla de salida
        int exitRow=6;
        int exitCol=6;

        // Inicializamos los vectores de jugadores y monstruos
        this.players = new ArrayList<>();
        this.monsters = new ArrayList<>();
        
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
        // Inicializamos el vector de monstruos y los añadimos al laberinto
        for (int i=0; i<NUM_MONSTERS; i++){
            Monster monstruo=new Monster ("Monster "+i, Dice.randomIntelligence(), Dice.randomStrength());
            this.monsters.add(monstruo);
            this.labyrinth.addMonster(INIT_MONSTERS[i][0], INIT_MONSTERS[i][1], monstruo);
        }
        
         for (int i=0; i<NUM_BLOCKS; i++){
            this.labyrinth.addBlock((Orientation)INIT_BLOCKS[i][0], (int)INIT_BLOCKS[i][1], 
                    (int)INIT_BLOCKS[i][2], (int)INIT_BLOCKS[i][3]);
        }
        
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
