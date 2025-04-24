require_relative 'Controller/controller'
require_relative 'UI/textUI'
require_relative 'game'

module Irrgarten

    NUM_JUGADORES = 1

    vista=UI::TextUI.new
    juego=Game.new(NUM_JUGADORES)

    controller=Control::Controller.new(juego,vista)
    controller.play
end