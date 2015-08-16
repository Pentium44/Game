void clearEntities();
int getFreeEntity();
void doEntities();
void drawEntities();
void drawStandardEntity();
void initPlayer();
void doPlayer();
void drawPlayer();
/* Map gen */
void drawMapChunk(int c, int x, int y);
void drawMap();
/* other non-standard entities */
void addBullet(int, int);
void addNPC(int x, int y);
void moveNPC(void);
/* null stuffs */
//void nullAction(void);
