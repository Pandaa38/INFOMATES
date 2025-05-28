module Irrgarten

  class Monster < LabyrinthCharacter
    @@INITIAL_HEALTH = 5

    def initialize(name, intelligence, strength)
      super(name, intelligence, strength, @@INITIAL_HEALTH)
    end

    def dead
      @health == 0
    end

    def attack
      Dice.intensity(@strength)
    end

    def defend(received_attack)
      if(!self.dead)
        defensive_energy = Dice.intensity(@intelligence)
        if(received_attack > defensive_energy)
          got_wounded
        end
      end
      dead
    end

  end
end
