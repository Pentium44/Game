#include "defs.h"

typedef struct Game
{
	int score, fps, framecount, walkAnimationCount, playerWalkDirection;
	float startTime;
	SDL_Surface *screen;
	TTF_Font *font;
} Game;

typedef struct Sprite
{
	SDL_Surface *image;
} Sprite;

typedef struct Sound
{
	Mix_Chunk *effect;
} Sound;

typedef struct Entity
{
	int active, type;
	int x, y, thinkTime;
	SDL_Surface *sprite;
	void (*action)(void);
	void (*draw)(void);
} Entity;

typedef struct Control
{
	int yaw, up, down, left, right, fire, aspeed, pspeed, byaw, factive;
} Control;

typedef struct Animation  
{  
	int frameCount, frameIndex, counter;  
	SDL_Surface **frame;  
} Animation;  
