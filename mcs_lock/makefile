CC = gcc
CFLAGS = -Wall -Wextra -pthread -I./include
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Ensure the bin and obj directories exist
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

# Object files
OBJS = $(OBJ_DIR)/mcs_lock.o $(OBJ_DIR)/test_mcs.o

all: test_mcs

test_mcs: $(OBJS)
				$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/test_mcs