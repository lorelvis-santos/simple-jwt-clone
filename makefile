# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Directories
SRCDIR   := src
BINDIR   := bin

# Target name
TARGET   := $(BINDIR)/simple-jwt-clone

# Source files
SOURCES  := main.cpp $(SRCDIR)/base64.cpp

# Default rule
all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Clean generated files
clean:
	rm -f $(TARGET)