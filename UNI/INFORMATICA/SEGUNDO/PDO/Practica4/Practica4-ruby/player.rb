require_relative 'dice'
require_relative 'weapon'
require_relative 'shield'
require_relative 'labyrinth_character'


module Irrgarten

  class Player < LabyrinthCaracter
    @@MAX_WEAPONS = 2
    @@MAX_SHIELDS = 3
    @@INITIAL_HEALTH = 10
    @@HITS2LOSE = 3
  
    attr_reader :number
  
    def initialize(number, intelligence, strength)
      @number = number.to_s
      name = "Player #{@number}"
      super(name, intelligence, strength, @@INITIAL_HEALTH)

      @weapons = Array.new
      @shields = Array.new

      @consecutive_hits = 0
    end
    def copy(other)
      super
      @number = other.number
      @weapons = other.weapons
      @shields = other.shields
      @consecutive_hits = other.consecutive_hits
    end

    def resurrect
      @weapons.clear
      @shields.clear
  
      @health = @@INITIAL_HEALTH
      reset_hits()
    end
  
    def get_number
      @number
    end
    
    def move(direction, valid_moves)
      size = valid_moves.size
      contained = valid_moves.include?(direction)
      if(size > 0 && !contained)
        return valid_moves[0]
      else
        return direction
      end
    end
  
    def attack
      sum_weapons + @strength
    end
  
    def defend(received_attack)
      manage_hit(received_attack)
    end
  
    def receive_reward

      w_reward = Dice.weapon_reward
      w_reward.times do
        receive_weapon(new_weapon)
      end
      
      s_reward = Dice.shields_reward
      s_reward.times do
        receive_shield(new_shield)
      end

      @health += Dice.health_reward

    end
  
    #######################################################################################
    def to_s
      # Guardamos la info de todas las armas en un string
      to_weapons="["
      tam_weapons=@weapons.size
      # Se incluye 0 y tam_weapons-1
      for i in 0..(tam_weapons-1) do
          to_weapons+=@weapons[i].to_s

          # NO hace la parte de delante si i == (tam_weapons-1)
          to_weapons += ", " unless i == (tam_weapons - 1)
      end
      to_weapons+="]"

      # Guardamos la info de todas las armas en un string
      to_shields="["
      tam_shields=@shields.size
      # Se incluye 0 y tam_shields-1
      for i in 0..(tam_shields-1) do
          to_shields+=@shields[i].to_s

          # NO hace la parte de delante si i == (tam_weapons-1)
          to_shields += ", " unless i == (tam_shields - 1)
      end
      to_shields+="]"

      return super + " [ ch:#{@consecutive_hits}, w:"+to_weapons+", sh:"+to_shields + " ]"
    end
  
    private
  
    def receive_weapon(w)
      @weapons.each do |weapon|
        discard = weapon.discard
        if(discard)
          @weapons.delete(weapon)
        end
      end

      if(@weapons.size < @@MAX_WEAPONS)
        @weapons.push(w)
      end
    end
  
    def receive_shield(s)
      @shields.each do |shield|
        discard = shield.discard
        if(discard)
          @shields.delete(shield)
        end
      end
      if(@shields.size < @@MAX_SHIELDS)
        @shields.push(s)
      end
    end
  
    def new_weapon
      w = Weapon.new(Dice.weapon_power, Dice.uses_left)
      w
    end
  
    def new_shield
      s = Shield.new(Dice.shield_power, Dice.uses_left)
      s
    end
  
    protected
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
    
    private
    def manage_hit(received_attack)

      if(defensive_energy() < received_attack)
          self.got_wounded
          self.inc_consecutive_hits
      else
          self.reset_hits
      end

      if ( (@consecutive_hits==@@HITS2LOSE) || self.dead )
          self.reset_hits
          lose=true
      else
          lose=false
      end
      lose
    end
  
    def reset_hits
      @consecutive_hits = 0
    end
  
    def inc_consecutive_hits
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
