# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Archivos
SRC = tsp.cpp
EXE = tsp

# Regla principal
all: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC)

# Limpiar archivos generados
clean:
	rm -f $(EXE)

