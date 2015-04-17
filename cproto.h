/* assets.c */
void loadTileMap(char *path, Window *window, Tilemap *tilemap);
SDL_Surface *getTile(SDL_Surface *tilemap, int indexX, int indexY);
/* events.c */
void handleEvents(Window *window);
/* globals.c */
/* init.c */
int init(Window *window);
void cleanup(Window *window);
void init_img(void);
/* keyboard.c */
Uint8 *scanKeyboard(void);
void handleKeys(Uint8 *keys);
/* levels.c */
SDL_Surface *genCaveLevel(Window *window, Tilemap *tilemap, Level *leveldata);
void initMap(int map[][500 / 2], int xx, int yy, float chance);
void copyMap(int map[][500 / 2], int newmap[][500 / 2], int columns, int rows);
void growCaves2(int map[][500 / 2], int xx, int yy, int blimit, int dlimit);
void growCaves(int map[][500 / 2], int newmap[][500 / 2], int xx, int yy, int blimit, int dlimit);
int checkNeighbor(int map[][500 / 2], int x, int y, int yy, int xx);
void fixWalls(Level *level);
int getTileType(char *pattern, int value);
char *findTileType(Level *level, int x, int y, int xx, int yy);
/* main.c */
int main(int argc, char *args[]);
/* video.c */
SDL_Texture *loadTexture(Window *window, SDL_Surface *surf);
int render(Window *window, SDL_Texture *frame, int angle);
/* window.c */
int handleWindowEvent(SDL_Event *event, Window *window);
