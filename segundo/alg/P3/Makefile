# Makefile for compiling pixelMountain.cpp

# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Target executable name
TARGET   := pixelMountain

# Source and object files
SRCS     := pixelMountain.cpp
OBJS     := $(SRCS:.cpp=.o)

.PHONY: all clean

# Default target
all: $(TARGET)

# Link objects into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove generated files
clean:
	rm -f $(OBJS) $(TARGET)
