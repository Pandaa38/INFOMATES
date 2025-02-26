
SRC=./src
INCLUDE=./include
all: raya

juego.o: $(SRC)/juego.cpp $(INCLUDE)/juego.h $(INCLUDE)/tablero.h $(INCLUDE)/jugador.h
	g++ -Wall -c $(SRC)/juego.cpp

tablero.o: $(SRC)/tablero.cpp $(INCLUDE)/tablero.h $(INCLUDE)/ficha.h
	g++ -Wall -c $(SRC)/tablero.cpp

ficha.o: $(SRC)/ficha.cpp $(INCLUDE)/ficha.h
	g++ -Wall -c $(SRC)/ficha.cpp
	
conexion.o: $(SRC)/conexion.cpp $(INCLUDE)/conexion.h
	g++ -Wall -c $(SRC)/conexion.cpp
	
jugador.o: $(SRC)/jugador.cpp $(INCLUDE)/jugador.h $(INCLUDE)/ficha.h
	g++ -Wall -c $(SRC)/jugador.cpp

main.o: $(SRC)/main.cpp $(INCLUDE)/tablero.h $(INCLUDE)/ficha.h $(INCLUDE)/jugador.h $(INCLUDE)/juego.h $(INCLUDE)/conexion.h 
	g++ -Wall -c $(SRC)/main.cpp

raya: main.o jugador.o ficha.o tablero.o juego.o conexion.o
	g++ -o raya main.o jugador.o ficha.o tablero.o juego.o conexion.o

raya3.ps: main.cpp jugador.cpp ficha.cpp tablero.cpp juego.cpp conexion.cpp\
         jugador.h ficha.h tablero.h juego.h conexion.h Makefile
	a2ps -A fill ficha.h ficha.cpp tablero.h tablero.cpp jugador.h \
                     jugador.cpp juego.h juego.cpp conexion.h conexion.cpp main.cpp \
                     Makefile -o Documentacion/raya3.ps

clean :
	-rm main.o ficha.o jugador.o tablero.o juego.o conexion.o

mrproper : clean
	-rm raya Documentacion/raya3.ps
