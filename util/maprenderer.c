/*
Game mapgen test.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Map chunk types */
#define DIRT_CHUNK 2
#define PATH_CHUNK 3
#define TOP_PATH_EDGE_CHUNK 4
#define BOT_PATH_EDGE_CHUNK 5

#define RETURN_CHUNK 0

#define ERROR 1

int charForChunk(char chunk)
{
	switch(chunk)
	{
		case '\r': return RETURN_CHUNK;
		case '#': return DIRT_CHUNK;
		case '=': return PATH_CHUNK;
		case '^': return TOP_PATH_EDGE_CHUNK;
		case 'v': return BOT_PATH_EDGE_CHUNK;
	}
	
	return ERROR;
}

int main() {
	int ix;
	int iy;
	ix = 0;
	iy = 0;
	
	char *filename = "maps/map01.map";
	FILE *file = fopen(filename, "r");
	
	int i;
	
	// check if file is empty.
	if(file == NULL)
	{
		printf("Error: loading map \"%s\" failed\n", filename);
		exit(1);
	}
	
	while ((i = fgetc(file)) != EOF)
	{
		int c = charForChunk((char)i);
		
		if(c == RETURN_CHUNK || c == ERROR)
		{
			continue;
		}
		
		if(ix >= 800) {
			iy = iy + 32;
			ix = 0;
		}
	
		if(iy >= 480) {
			break;
		}
		
		printf("Block ID: %d, location: (%d, %d)\n", c, ix, iy);
		ix = ix + 32;
	}
	exit(0);
}
