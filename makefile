CC = gcc
CFLAGS = -g -Wall
LIBS = -lncurses -lm

SRC = main.c stack.c queue.c world.c
OBJ = $(SRC:.c=.o)
nomeDoPrograma = deburger

all: $(nomeDoPrograma)

$(nomeDoPrograma): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(nomeDoPrograma)
