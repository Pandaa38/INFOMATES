module Irrgarten
  class Player
    class Player
      @@MAX_WEAPONS = 2
      @@MAX_SHIELDS = 3
      @@INITIAL_HEALTH = 10
      @@HITS2LOSE = 3
    
      attr_reader :row, :col, :number
    
      def initialize(number, intelligence, strength)
        @name = "Player##{number}"
        @number = number
        @intelligence = intelligence
        @strength = strength
        @health = @@INITIAL_HEALTH
        @consecutive_hits = 0
    
        @weapons = Array.new   
        @shields = Array.new
      end

      def resurrect
        @weapons.clear
        @shields.clear
    
        @health = @@initial_health
        reset_hits
      end
    
      def get_row
        @row
      end
    
      def get_col
        @col
      end
    
      def get_number
        @number
      end
    
      def set_pos(row, col)
        @row = row
        @col = col
      end
    
      def dead?
        @health == 0
      end
    
      def move(direction, valid_moves)
        raise NotImplementedError, "El método move no está implementado."
        # PRACTICA 3 **************************************
      end
    
      def attack
        sum_weapons + @strength
      end
    
      def defend(received_attack)
        manage_hit(received_attack)
      end
    
      def receive_reward
        # PRACTICA 3 **************************************
      end
    
      def to_s
        "#{@name}: \n\tInteligencia = #{@intelligence}\n\tFuerza = #{@strength}\n\tVida = #{@health}\n\tPos = (#{@row}, #{ @col})"
      end
    
      private
    
      def receive_weapon(w)
        # PRACTICA 3 **************************************
      end
    
      def receive_shield(s)
        # PRACTICA 3 **************************************
      end
    
      def new_weapon
        w = Weapon.new(Dice.weaponPower, Dice.usesLeft)
        w
      end
    
      def new_shield
        s = Shield.new(Dice.shieldPower, Dice.usesLeft)
        s
      end
    
      def sum_weapons
        sum = 0.0
        @weapons.each do |w|
          sum += w.attack
        end
        sum
      end
    
      def sum_shields
        sum = 0.0
        @shields.each do |s|
          sum += s.protect
        end
        sum
      end
    
      def defensive_energy
        sum_shields + @intelligence
      end
    
      def manage_hit(received_attack)
        raise NotImplementedError, "El método manage_hit no está implementado."
        # PRACTICA 3 **************************************
      end
    
      def reset_hits
        @consecutive_hits = 0
      end
    
      def got_wounded
        @health -= 1
      end
    
      def inc_cosecutive_hits
        @consecutive_hits += 1
      end

  end
end