# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -I./src
DEBUG_FLAGS = -g

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj

# Source and Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Executable name
EXECUTABLE = main

# Default target
all: $(EXECUTABLE)

# Compile the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Debug target
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean debug

