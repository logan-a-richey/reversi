# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -I.

# File structure
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
BIN := $(BIN_DIR)/reversi.exe

# Find all .cpp files recursively
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target
all: $(BIN)

# Link all object files into the final executable
$(BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $@

# Compile source files to object files (mirrored path)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
