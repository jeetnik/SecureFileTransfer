# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Source files
SOURCES = Node.cpp HuffmanCoding.cpp Encryption.cpp FileOps.cpp Application.cpp main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
TARGET = huffman_app

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcrypto

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean

# Dependencies
Node.o: Node.cpp Node.h
HuffmanCoding.o: HuffmanCoding.cpp HuffmanCoding.h Node.h
Encryption.o: Encryption.cpp Encryption.h
FileOps.o: FileOps.cpp FileOps.h
Application.o: Application.cpp Application.h HuffmanCoding.h Encryption.h FileOps.h
main.o: main.cpp Application.h
