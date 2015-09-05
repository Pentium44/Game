.POSIX:  ;

include config.mk

OBJS    = src/audio.o src/collisions.o src/draw.o src/entity.o src/font.o src/input.o src/graphics.o src/main.o src/mapgen.o
PROG    = game

# top-level rule to create the program.
all: $(PROG)

# linking the program.
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm -f $(PROG) $(OBJS)

maprenderer: 
	$(CC) -o maprenderer util/maprenderer.c 

