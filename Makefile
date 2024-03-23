WIDTH ?= 5
HEIGHT ?= 4
SEED ?= 0
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT) -DSEED=$(SEED)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
SRCS = geometry.c neighbors.c world.c set.c moves.c project.c ploop.c
OBJS = $(SRCS:.c=.o)
SRCS2 = geometry.c neighbors.c world.c set.c moves.c ploop.c
OBJS2 = $(SRCS2:.c=.o)

all: project

project: project.o $(OBJS)
	gcc $(CFLAGS) $^ -o project

%.o: src/%.c
	gcc -c $(CFLAGS) $<

%.o: tst/%.c
	gcc -I src -c $(CFLAGS) $<

test: tests.o $(OBJS2)
	gcc $(CFLAGS) $^ -o test
	./test

clean:
	rm -f *.o *~
