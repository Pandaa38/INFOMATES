# Makefile

# Variables del compilador y flags
CXX = g++
CXXFLAGS = -Wall -g

# Targets a generar
all: euclidia_divide euclidia_fuerza

# Enlaza el programa euclidia_divide
euclidia_divide: euclidia_divide.o Punto2D.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Enlaza el programa euclidia_fuerza
euclidia_fuerza: euclidia_fuerza.o Punto2D.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla genérica para compilar archivos .cpp a .o
%.o: %.cpp Punto2D.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza de archivos generados
clean:
	rm -f *.o euclidia_divide euclidia_fuerza

.PHONY: all clean
