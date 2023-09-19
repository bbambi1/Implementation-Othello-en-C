CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=
SOURCES=gameplay.c othello.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=othello_game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
