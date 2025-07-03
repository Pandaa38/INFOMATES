require_relative 'dice'

module Irrgarten

  class CombatElement

    def initialize(effect, uses)
      @effect = effect
      @uses = uses
    end

    def discard
      Dice.discard_element(@uses)
    end

    def to_s
      return "[#{@effect}, #{@uses}]"
    end

    protected
    def produce_effect
      
      if @uses > 0
          @uses -= 1
          return @effect
      else
          return 0.0
      end
    end

  end
end