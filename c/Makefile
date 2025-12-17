CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./src/include
SRC = src/main.c src/hardwareInterfaces.c src/temperatureMonitor.c
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
BIN = bin/app

all: clean $(BIN)

$(BIN): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@
	
run: clean all
	./bin/app

debug: CFLAGS += -g
debug: clean all

clean:
	rm -rf build bin