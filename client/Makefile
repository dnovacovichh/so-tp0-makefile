# Globales
CC = gcc
OUTFILE = client.out


# SRC -> find ./src -type f -iname "*.c" -exec basename {} \; (Da una lista de *.c)
SRC = $(shell find ./src -type f -iname "*.c" -exec basename {} \;)
OBJ = $(SRC:%.c=./obj/%.o) #De la variable SRC agarra todo lo que sea *.c  y lo pone en la carpeta obj/*.o

LINK = -lpthread -lcommons -lm -lreadline

build: makefolder $(OBJ)
	$(CC) -o $(OUTFILE) client.c $(OBJ) $(LINK)


CFLAGS = -c

debug: CFLAGS := $(CFLAGS) -g
debug: build

./obj/%.o: ./src/%.c # REGLA
	$(CC) $(CFLAGS) -c $< -o $@ $(LINK)

makefolder:  # Crea carpeta obj
	if [ ! -d ./obj ]; then mkdir obj; fi


valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.log ./$(OUTFILE)


# Clean

clean:
	rm -rf obj
	rm -rf *.out
	rm -rf *.log