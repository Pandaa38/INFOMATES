module Irrgarten
  require_relative 'weapon'
  require_relative 'shield'
  require_relative 'dice'
  require_relative 'gamestate'
  require_relative 'gamecharacter'
  require_relative 'directions'
  require_relative 'orientation'

  class TestP1

    def self.main 
      puts "CLASE WEAPON:"
      weapon = Weapon.new(2.0, 5)
      puts weapon.to_s
      puts weapon.attack
      puts weapon.to_s


      puts "\nCLASE GAME_STATE"
      game = Game_state.new("laberinto", "jugador", "mounstro", 3, true, "log")
      puts game.labyrinth
      puts game.players
      puts game.monsters
      puts game.current_player
      puts game.winner
      puts game.log


      puts "\nCLASE DICE"
      puts "Jugador que empieza: #{Dice.who_starts(4)}"
      puts "Inteligencia: #{Dice.random_intelligence}"
      puts "Fuerza: #{Dice.random_strength}"
      puts "Resucitar? #{Dice.resurrect_player}"
      puts "Recompensa armas: #{Dice.weapon_reward}"
      puts "Recompensa escudos: #{Dice.shields_reward}"
      puts "Recompensa salud: #{Dice.health_reward}"
      puts "Potencia arma: #{Dice.weapon_power}"
      puts "Potencia escudo: #{Dice.shield_power}"
      puts "descarte?: #{Dice.discard_element(3)}"


    end

  end

  TestP1.main
end