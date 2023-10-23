CC = gcc
CFLAGS = --std=c99 -Wall -Werror -pedantic -g

INC_DIR = ./include
BIN_DIR = ./bin

LIB_HEADER_FILES = $(shell find ./include -type f -name "*.h")

TEST_HEADER_FILES = $(shell find ./test -type f -name "*.h")
TEST_SOURCE_FILES = $(shell find ./test -type f -name "*.c")

TEST_TARGET = $(BIN_DIR)/tests

build: $(LIB_HEADER_FILES) $(TEST_HEADER_FILES) $(TEST_SOURCE_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) $(TEST_SOURCE_FILES) -o $(TEST_TARGET)

.PHONY: test clean

test:
	$(TEST_TARGET)

clean:
	rm -rf $(BIN_DIR)