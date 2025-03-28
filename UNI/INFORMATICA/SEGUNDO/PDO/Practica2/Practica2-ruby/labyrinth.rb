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

  end
end