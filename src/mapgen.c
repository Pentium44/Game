#include "mapgen.h"
#include "structs.h"

int charForChunk(char chunk)
{
	switch(chunk)
	{
		case '\r': return RETURN_CHUNK;
		case '#': return GRASS_CHUNK;
		case '=': return DIRT_CHUNK;
		case '^': return TOP_DIRT_EDGE_CHUNK;
		case 'v': return BOT_DIRT_EDGE_CHUNK;
	}
	
	return ERROR;
}
