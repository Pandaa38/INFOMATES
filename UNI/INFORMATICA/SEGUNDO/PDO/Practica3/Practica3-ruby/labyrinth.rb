require_relative 'dice'
require_relative 'directions'
require_relative 'orientation'

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

      @monsters = Array.new(@n_rows) { Array.new(@n_cols) }
      @players = Array.new(@n_rows) { Array.new(@n_cols) }
      @labyrinth = Array.new(@n_rows) {Array.new(@n_cols, @@EMPTY_CHAR)}

      @labyrinth[@exit_row][@exit_col] = @@EXIT_CHAR
    end

    def spread_players(players)
      players.each do |p|
        pos = self.random_empty_pos
        put_player2D(-1, -1, pos[@@ROW], pos[@@COL], p)
      end
    end

    def have_a_winner
      return @players[@exit_row][@exit_col] != nil
    end

    def to_s
      ancho_maximo = @labyrinth.flatten.max.to_s.size
      str = "".rjust(ancho_maximo+2)
      @n_cols.times do |i|
          str+=i.to_s.rjust(ancho_maximo+2)
      end
      str+="\n"
      num_row=0

      @labyrinth.each do |row|
          str+=num_row.to_s.rjust(ancho_maximo+2)
          num_row+=1
          row.each do |cell|
              str += cell.to_s.rjust(ancho_maximo+2)
          end
          str += "\n"
      end
      return str
    end

    def add_monster(row, col, monster)
      if(pos_ok(row, col) && empty_pos(row, col))
        @monsters[row][col] = monster
        @labyrinth[row][col] = @@MONSTER_CHAR
      end
    end

    def put_player(direction, player)
      old_row = player.row
      old_col = player.col

      new_pos = dir_2_pos(old_row, old_col, direction)

      monster = put_player2D(old_row, old_col, new_pos[@@ROW], new_pos[@@COL], player)
    end

    def add_block(orientation, start_row, start_col, length)
      if(orientation==Orientation::VERTICAL)
          inc_row = 1
          inc_col = 0
      else
          inc_row = 0
          inc_col = 1
      end

      row = start_row
      col = start_col

      while ( pos_ok(row,col) && empty_pos(row,col) && (length>0) )
          @labyrinth[row][col] = @@BLOCK_CHAR
          length-=1
          row+=inc_row
          col+=inc_col
      end
    end

    def valid_moves(row, col)
      output=Array.new

      if(self.can_step_on(row+1, col))
          output.push(Directions::DOWN)
      end
      if(self.can_step_on(row-1, col))
          output.push(Directions::UP)
      end
      if(self.can_step_on(row, col+1))
          output.push(Directions::RIGHT)
      end
      if(self.can_step_on(row, col-1))
          output.push(Directions::LEFT)
      end

      output
    end

    private

    def pos_ok(row, col)
      row >= 0 && row < @n_rows && col >= 0 && col < @n_cols
    end

    def empty_pos(row, col)
      @labyrinth[row][col] == @@EMPTY_CHAR
    end 

    def monster_pos(row, col)
      @labyrinth[row][col] == @@MONSTER_CHAR
    end 

    def exit_pos(row,col)
      @labyrinth[row][col] == @@EXIT_CHAR
    end

    def combat_pos(row, col)
      @labyrinth[row][col] == @@COMBAT_CHAR
    end

    def can_step_on(row, col)
      pos_ok(row, col) && (empty_pos(row, col) || exit_pos(row, col) || monster_pos(row, col))
    end

    def update_old_pos(row, col)
      if(pos_ok(row, col))
        if(combat_pos(row, col))
          @labyrinth[row][col] = @@MONSTER_CHAR
        else
          @labyrinth[row][col] = @@EMPTY_CHAR
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

    def put_player2D(old_row, old_col, row, col, player)
      output = nil

      if(can_step_on(row, col))

          if(pos_ok(old_row, old_col))

              if(@players[old_row][old_col]==player)
                  update_old_pos(old_row, old_col)
                  @players[old_row][old_col] = nil
              end
          end

          if(monster_pos(row,col))
 
              @labyrinth[row][col] = @@COMBAT_CHAR
              output = @monsters[row][col]
          else
              @labyrinth[row][col] = player.number
          end

          @players[row][col] = player
          player.set_pos(row,col)
      end

      output
    end

  end
end