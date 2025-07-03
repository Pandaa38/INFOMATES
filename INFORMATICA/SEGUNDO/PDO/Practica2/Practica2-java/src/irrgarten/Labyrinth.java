
package irrgarten;

import java.util.ArrayList;

/**
 *
 * @author juan
 */
public class Labyrinth {
    private static final char BLOCKCHAR = 'X';
    private static final char EMPTYCHAR = '-';
    private static final char MONSTERCHAR = 'M';
    private static final char COMBATCHAR = 'C';
    private static final char EXITCHAR = 'E';
    private static final int ROW = 0;
    private static final int COL = 1;
    
    
    private int nRows;
    private int nCols;
    private int exitRow;
    private int exitCol;
    
    
    private Monster MonsterSquare[][];
    private Player PlayerSquare[][];
    private char LabyrinthSquare[][];
    
    
    Labyrinth(int nRows, int nCols, int exitRow, int exitCol){
        this.nRows = nRows;
        this.nCols = nCols;
        this.exitRow = exitRow;
        this.exitCol= exitCol;
        
    }
    public void spreadPlayers(ArrayList<Player> players){
        //PRACTICA 3 ---------------------------------------------------
    }
    public boolean haveAWinner(){
        return PlayerSquare[exitRow][exitCol] != null;
    }
    public String toString(){
        return "Laberinto";
    }
    public void addMonster(int row, int col, Monster monster){
        if( posOk(row, col) && emptyPos(row, col) ){
            monster.setPos(row, col);
            MonsterSquare[row][col] = monster;
            LabyrinthSquare[row][col] = MONSTERCHAR;
        }
    }
    public Monster putPlayer(Directions direction, Player player){
        throw new UnsupportedOperationException();
        //PRACTICA 3 ---------------------------------------------------
    }
    public void addBlock(Orientation orientation, int startRow, int startCol, 
            int length){
        //PRACTICA 3 ---------------------------------------------
    }
    public ArrayList<Directions> validMoves(int row, int col){
        throw new UnsupportedOperationException();
        //PRACTICA 3 ---------------------------------------------
    }
    
    
    private boolean posOk(int row, int col){
        return (row >= 0 && col >= 0 && row < nRows && col < nCols);
    }
    private boolean emptyPos(int row, int col){
        return LabyrinthSquare[row][col] == EMPTYCHAR;
    }
    private boolean monsterPos(int row, int col){
        return LabyrinthSquare[row][col] == MONSTERCHAR;
    }
    private boolean exitPos(int row, int col){
        return LabyrinthSquare[row][col] == EXITCHAR;
    }
    private boolean combatPos(int row, int col){
        return LabyrinthSquare[row][col] == COMBATCHAR;
    }
    private boolean canStepOn(int row, int col){
        boolean can = emptyPos(row, col) || exitPos(row, col) || monsterPos(row, col);
        return can && posOk(row, col);
    }
    private void updateOldPos(int row, int col){
        if(posOk(row, col)){
            if(combatPos(row, col))
                LabyrinthSquare[row][col] = MONSTERCHAR;
            else
                LabyrinthSquare[row][col] = EMPTYCHAR;
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
        throw new UnsupportedOperationException();
        //PRACTICA 3 ---------------------------------------------------
    }
            
}
