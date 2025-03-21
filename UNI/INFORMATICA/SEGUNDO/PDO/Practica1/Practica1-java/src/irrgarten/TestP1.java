
package irrgarten;

/**
 *
 * @author juan
 */
public class TestP1 {
    public static void main(String[] args) {
        // ---------- Prueba de Weapon ----------
        System.out.println("=== Probando Weapon ===");
        Weapon weapon = new Weapon(2.0f, 5);
        System.out.println("Estado inicial del arma: " + weapon.toString());
        System.out.println("Ataque: " + weapon.attack());
        System.out.println("Estado tras el ataque: " + weapon.toString());
        System.out.println("Decisión de descarte: " + weapon.discard());
        System.out.println();

        // ---------- Prueba de GameState ----------
        System.out.println("=== Probando GameState ===");
        GameState gameState = new GameState("Labyrinth1", "Players1",
                                    "Monsters1", 0, false, "Inicio del juego");
        
        System.out.println(gameState.getLabyrinth());
        System.out.println(gameState.getPlayers());
        System.out.println(gameState.getMonsters());
        System.out.println(gameState.getCurrentPlayer());
        System.out.println(gameState.isWinner());
        System.out.println(gameState.getLog());
        System.out.println();

        // ---------- Prueba de Enumerados ----------
        System.out.println("=== Enumerados ===");
        System.out.println("Directions:");
        for (Directions d : Directions.values()) {
            System.out.println(d);
        }
        System.out.println("Orientation:");
        for (Orientation o : Orientation.values()) {
            System.out.println(o);
        }
        System.out.println("GameCharacter:");
        for (GameCharacter gc : GameCharacter.values()) {
            System.out.println(gc);
        }
        System.out.println();
        
        // ---------- Pruebas de Dice ----------
        System.out.println("=== Probando Dice ===");
        int iterations = 100;
        
        // Probando resurrectPlayer (se espera alrededor del 30% de true)
        int resurrectTrueCount = 0;
        for (int i = 0; i < iterations; i++) {
            if (Dice.resurrectPlayer()) {
                resurrectTrueCount++;
            }
        }
        System.out.println("resurrectPlayer true en " + resurrectTrueCount + " de " + iterations + " iteraciones.");
        
        // Probando discardElement para usesLeft = MAX_USES (5) y para usesLeft = 0
        int discardMaxCount = 0; // Para usesLeft = 5, se espera false (0 veces true)
        int discardZeroCount = 0; // Para usesLeft = 0, se espera true (100 veces true)
        for (int i = 0; i < iterations; i++) {
            if (Dice.discardElement(5)) {
                discardMaxCount++;
            }
            if (Dice.discardElement(0)) {
                discardZeroCount++;
            }
        }
        System.out.println("discardElement(5): " + discardMaxCount + " true de " + iterations + " iteraciones (se espera 0).");
        System.out.println("discardElement(0): " + discardZeroCount + " true de " + iterations + " iteraciones (se espera 100).");
        
        // Probando rewards: weaponsReward, shieldsReward, healthReward        
        for (int i = 0; i < 5; i++) {
            System.out.println("Distribución de weaponsReward:" + i + ": " + Dice.weaponsReward());
        }
        for (int i = 0; i < 5; i++) {
            System.out.println("Distribución de healthReward:" + i + ": " + Dice.healthReward());
        }
        for (int i = 0; i < 5; i++) {
            System.out.println("Distribución de shieldsReward:" + i + ": " + Dice.shieldsReward());            
        }
        
        float sumWeaponPower = 0.0f;
        float sumShieldPower = 0.0f;
        float sumIntelligence = 0.0f;
        float sumStrength = 0.0f;
        
        for (int i = 0; i < iterations; i++) {
            sumWeaponPower += Dice.weaponPower();
            sumShieldPower += Dice.shieldPower();
            sumIntelligence += Dice.randomIntelligence();
            sumStrength += Dice.randomStrength();
        }
        System.out.println("Promedio de weaponPower: " + 
                (sumWeaponPower / iterations));
        System.out.println("Promedio de shieldPower: " + 
                (sumShieldPower / iterations));
        System.out.println("Promedio de randomIntelligence: " + 
                (sumIntelligence / iterations));
        System.out.println("Promedio de randomStrength: " + 
                (sumStrength / iterations));
        
        // Probando randomPos para un tablero de 10 (índices 0 a 9)
        int[] posDistribution = new int[10];
        for (int i = 0; i < iterations; i++) {
            int pos = Dice.randomPos(10);
            posDistribution[pos]++;
        }
        System.out.println("Distribución de randomPos (0 a 9):");
        for (int i = 0; i < posDistribution.length; i++) {
            System.out.println("Posición " + i + ": " + posDistribution[i]);
        }
        
        // Probando whoStarts para 4 jugadores
        int[] whoStartsDist = new int[4];
        for (int i = 0; i < iterations; i++) {
            int starter = Dice.whoStarts(4);
            whoStartsDist[starter]++;
        }
        System.out.println("Distribución de whoStarts (para 4 jugadores):");
        for (int i = 0; i < whoStartsDist.length; i++) {
            System.out.println("Jugador " + i + ": " + whoStartsDist[i]);
        }        
        
        
    }//Clase main
}//Clase TestP1
