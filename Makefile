CC = gcc
CFLAGS = --std=c99 -Wall -Werror -pedantic -g

INC_DIR = ./include
GEN_DIR = ./test/templates/containers/generated
BIN_DIR = ./bin

TEST_HEADER_FILES = $(shell find ./test -type f -name "*.h")
TEST_SOURCE_FILES = $(shell find ./test -type f -name "*.c")

TEST_TARGET = $(BIN_DIR)/tests

build: $(LIB_HEADER_FILES) $(TEST_HEADER_FILES) $(TEST_SOURCE_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) $(TEST_SOURCE_FILES) -o $(TEST_TARGET)

.PHONY: generate test clean

generate:
	mkdir -p $(GEN_DIR)
	python3 ./templates/generate_template.py --config_file=./test/templates/template_config.json

test:
	$(TEST_TARGET)

clean:
	rm -rf $(GEN_DIR)
	rm -rf $(BIN_DIR)