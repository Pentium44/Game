#include "structs.h"
#include "draw.h"
#include "entity.h"
#include "font.h"
#include "graphics.h"

Game game;

void draw()
{
	char text[20];
	
	/* Blank the screen */
	SDL_FillRect(game.screen, NULL, 0);
	
	/* Draw the entities; before anything
	   so everything is on top of map */
	drawEntities();
	
	/* Draw the score */
	sprintf(text, "SCORE: %05d", game.score);
	drawString(text, 100, 10, game.font, 1, 0);
	
	/* Draw the player */
	drawPlayer();
	
	/* Update the buffer */
	SDL_Flip(game.screen);
	
	/* Sleep briefly */
	SDL_Delay(1);
}

void delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}
	
	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}
	
	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}
