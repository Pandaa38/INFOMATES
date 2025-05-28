module Irrgarten
  class LabyrinthCaracter
    @@INVALID_POS = -1

    attr_reader :row, :col

    def initialize(name, intelligence, strength, health)
      @name = name
      @intelligence = intelligence
      @strength = strength
      @health = health
      set_pos(@@INVALID_POS, @@INVALID_POS)
    end

    def copy(other)
      @name = other.name
      @intelligence = other.intelligence
      @strength = other.strength
      @health = other.health
      pos(other.row, other.col)
  end

    def dead
      @health <= 0
    end

    def set_pos(row, col)
      @row = row
      @col = col
    end

    def to_s
      formato='%.6f'

      return "#{@name}[i:#{format(formato,@intelligence)}, s:#{format(formato,@strength)}, "+
      "h:#{format(formato,@health)}, p:(#{@row}, #{@col})]"
    end

    def attack
    end
    def defend(attack)
    end

    protected

    attr_reader :intelligence, :strength
    attr_accessor :health

    def got_wounded
      @health -= 1
    end


end
