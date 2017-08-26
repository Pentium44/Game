#include "main.h"
#include "structs.h"
#include "input.h"
#include "draw.h"
#include "entity.h"
#include "graphics.h"
#include "font.h"
#include "audio.h"
#include "collisions.h"

Game game;
Control input;
Entity player, *self, entity[MAX_ENTITIES];
Sprite sprite[MAX_SPRITES];
Sound sound[MAX_SOUNDS];

void init(char *title)
{
	
	/* Initialise SDL */
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	/* Initialise SDL_TTF */
	
	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		exit(1);
	}
	
	/* Open a screen */
	
	game.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWPALETTE|SDL_DOUBLEBUF);
	
	if (game.screen == NULL)
	{
		printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}
	
	/* Set the audio rate to 22050, 16 bit stereo, 2 channels and a 4096 byte buffer */
	
	if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0)
	{
		printf("Could not open audio: %s\n", Mix_GetError());
		exit(1);
	}
	
	/* Set the screen title */
	
	SDL_WM_SetCaption(title, NULL);
}

void cleanup()
{
	/* Free the sprites */
	freeSprites();
	
	/* Free the sounds */
	freeSounds();
	
	/* Close the font */
	closeFont(game.font);
	
	/* Close the mixer */
	Mix_CloseAudio();
	
	/* Close SDL_TTF */
	TTF_Quit();
	
	/* Shut down SDL */
	SDL_Quit();
}

Animation walkUpAnimation;
Animation walkDownAnimation;
Animation walkRightAnimation;
Animation walkLeftAnimation;

int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go;
	
	/* Set some player variables */
	input.aspeed = 10;
	input.pspeed = 1;
	
	/* Start up SDL */
	init("Maetrox");
	
	/* Call the cleanup function when the program exits */
	atexit(cleanup);
	go = 1;
	
	/* Load all the sprites */
	loadAllSprites();
	
	/* Load all the sounds */
	loadAllSounds();
	
	/* Load animations */
	loadAnimation("gfx/anim/walk-up.dat", &walkUpAnimation);  
	loadAnimation("gfx/anim/walk-down.dat", &walkDownAnimation);  
	loadAnimation("gfx/anim/walk-right.dat", &walkRightAnimation);  
	loadAnimation("gfx/anim/walk-left.dat", &walkLeftAnimation);  
	
	/* Load the font */
	game.font = loadFont("font/Cabin.ttf", 16);
	
	/* Draw map */
	drawMap();
	
	/* Intialise the player */
	initPlayer();
	
	/* These will be rendered with a map generator */
	/*
	addNPC(500, 50);
	addNPC(500, 100);
	addNPC(500, 150);
	addNPC(500, 200);
	addNPC(500, 250);
	addNPC(500, 300);
	*/
	
	/* Set start time for FPS and set first frame */
	game.startTime = SDL_GetTicks();
	game.framecount = 1;
	
	/* Loop indefinitely for messages */
	while (go == 1)
	{
		/* Get the input */
		if(game.walkAnimationCount == 0)
		{
			getInput();
		}
		
		/* Update the player's position */
		doPlayer();
		
		/* Update the entities */
		doEntities();
		
		/* Do the collisions */
		doCollisions();
		
		/* Draw everything */
		draw();
		
		/* Sleep briefly to stop sucking up all the CPU time */
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + VSYNC_TIMING;
		++game.framecount;
	}
	
	/* Exit the program */
	exit(0);
}
