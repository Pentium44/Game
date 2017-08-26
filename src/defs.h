#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define MAX_ENTITIES 975
#define MAX_RELOAD_TIME 35
#define VSYNC_TIMING 17 // 60 fps
//#define VSYNC_TIMING 34 // 30 fps
#define BULLET_SPEED 10

/* Yaw definitions */
#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

/* 
   Map chunk types
   Start with 2 because of usage of ERROR.
*/
#define DIRT_CHUNK 2
#define GRASS_CHUNK 3
#define DIRT_TOP_EDGE_CHUNK 4
#define DIRT_BOT_EDGE_CHUNK 5
#define STEEL_WALL_SIDE_CHUNK 6 
#define STEEL_WALL_FRONT_CHUNK 7
#define STEEL_WALL_BLCORNER_CHUNK 8

#define RETURN_CHUNK 0

#define OK 0
#define ERROR 1

enum
{
	PLAYER_RIGHT_SPRITE,
	PLAYER_LEFT_SPRITE,
	PLAYER_UP_SPRITE,
	PLAYER_DOWN_SPRITE,
 	BULLET_SPRITE,
  	UFO_SPRITE,
  	DIRT_SPRITE,
  	GRASS_SPRITE,
  	DIRT_TOP_EDGE_SPRITE,
  	DIRT_BOT_EDGE_SPRITE,
  	STEEL_WALL_SIDE_SPRITE,
  	STEEL_WALL_FRONT_SPRITE,
  	STEEL_WALL_BLCORNER_SPRITE,
	MAX_SPRITES
};

enum
{
	BULLET_SOUND,
	STEP_GRASS_L_SOUND,
	STEP_GRASS_R_SOUND,
 	MAX_SOUNDS
};

enum
{
	TYPE_PLAYER,
	TYPE_BULLET,
 	TYPE_ENEMY,
 	TYPE_GROUND,
 	TYPE_FENCE,
 	TYPE_WALL,
 	TYPE_BARRIER
};
