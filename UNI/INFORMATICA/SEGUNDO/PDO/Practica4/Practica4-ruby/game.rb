require_relative 'dice'
require_relative 'player'
require_relative 'monster'
require_relative 'labyrinth'
require_relative 'game_state'
require_relative 'game_character'
require_relative 'orientation'

module Irrgarten
  
  class Game
    # ---------------------- PERSONALIZACIÓN LABERINTO ----------------
    # Número de filas del laberinto.
    @@ROWS = 7

    # Número de columnas del laberinto.
    @@COLS = 7

    # Posiciones iniciales de los monstruos en el laberinto.
    @@MONSTER_INIT = [
      ["Monster1", 0, 0],
      ["Monster2", 1, 1],
      ["Monster3", 2, 2],
      ["Monster4", 3, 3],
      ["Monster5", 0, 3]
    ]

    # Bloques iniciales a incluir en el laberinto donde el último parámetro indica la longitud.
    @@BLOCKS = [
      [Orientation::HORIZONTAL, 1, 4, 3],
      [Orientation::VERTICAL,   2, 6, 3],
      [Orientation::HORIZONTAL, 4, 1, 4],
      [Orientation::VERTICAL,   5, 3, 2]
    ]
    # ---------------------------------------------------------------

    @@MAX_ROUNDS = 10

    def initialize(n_players)

      @players = Array.new
      @monsters = Array.new

      n_players.times do |i|
          @players.push(Player.new(i.to_s, Dice.random_intelligence, Dice.random_strength))
      end

      @current_player_index = Dice.who_starts(n_players)
      @current_player = @players[@current_player_index]

      @labyrinth = Labyrinth.new(@@ROWS, @@COLS, 6, 6)
      self.configure_labyrinth
      @labyrinth.spread_players(@players)

      @log = "- Game just started.\n"

    end

    def finished
      @labyrinth.have_a_winner
    end

    def next_step(preferred_direction)
      @log = ""

      if(!@current_player.dead)
          direction = self.actual_direction(preferred_direction)

          if(direction != preferred_direction)
              self.log_player_no_orders
          end

          monster = @labyrinth.put_player(direction, @current_player)
          if(monster == nil)
              self.log_no_monster
          else
              winner = self.combat(monster)
              self.manage_reward(winner)
          end
      else
          self.manage_resurrection
      end

      end_game = self.finished()
      if(!end_game)
          self.next_player
      end

      end_game
    end

    def game_state
      info_players = ""
      
      @players.each do |player|
        info_players += player.to_s + "\n"
      end

      info_monsters = ""
      @monsters.each do |monster|
        info_monsters += monster.to_s + "\n"
      end

      return GameState.new(@labyrinth.to_s, info_players, info_monsters, @current_player_index, self.finished, @log)
      
    end

    private

    def configure_labyrinth

      # BLOQUES
      @@BLOCKS.each do |block|
        orientation, row, col, length = block
        @labyrinth.add_block(orientation, row, col, length)
      end

      # MONSTRUOS
      @@MONSTER_INIT.each do |monster_info|
        name, row, col = monster_info

        monster = Monster.new(name, Dice.random_intelligence, Dice.random_strength)

        @monsters.push(monster)
        @labyrinth.add_monster(row, col, monster)
      end

    end

    def next_player
      @current_player_index = (@current_player_index + 1) % @players.size
      @current_player = @players[@current_player_index]
    end

    def actual_direction(preferred_direction)
      current_row = @current_player.row
      current_col = @current_player.col

      valid_moves = @labyrinth.valid_moves(current_row, current_col)

      out = @current_player.move(preferred_direction, valid_moves)
      return out
    end

    def combat(monster)
      rounds = 0
      winner = GameCharacter::PLAYER

      lose = monster.defend(@current_player.attack)

      while ( (!lose) && (rounds<@@MAX_ROUNDS) )
          winner = GameCharacter::MONSTER
          rounds += 1

          # Turno del monstruo de atacar al jugador
          lose = @current_player.defend(monster.attack())
          if(!lose)
              winner = GameCharacter::PLAYER
              lose = monster.defend(@current_player.attack())
          end
      end

      self.log_rounds(rounds, @@MAX_ROUNDS)

      winner
    end

    def manage_reward(winner)
      if(winner == GameCharacter::PLAYER)
        @current_player.receive_reward
        log_player_won
      else
        log_monster_won
      end
    end

    def manage_resurrection
      if(Dice.resurrect_player)
        @current_player.resurrect
        log_resurrected
      else
        log_player_skip_turn
      end
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