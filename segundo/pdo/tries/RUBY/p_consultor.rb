class UnaClase
	attr_reader :atr1
	attr_accessor :atr2
	attr_writer :atr3


	def initialize(un, dos, tres )
		@atr1 = un
		@atr2 = dos
		@atr3 = tres
	end
end
obj = UnaClase.new(1, 2, 3)
obj.atr2 = 8
puts obj.inspect
obj.atr2 = 9
puts obj.inspect
obj.atr3 = 7
puts obj.inspect
puts obj.atr1
puts obj.atr2
