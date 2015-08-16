CFLAGS = -Wall -Werror
LFLAGS = `sdl-config --libs` -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
OBJS = audio.o collisions.o draw.o entity.o font.o input.o graphics.o main.o mapgen.o
PROG = game
CXX = gcc

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
%.o: src/%.c src/%.h src/defs.h src/structs.h
	$(CXX) $(CFLAGS) -c -s $<

# linking the program.
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS)

# cleaning everything that can be automatically recreated with "make".
clean:
	rm $(PROG) *.o

maprenderer: 
	gcc -o maprenderer util/maprenderer.c 
