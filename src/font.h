TTF_Font *loadFont(char *name, int size);
void closeFont(TTF_Font *font);
void drawString(char *text, int x, int y, TTF_Font *font, int centerX, int centerY);
