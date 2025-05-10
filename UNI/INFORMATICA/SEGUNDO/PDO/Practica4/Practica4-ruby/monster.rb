module Irrgarten

  class Monster
    @@INITIAL_HEALTH = 5

    def initialize(name, intelligence, strength)
      @name = name
      @intelligence = intelligence
      @strength = strength
      @health = @@INITIAL_HEALTH
      @row = -1
      @col = -1
    end

    def dead
      @health == 0
    end

    def attack
      Dice.intensity(@strength)
    end

    def defend(received_attack)
      if(!dead)
        defensive_energy = Dice.intensity(@intelligence)
        if(received_attack > defensive_energy)
          got_wounded
        end
      end
      dead
    end

    def set_pos(row, col)
      @row = row
      @col = col
    end

    def to_s
      "#{@name}: \n\tInteligencia = #{@intelligence}\n\tFuerza = #{@strength}\n\tVida = #{@health}\n\tPos = (#{@row}, #{@col})"
    end

    private
    
    def got_wounded
      if @health > 0
        @health -= 1
      end
      @health
    end


  end
end
