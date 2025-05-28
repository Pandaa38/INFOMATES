module Irrgarten
  require_relative 'dice' 

  class Weapon < CombatElement

    def initialize(power, uses)
      super(power, uses)
    end

    def attack
      self.produce_effect
    end

    def to_s
      "W: " + super
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