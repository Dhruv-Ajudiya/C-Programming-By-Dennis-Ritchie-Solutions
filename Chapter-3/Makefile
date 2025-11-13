# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra

# Directories
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj
INCLUDE_DIR := include

# Source files
SRC_FILES := $(filter-out $(SRC_DIR)/error_handling.c, $(wildcard $(SRC_DIR)/*.c))
# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
# Binary files
BIN_FILES = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC_FILES))

# Prevent make from deleting object files
.PRECIOUS: $(OBJ_FILES)

# Default target
all: $(BIN_FILES)

# Rule to build each binary from its corresponding object file
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJ_DIR)/error_handling.o
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

# Rule to compile error_handling.c into an object file
$(OBJ_DIR)/error_handling.o: $(SRC_DIR)/error_handling.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

# Clean up object and binary files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
