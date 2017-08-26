#include "structs.h"
#include "graphics.h"
#include "draw.h"
#include "audio.h"

Sprite sprite[MAX_SPRITES];
Game game;
Control input;

SDL_Surface *loadImage(char *name);

SDL_Surface *loadImage(char *name)
{
	/* Load the image using SDL Image */
	
	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image;
	
	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);
		
		return NULL;
	}
	
	/* Make the background transparent */
	
	SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format, 0, 0, 0));
	
	/* Convert the image to the screen's native format */
	
	image = SDL_DisplayFormat(temp);
	
	SDL_FreeSurface(temp);
	
	if (image == NULL)
	{
		printf("Failed to convert image %s to native format\n", name);
		
		return NULL;
	}
	
	/* Return the processed image */
	
	return image;
}

void drawImage(SDL_Surface *image, int x, int y)
{
	SDL_Rect dest;
	
	/* Set the blitting rectangle to the size of the src image */
	
	dest.x = x;
	dest.y = y;
	dest.w = image->w;
	dest.h = image->h;
	
	/* Blit the entire image onto the screen at coordinates x and y */
	
	SDL_BlitSurface(image, NULL, game.screen, &dest);
}

void loadSprite(int index, char *name)
{
	/* Load the image into the next slot in the sprite bank */
	
	if (index >= MAX_SPRITES || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);
		
		exit(1);
	}
	
	sprite[index].image = loadImage(name);
	
	if (sprite[index].image == NULL)
	{
		exit(1);
	}
}

SDL_Surface *getSprite(int index)
{
	if (index >= MAX_SPRITES || index < 0)
	{
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITES);
		
		exit(1);
	}
	
	return sprite[index].image;
}

void freeSprites()
{
	int i;
	
	/* Loop through the sprite bank and clear the images */
	for (i=0;i<MAX_SPRITES;i++)
	{
		if (sprite[i].image != NULL)
		{
			SDL_FreeSurface(sprite[i].image);
		}
	}
}

void loadAllSprites()
{
	loadSprite(PLAYER_RIGHT_SPRITE, "gfx/player/player01-right.png");
	loadSprite(PLAYER_LEFT_SPRITE, "gfx/player/player01-left.png");
	loadSprite(PLAYER_UP_SPRITE, "gfx/player/player01-up.png");
	loadSprite(PLAYER_DOWN_SPRITE, "gfx/player/player01-down.png");
	//loadSprite(BULLET_SPRITE, "gfx/bullet.png");
	loadSprite(DIRT_SPRITE, "gfx/terrain/dirt.png");
	loadSprite(GRASS_SPRITE, "gfx/terrain/grass.png");
	loadSprite(DIRT_TOP_EDGE_SPRITE, "gfx/terrain/dirt_top_edge.png");
	loadSprite(DIRT_BOT_EDGE_SPRITE, "gfx/terrain/dirt_bot_edge.png");
	loadSprite(STEEL_WALL_SIDE_SPRITE, "gfx/terrain/steel_wall_side.png");
	loadSprite(STEEL_WALL_FRONT_SPRITE, "gfx/terrain/steel_wall_front.png");
	loadSprite(STEEL_WALL_BLCORNER_SPRITE, "gfx/terrain/steel_wall_blcorner.png");
	/*loadSprite(UFO_SPRITE, "gfx/enemy.png");*/
}

/* Animations */

void loadAnimation(char *name, Animation *anim)  
{  
    /* Load up the data file that describes the animation */  
      
    int i;  
    FILE *fp = fopen(name, "rb");  
    char frameName[20];  
      
    if (fp == NULL)  
    {  
        printf("Failed to load animation file %s\n", name);  
          
        exit(1);  
    }  
      
    /* Read the frame count */  
      
    fscanf(fp, "%d", &anim->frameCount);  
      
    /* Allocate space for the animation */  
      
    anim->frame = (SDL_Surface **)malloc(anim->frameCount * sizeof(SDL_Surface *));  
      
    if (anim->frame == NULL)  
    {  
        printf("Ran out of memory when creating the animation for %s\n", name);  
          
        exit(1);  
    }  
      
    /* Now load up each frame */  
      
    for (i=0;i<anim->frameCount;i++)  
    {  
        fscanf(fp, "%s", frameName);  
          
        anim->frame[i] = loadImage(frameName);  
          
        if (anim->frame[i] == NULL)  
        {  
            printf("Failed to load animation frame %s\n", frameName);  
              
            exit(1);  
        }  
    }  
      
    /* Set the initial frame index to 0 */  
      
    anim->frameIndex = 0;  
      
    /* Set the animation counter */  
      
    anim->counter = input.aspeed;  
} 

void freeAnimation(Animation *anim)  
{  
    int i;  
      
    /* Loop through each of the frames and free it */  
  
    if (anim->frame != NULL)  
    {  
        for (i=0;i<anim->frameCount;i++)  
        {  
            if (anim->frame[i] != NULL)  
            {  
                SDL_FreeSurface(anim->frame[i]);  
            }  
        }  
          
        free(anim->frame);  
    }  
} 

void doAnimation(Animation *anim)  
{  
    anim->counter--;  
 
      
    if (anim->counter <= 0)  
    {  
        anim->frameIndex++;  
        
        // Slip in walking sounds here
        if (anim->frameIndex == 1)
        {
			playSound(STEP_GRASS_L_SOUND);
		}
		else if (anim->frameIndex == 3)
		{
			playSound(STEP_GRASS_R_SOUND);
		}
        
        if (anim->frameIndex == anim->frameCount)  
        {  
            anim->frameIndex = 0;  
        }  
          
        anim->counter = input.aspeed;  
    }  
    
}

void drawAnimation(Animation *anim, int x, int y)  
{  
    drawImage(anim->frame[anim->frameIndex], x, y);  
}
