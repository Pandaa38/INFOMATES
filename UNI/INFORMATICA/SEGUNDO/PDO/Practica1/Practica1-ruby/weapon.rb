module Irrgarten
  require_relative 'dice' #da error preguntar al profe

  class Weapon
    #inicializador recibe power y uses
    def initialize(power, uses)
      @power = power
      @uses = uses
    end

    def attack
      if @uses > 0
        @uses -= 1
        attack_w = @power
      else
        attack_w = 0.0
      end
      attack_w
    end

    def to_s
      "W[#{@power}, #{@uses}]"
    end

    def discard
      Dice.discardElement(@uses)
    end


  end
=begin
  weapon = Weapon.new(2.0, 3)
  puts "\nestado arma #{weapon.to_s} \n"
  puts weapon.attack
  puts "estado arma #{weapon.to_s}"
  puts "Se ha eliminado arma? #{weapon.discard}"
=end
end