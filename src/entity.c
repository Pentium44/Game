#include "entity.h"
#include "structs.h"
#include "audio.h"
#include "graphics.h"
#include "mapgen.h"

Entity player;
Control input;
Entity *self, entity[MAX_ENTITIES];

SDL_Surface *getSprite(int index);

/*

   Entity functions, used by all entities. Players, walls, NPCs (Future stuffs)

*/

void clearEntities()
{
	int i;
	
	/* Clear the list */
	for (i=0;i<MAX_ENTITIES;i++)
	{
		memset(&entity[i], 0, sizeof(Entity));
	}
}

int getFreeEntity()
{
	int i;
	
	/* Loop through all the entities and find a free slot */
	for (i=0;i<MAX_ENTITIES;i++)
	{
		if (entity[i].active == 0)
		{
			memset(&entity[i], 0, sizeof(Entity));
			entity[i].active = 1;
			return i;
		}
	}
	
	/* Return -1 if you couldn't any free slots */
	return -1;
}

void doEntities()
{
	int i;
	
	/* Loop through the entities and perform their action */
	for (i=0;i<MAX_ENTITIES;i++)
	{
		self = &entity[i];
		if (self->active == 1)
		{
			self->action();
		}
	}
}

void drawEntities()
{
	int i;
	
	/* Loop through the entities and perform their action */
	for (i=0;i<MAX_ENTITIES;i++)
	{
		self = &entity[i];
		if (self->active == 1)
		{
			self->draw();
		}
	}
}

void drawStandardEntity()
{
	drawImage(self->sprite, self->x, self->y);
}

/* 
  
  Player entity added to main file. Compact things
  
*/

void initPlayer()
{
	player.sprite = getSprite(PLAYER_SPRITE);
	
	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGHT / 2;
}

void doPlayer()
{
	player.thinkTime--;
	
	if (player.thinkTime <= 0)
	{
		player.thinkTime = 0;
	}
	
	if (input.up == 1)
	{
		player.y -= PLAYER_SPEED;
		
		/* Don't allow the player to move off the screen */
		if (player.y < 0)
		{
			player.y = 0;
		}
	}
	
	if (input.down == 1)
	{
		player.y += PLAYER_SPEED;
		
		/* Don't allow the player to move off the screen */
		if (player.y + player.sprite->h >= SCREEN_HEIGHT)
		{
			player.y = SCREEN_HEIGHT - (player.sprite->h + 1);
		}
	}
	
	if (input.left == 1)
	{
		player.x -= PLAYER_SPEED;
		
		/* Don't allow the player to move off the screen */
		if (player.x < 0)
		{
			player.x = 0;
		}
	}
	
	if (input.right == 1)
	{
		player.x += PLAYER_SPEED;
		
		/* Don't allow the player to move off the screen */
		if (player.x + player.sprite->w >= SCREEN_WIDTH)
		{
			player.x = SCREEN_WIDTH - (player.sprite->w + 1);
		}
	}
	
	if (input.fire == 1)
	{
		/* You can only fire when the thinkTime is 0 or less */
		if (player.thinkTime <= 0)
		{
			addBullet(player.x + player.sprite->w, player.y + (player.sprite->h / 2));
			player.thinkTime = MAX_RELOAD_TIME;
		}
	}
}

void drawPlayer()
{
	/* Draw the image in the player structure */
	drawImage(player.sprite, player.x, player.y);
}

Animation dirtAnim;

/* Map functions */

static void nullAction(void);

void drawMapChunk(int c, int x, int y)
{	
	int i = getFreeEntity();
	
	if (i == -1)
	{
		printf("Couldn't get a free slot for a dirt!\n");
		
		return;
	}
	
	entity[i].x = x;
	entity[i].y = y;
	entity[i].action = &nullAction;
	entity[i].draw = &drawStandardEntity;
	
	if(c == DIRT_CHUNK) entity[i].sprite = getSprite(DIRT_SPRITE);
	if(c == GRASS_CHUNK) entity[i].sprite = getSprite(GRASS_SPRITE);
	if(c == TOP_DIRT_EDGE_CHUNK) entity[i].sprite = getSprite(TOP_DIRT_EDGE_SPRITE);
	if(c == BOT_DIRT_EDGE_CHUNK) entity[i].sprite = getSprite(BOT_DIRT_EDGE_SPRITE);
	
}

void drawMap() {
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
		printf("Error: loading map \"%s\" failed", filename);
		exit(1);
	}
	
	while ((i = fgetc(file)) != EOF)
	{
		int c = charForChunk((char)i);
		
		if(c == RETURN_CHUNK || c == ERROR) {
			iy = iy + 32;
			ix = 0;
			continue;
		}
		
		//printf("Block ID: %d, location: (%d, %d)\n", c, ix, iy);
		
		drawMapChunk(c, ix, iy);		
		ix = ix + 32;
	}
	
}

/*

  Bullet entity functions

*/

static void moveStandardBullet(void);

void addBullet(int x, int y)
{
	int i = getFreeEntity();
	
	if (i == -1)
	{
		printf("Couldn't get a free slot for a bullet!\n");
		
		return;
	}
	
	entity[i].x = x;
	entity[i].y = y;
	entity[i].action = &moveStandardBullet;
	entity[i].draw = &drawStandardEntity;
	entity[i].sprite = getSprite(BULLET_SPRITE);
	entity[i].type = TYPE_BULLET;
	
	/* Play a sound when the shot is fired */
	playSound(BULLET_SOUND);
}

static void moveStandardBullet()
{
	/* Move the bullet across the screen */
	if(input.yaw == EAST) 
	{
		self->x += BULLET_SPEED;
	}
	else if(input.yaw == WEST)
	{
		self->x -= BULLET_SPEED;
	}
	else if(input.yaw == NORTH)
	{
		self->y += BULLET_SPEED;
	}
	else
	{
		self->y -= BULLET_SPEED;
	}
	
	/* Kill the bullet if it moves off the screen */
	if (self->x >= SCREEN_WIDTH || self->x <= 0 || self->y >= SCREEN_HEIGHT || self->y <= 0)
	{
		self->active = 0;
	}
}

/*

  NPC entity, does nothing really as of yet

*/

void addNPC(int x, int y)
{
	int i = getFreeEntity();
	
	if (i == -1)
	{
		printf("Couldn't get a free slot for a NPC!\n");
		
		return;
	}
	
	entity[i].x = x;
	entity[i].y = y;
	entity[i].action = &moveNPC;
	entity[i].draw = &drawStandardEntity;
	entity[i].sprite = getSprite(UFO_SPRITE);
	entity[i].type = TYPE_ENEMY;
}

void moveNPC(void)
{
	/* Do nothing, just sit there */
}

/* null action; for map generation */

void nullAction(void) {
	// do nothing
}
