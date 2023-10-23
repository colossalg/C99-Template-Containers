CC = gcc
CFLAGS = --std=c99 -Wall -Werror -pedantic -g

INC_DIR = ./include
BIN_DIR = ./bin

build: ./include/* ./test/*
	mkdir -p ./bin
	$(CC) $(CFLAGS) -I $(INC_DIR) ./test/*.c -o $(BIN_DIR)/tests

.PHONY: test clean

test:
	$(BIN_DIR)/tests

clean:
	rm -rf $(BIN_DIR)