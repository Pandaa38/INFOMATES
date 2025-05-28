require_relative 'dice'

module Irrgarten  
  class Shield < CombatElement
    
    def initialize(protection, uses)
      super(protection, uses)
    end

    def protect
      self.produce_effect
    end

    def to_s
      "S" + super
    end
    
  end
end
