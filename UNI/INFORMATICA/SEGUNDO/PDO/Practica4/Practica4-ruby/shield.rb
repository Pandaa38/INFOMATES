module Irrgarten
  require_relative 'dice'
  class Shield
    #inicalizador con atributos protection y uses
    def initialize(protection, uses)
      @protection = protection
      @uses = uses
    end

    def protect
      if @uses > 0
        @uses -= 1
        protection_sh = @protection
      else
        protection_sh = 0.0
      end
      protection_sh
    end

    def to_s
      "W[#{@protection}, #{@uses}]"
    end

    def discard
      Dice.discard_element(@uses)
    end

  end
end
