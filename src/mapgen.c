#include "mapgen.h"
#include "structs.h"

int charForChunk(char chunk)
{
	switch(chunk)
	{
		case '\r': return RETURN_CHUNK;
		case '#': return GRASS_CHUNK;
		case '=': return DIRT_CHUNK;
		case '^': return DIRT_TOP_EDGE_CHUNK;
		case 'v': return DIRT_BOT_EDGE_CHUNK;
		case ':': return STEEL_WALL_SIDE_CHUNK;
		case 'a': return STEEL_WALL_BLCORNER_CHUNK;
		case '-': return STEEL_WALL_FRONT_CHUNK;
	}
	
	return ERROR;
}
