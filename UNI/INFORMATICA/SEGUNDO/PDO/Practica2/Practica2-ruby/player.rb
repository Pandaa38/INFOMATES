module Irrgarten

  require_relative 'dice'
  require_relative 'weapon'
  require_relative 'shield'

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

        @row = -1
        @col = -1
      end

      def resurrect
        @weapons.clear
        @shields.clear
    
        @health = @@INITIAL_HEALTH
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
    
      def dead
        @health == 0
      end
    
      def move(direction, valid_moves)
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
        weapons_str = ""
        @weapons.each do |weapon|
          weapons_str += weapon.to_s + ", "
        end
        weapons_str.chomp(", ")
    
        shields_str = ""
        @shields.each do |shield|
          shields_str += shield.to_s + ", "
        end
        shields_str.chomp(", ")
    
        "#{@name}: \n\tInteligencia = #{@intelligence}\n\tFuerza = #{@strength}\n\tVida = #{@health}\n\tPos = (#{@row}, #{ @col})\n\tArmas = [#{weapons_str}]\n\tEscudos = [#{shields_str}]"
      end
    
      #private
    
      def receive_weapon(w)
        # PRACTICA 3 **************************************
      end
    
      def receive_shield(s)
        # PRACTICA 3 **************************************
      end
    
      def new_weapon
        w = Weapon.new(Dice.weapon_power, Dice.uses_left)
        w
      end
    
      def new_shield
        s = Shield.new(Dice.shield_power, Dice.uses_left)
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


=begin
  puts "Prueba de la clase Player"

  # Crear una instancia de Player
  player = Player.new('A', 10, 7)
  puts "\nEstado inicial del Player:"
  puts player.to_s

  # Probar el método set_pos
  player.set_pos(3, 5)
  puts "\nDespués de ejecutar set_pos(3, 5):"
  puts player.to_s

  # Simular daño usando el método take_damage
  player.got_wounded
  player.got_wounded
  puts "\nDespués de simular daño (reduciendo 2 puntos de vida):"
  puts "¿Está muerto? #{player.dead}"
  puts player.to_s

  # Probar resurrect para restaurar la salud y vaciar armas/escudos
  player.resurrect
  puts "\nDespués de ejecutar resurrect:"
  puts player.to_s

  # Probar el método new_weapon
  puts "\nCreando un arma con new_weapon:"
  puts player.new_weapon.to_s
=end
end