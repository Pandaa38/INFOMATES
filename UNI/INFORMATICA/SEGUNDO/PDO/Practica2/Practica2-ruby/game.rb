module Irrgarten
  class Game
    #PERSONALIZACION LABERINTO --------------------------------------------------------------------------------
    @@ROWS = 7
    @@COLS = 7

    @@NUM_MONSTERS = 5
    @@INIT_MONSTERS = Array.new(@@NUM_MONSTERS) { Array.new(2) }
    @@INIT_MONSTERS[0] = [0, 0]
    @@INIT_MONSTERS[1] = [1, 1]
    @@INIT_MONSTERS[2] = [2, 2]
    @@INIT_MONSTERS[3] = [3, 3]
    @@INIT_MONSTERS[4] = [0, 3]

    @@NUM_BLOCKS = 4

    #---------------------------------------------------------------------------------------------------------
    @@MAX_ROUNDS = 10

    def initialize(nplayers)
      @log = "Game just started.\n"
    end

    def finished
      @labyrinth.have_a_winner
    end

    def next_step(preferred_direction)
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    def get_game_state
    end

    private:

    def configure_labyrinth
    end

    def next_player
    end

    def actual_direction(preferred_direction)
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    def combat(monster)
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    def manage_reward(winner)
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    def manage_resurrection
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    def log_player_won
      @log += "El jugador ha ganado el combate.\n"
    end
  
    def log_monster_won
      @log += "El monstruo ha ganado el combate.\n"
    end
  
    def log_resurrected
      @log += "El jugador ha resucitado.\n"
    end
  
    def log_player_skip_turn
      @log += "El jugador ha perdido el turno por estar muerto.\n"
    end
  
    def log_player_no_orders
      @log += "El jugador no ha seguido las instrucciones del jugador humano (no fue posible).\n"
    end
  
    def log_no_monster
      @log += "El jugador se ha movido a una celda vacía o no le ha sido posible moverse.\n"
    end
  
    def log_rounds(rounds, max)
      @log += "Se han producido #{rounds} de #{max} rondas de combate.\n"
    end



  end
end