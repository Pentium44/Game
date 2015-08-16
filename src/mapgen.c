#include "mapgen.h"
#include "structs.h"

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
