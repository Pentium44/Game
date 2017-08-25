#include "input.h"
#include "structs.h"

Control input;

// Keep player from holding multiple walking keys down
void setKeyDownOff()
{
	input.up = 0;
	input.down = 0;
	input.right = 0;
	input.left = 0;
}

void getInput()
{
	SDL_Event event;
	
	/* Loop through waiting messages and process them */
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			/*
			** Closing the Window or pressing Escape will exit the program
			** Pressing the arrow keys will move the player
			** Pressing space will fire a bullet
			*/
			
			case SDL_QUIT:
				exit(0);
				break;
			
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						setKeyDownOff();
						input.up = 1;
						input.yaw = NORTH;
						break;
					
					case SDLK_DOWN:
						setKeyDownOff();
						input.down = 1;
						input.yaw = SOUTH;
						break;
						
					case SDLK_LEFT:
						setKeyDownOff();
						input.left = 1;
						input.yaw = WEST;
						break;
						
					case SDLK_RIGHT:
						setKeyDownOff();
						input.right = 1;
						input.yaw = EAST;
						break;
						
					case SDLK_LSHIFT:
						input.aspeed = 3;
						input.pspeed = 2;
						break;
						
					/*
					case SDLK_SPACE:
						input.fire = 1;
						break;
					*/
					
					case SDLK_ESCAPE:
						exit(0);
						break;
					
					default:
					break;
				}
				break;
			
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						input.up = 0;
						break;
					
					case SDLK_DOWN:
						input.down = 0;
						break;
						
					case SDLK_LEFT:
						input.left = 0;
						break;
						
					case SDLK_RIGHT:
						input.right = 0;
						break;
						
					case SDLK_LSHIFT:	
						input.aspeed = 5;
						input.pspeed = 1;
						break;
						
					case SDLK_SPACE:
						input.fire = 0;
						break;
					
					default:
						break;
				}
				break;
		}
	}
}
