# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -O2

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET = SpaceInvader

# Source file
SRC = main.cpp

# Default build
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

.PHONY: all run clean
