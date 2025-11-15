# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Directories
SRCDIR   := src
BINDIR   := bin

# Target name
TARGET   := $(BINDIR)/simple-jwt-clone

# Source files
SOURCES  := main.cpp $(SRCDIR)/*.cpp

# Default rule
all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Clean generated files
clean:
	rm -f $(TARGET)

# Tests
TEST_DIR = tests
TEST_BIN = bin/tests

test: $(TEST_BIN)

$(TEST_BIN): $(TEST_DIR)/*.cpp src/*.cpp
	mkdir -p bin
	g++ -std=c++17 -Wall -Wextra -O2 \
		$(TEST_DIR)/*.cpp src/*.cpp \
		-o $(TEST_BIN)

clean-tests:
	rm -f $(TEST_BIN)