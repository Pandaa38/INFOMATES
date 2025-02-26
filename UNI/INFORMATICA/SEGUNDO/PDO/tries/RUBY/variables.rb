class Clase
  @@variable = "De clase "
  @variable = "De i n s t a n c i a de l a clase "
  
  def initialize
    @variable = "De i n s t a n c i a "
  end
  
  def muestraValores
    puts @@variable
    puts @variable
  end

  def self.muestraValores
    puts @@variable
    puts @variable
  end
end

objeto = Clase.new
objeto.muestraValores
Clase.muestraValores
