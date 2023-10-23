CC = gcc
CFLAGS = --std=c99 -Wall -Werror -pedantic -g

build: ./include/* ./test/*
	mkdir -p ./bin
	$(CC) $(CFLAGS) ./test/*.c -o ./bin/tests

.PHONY: test clean

test:
	./bin/tests

clean:
	rm -rf ./bin