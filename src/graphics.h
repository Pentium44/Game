void drawImage(SDL_Surface *image, int x, int y);
void loadSprite(int index, char *name);
void freeSprites();
void loadAllSprites();
/* Animation */
void loadAnimation(char *name, Animation *anim);
void freeAnimation(Animation *anim);
void doAnimation(Animation *anim);
void drawAnimation(Animation *anim, int x, int y);
