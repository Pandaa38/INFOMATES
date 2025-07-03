module Irrgarten
  class Labyrinth

    @@BLOCK_CHAR = 'X'
    @@EMPTY_CHAR = '-'
    @@MONSTER_CHAR = 'M'
    @@COMBAT_CHAR = 'C'
    @@EXIT_CHAR = 'E'
    @@ROW = 0
    @@COL = 1

    def initialize(n_rows, n_cols, exit_row, exit_col)
      @n_rows = n_rows
      @n_cols = n_cols
      @exit_row = exit_row
      @exit_col = exit_col

      @monster_square = Array.new(@n_rows) { Array.new(@n_cols) }
      @player_square = Array.new(@n_rows) { Array.new(@n_cols) }
      @labyrinth_square = Array.new(@n_rows) { Array.new(@n_cols, EMPTY_CHAR) }
    end

    def spread_player
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    def have_a_winner
      @player_square[@exit_row][@exit_col] != nil
    end

    def to_s
      "laberinto"
    end

    def add_monster(row, col, monster)
      if(pos_ok(row, col) && empty_pos(row, col))
        @monster_square[row][col] = monster
        @labyrinth_square[row][col] = @@MONSTER_CHAR
      end
    end

    def put_player(direction, player)
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    def add_block(orientation, start_row, start_col, length)
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    def valid_moves(row, col)
      #PRACTICA 3 --------------------------------------------------------------------------------
    end

    private:

    def pos_ok(row, col)
      row >= 0 && row < @n_rows && col >= 0 && col < @n_cols
    end

    def empty_pos(row, col)
      @labyrinth_square[row][col] == @@EMPTY_CHAR
    end 

    def monster_pos(row, col)
      @labyrinth_square[row][col] == @@MONSTER_CHAR
    end 

    def exit_pos(row,col)
      @labyrinth_square[row][col] == @@EXIT_CHAR
    end

    def combat_pos(row, col)
      @labyrinth_square[row][col] == @@COMBAT_CHAR
    end

    def can_step_on(row, col)
      pos_ok(row, col) && (empty_pos(row, col) || exit_pos(row, col) || monster_pos(row, col))
    end

    def update_old_pos(row, col)
      if(pos_ok(row, col))
        if(combat_pos(row, col))
          @labyrinth_square[row][col] = @@MONSTER_CHAR
        else
          @labyrinth_square[row][col] = @@EMPTY_CHAR
        end
      end
    end

    def dir_2_pos(row, col, direction)
      pos = Array.new(2)
      pos[@@ROW] = row
      pos[@@COL] = col

      case direction
      when :up
        pos[@@ROW] -= 1
      when :down
        pos[@@ROW] += 1
      when :left
        pos[@@COL] -= 1
      when :right
        pos[@@COL] += 1
      end

      pos
    end

    def random_empty_pos
      pos = Array.new(2)

      begin
        pos[@@ROW] = Dice.random_pos(@n_rows)
        pos[@@COL] = Dice.random_pos(@n_cols)
      end while(!empty_pos(pos[@@ROW], pos[@@COL]))
      
      pos
    end

    def put_player_2D(old_row, old_col, row, col, player)
      #PRACTICA 3 --------------------------------------------------------------------------------
    end








  end
end