
package irrgarten;

import java.util.ArrayList;

/**
 *
 * @author juan
 */
public class Labyrinth {
    private static final char BLOCK_CHAR = 'X';
    private static final char EMPTY_CHAR = '-';
    private static final char MONSTER_CHAR = 'M';
    private static final char COMBAT_CHAR = 'C';
    private static final char EXIT_CHAR = 'E';
    private static final int ROW = 0;
    private static final int COL = 1;
    
    
    private int nRows;
    private int nCols;
    private int exitRow;
    private int exitCol;
    
    
    private Monster [][] monsters;
    private Player [][] players;
    private char [][] labyrinth;
    
    
    Labyrinth(int nRows, int nCols, int exitRow, int exitCol){
        this.nRows = nRows;
        this.nCols = nCols;
        this.exitRow = exitRow;
        this.exitCol= exitCol;
        
         // Definimos tamaño del laberinto, players y monsters
        this.labyrinth = new char [nRows][nCols];
        this.players = new Player [nRows][nCols];
        this.monsters = new Monster[nRows][nCols];
        
        // Inicializaremos la matrice laberinto con valor por defecto
        // EMPTY_CHAR
        for (int i=0; i<this.nRows; i++){
            for(int j=0; j<this.nCols; j++){
                this.labyrinth[i][j]=EMPTY_CHAR;
            }
        }
        
        // Definimos casilla salida
        this.labyrinth[exitRow][exitCol]=EXIT_CHAR;
    }
    public void spreadPlayers(ArrayList<Player> players){
        for(Player p:players){
            int []pos = randomEmptyPos();
            putPlayer2D(-1,-1, pos[ROW], pos[COL], p);
        }
        /*
        for (int i=0; i<players.size(); i++){
            
            int [] pos = randomEmptyPos();
            putPlayer2D(INVALID_POS, INVALID_POS, pos[ROW], pos[COL], players.get(i));
        }
        */
    }
    public boolean haveAWinner(){
        return players[exitRow][exitCol] != null;
    }
    public String toString(){

        // Cálculo del número de caracteres que debe ocupar cada parte
        int filSize = Integer.toString(this.nRows-1).length();
        int colSize = Integer.toString(this.nCols-1).length();
        int nPlayersSize = Integer.toString(this.players.length-1).length();
        
        // Cálculo del tamaño máximo
        int maxSize = Math.max(Math.max(filSize, colSize), nPlayersSize);
        final String FORMAT = "%"+maxSize+"s";

        // Cadena a devolver
        String toReturn="";

        // Índices en cada columna
        toReturn+=" " + String.format(FORMAT, " ");
        for (int i=0; i<this.nCols; i++){
            toReturn+=String.format(FORMAT, i)+" ";
        }
        toReturn+="\n";


        for(int r=0; r<this.nRows; r++){
            toReturn+=String.format(FORMAT, r)+" "; // Índices en cada fila
            for(int c=0; c<this.nCols; c++){
                toReturn+=String.format(FORMAT, this.labyrinth[r][c])+" ";
            }
            toReturn+="\n";
        }
        return toReturn;
    }

    public void addMonster(int row, int col, Monster monster){
        if( posOk(row, col) && emptyPos(row, col) ){
            monster.setPos(row, col);
            monsters[row][col] = monster;
            labyrinth[row][col] = MONSTER_CHAR;
        }
    }
    public Monster putPlayer(Directions direction, Player player){
        int oldRow=player.getRow();
        int oldCol=player.getCol();
        
        int[] newPos = dir2Pos(oldRow,oldCol,direction);
        Monster monster = putPlayer2D(oldRow, oldCol, newPos[ROW], newPos[COL],player);
        
        return monster;
    }
    public void addBlock(Orientation orientation, int startRow, int startCol, int length){
        
        int incRow=0,incCol=0;
        if(orientation == Orientation.VERTICAL)
            incRow++;
        else
            incCol++;
        
        int row=startRow, col=startCol;
        
        while(posOk(row,col)&&emptyPos(row,col)&&length>0){
            this.labyrinth[row][col] = BLOCK_CHAR;
            row+=incRow;
            col+=incCol;
            length--;
        }
    }
    public ArrayList<Directions> validMoves(int row, int col){
        
        ArrayList<Directions> output = new ArrayList<>();
        
        if(canStepOn(row+1, col))
            output.add(Directions.DOWN);
        if(canStepOn(row-1, col))
            output.add(Directions.UP);
        if(canStepOn(row, col+1))
            output.add(Directions.RIGHT);
        if(canStepOn(row, col-1))
            output.add(Directions.LEFT);
            
        return output;
    }
    
    
    private boolean posOk(int row, int col){
        return (row >= 0 && col >= 0 && row < nRows && col < nCols);
    }
    private boolean emptyPos(int row, int col){
        return labyrinth[row][col] == EMPTY_CHAR;
    }
    private boolean monsterPos(int row, int col){
        return labyrinth[row][col] == MONSTER_CHAR;
    }
    private boolean exitPos(int row, int col){
        return labyrinth[row][col] == EXIT_CHAR;
    }
    private boolean combatPos(int row, int col){
        return labyrinth[row][col] == COMBAT_CHAR;
    }
    private boolean canStepOn(int row, int col){
        boolean can = posOk(row, col);
        can = can && (emptyPos(row, col) || exitPos(row, col) || monsterPos(row, col)); 
        return can;
    }
    private void updateOldPos(int row, int col){
        if(posOk(row, col)){
            if(combatPos(row, col))
                labyrinth[row][col] = MONSTER_CHAR;
            else
                labyrinth[row][col] = EMPTY_CHAR;
        }
        
    }
    private int[] dir2Pos(int row, int col, Directions direction){
        
        int[] pos = {row,col};
        
        switch(direction){
            case DOWN -> pos[ROW]++;
            case UP -> pos[ROW]--;
            case LEFT -> pos[COL]--;
            case RIGHT -> pos[COL]++;
        }
        return pos;
    }
    private int[] randomEmptyPos(){
        
        int[] pos = new int [2];
        do{
            pos[ROW] = Dice.randomPos(nRows);
            pos[COL] = Dice.randomPos(nCols);
        }while(!emptyPos(pos[ROW],pos[COL]));
        
        return pos;
    }
    private Monster putPlayer2D(int oldRow, int oldCol, int row, int col, 
            Player player){
        
        Monster output = null;
        
        if(canStepOn(row,col)){
            if(posOk(oldRow, oldCol) && players[oldRow][oldCol] == player){
                updateOldPos(oldRow, oldCol);
                players[oldRow][oldCol]=null;
            }
            
            if(monsterPos(row, col)){
                labyrinth[row][col] = COMBAT_CHAR;
                output = monsters[row][col];
            }
            else{
                this.labyrinth[row][col]=player.getNumber();
            }
            players[row][col] = player;
            player.setPos(row, col);
        }
                
        return output;
    }
            
}
