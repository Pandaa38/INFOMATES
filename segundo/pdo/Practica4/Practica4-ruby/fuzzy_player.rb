require_relative 'player'
require_relative 'dice'


module Irrgarten

    class FuzzyPlayer < Player

        def initialize(other_player)
            copy(other_player)
        end

        def move(direction, valid_moves)

            Dice.nextStep(super, valid_moves, intelligence)
        end

        def attack
            return self.sum_weapons + Dice.intensity(@strength)
        end

        def to_s
            return "(Fuzzy) " + super
        end

        protected
        def defensive_energy
            return self.sum_shields + Dice.intensity(@intelligence)
        end

    end 
end 