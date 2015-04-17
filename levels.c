#include "gamestate.h"

SDL_Surface *genCaveLevel(Window *window, Tilemap *tilemap, Level *leveldata) {

	// TODO(ekollof): Just use window size for now. Use bigger surfaces later.
	
	int i,j = 0;
	// int levelsize = window->width * window->height;
	int levelx = window->width;
	int levely = window->height;
	// int windowtiles = levelsize / TILE_WIDTH;
	int columns = window->width / TILE_WIDTH;
	int rows = window->height / TILE_HEIGHT;
	SDL_Rect tileRect;

	// Our canvas to blit tiles to.
	SDL_Surface *level = SDL_CreateRGBSurface(0, levelx, levely, window->bpp, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

	// Just pick random tiles for now. 
	for (i = 0; i < columns; i++) {
		for (j = 0; j < rows; j++) {

			int tilex = 0;
			int tiley = 0;

			log_info("Leveldata: %d", leveldata->level[i][j]);
			switch (leveldata->level[i][j]) {
			case TILE_OPEN:
				tilex = 1;
				tiley = 1;
				break;
			case TILE_CLOSE:
				tilex = 2;
				tiley = 3;
				break;
			case TILE_LVERT:
				tilex = 0;
				tiley = 1;
				break;
			case TILE_RVERT:
				tilex = 2;
				tiley = 1;
				break;
			case TILE_UHORZ:
				tilex = 1;
				tiley = 2;
				break;
			case TILE_DHORZ:
				tilex = 1;
				tiley = 0;
				break;
			case TILE_TLCORN:
				tilex = 2;
				tiley = 2;
				break;
			case TILE_TRCORN:
				tilex = 0;
				tiley = 2;
				break;
			default:
				tilex = 1;
				tiley = 1;
				break;
			}


			tileRect.x = i * TILE_WIDTH;
			tileRect.y = j * TILE_HEIGHT;
			tileRect.w = TILE_WIDTH;
			tileRect.h = TILE_HEIGHT;
			
			// log_info("Placing tile at  (%d,%d)\n", i, j);
			if (SDL_BlitSurface(tilemap->tile[tilex][tiley], NULL, level, &tileRect)) {
				log_error("SDL_BlitSurface failed for tile (%d,%d)\n", i, j);
			}
		}
	}
	return level;
}

void initMap(int map[][MAXTILES_X], int xx, int yy, float chance) {
	int i, j = 0;
	float alivechance = chance;

	log_info("%d %d", xx, yy);

	for (i = 0; i < xx; i++) {
		for (j = 0; j < yy; j++) {

			float random = (float) rand() / (float) RAND_MAX;
			if (random < alivechance) {
				log_info("Placing point at (%d,%d)\n", i, j);
				map[i][j] = TRUE;
			} else {
				map[i][j] = FALSE;
			}
		}
	}
}

void copyMap(int map[][MAXTILES_X], int newmap[][MAXTILES_X], int columns, int rows) {
	int x, y = 0;

	for (x = 0; x < columns; x++) {
		for (y = 0; y < rows; y++) {
			map[x][y] = newmap[x][y];
		}
	}
}

void growCaves2(int map[][MAXTILES_X], int xx, int yy, int blimit, int dlimit) {
	int x, y = 0;

	for (x = 0; x < xx; x++) {
		for (y = 0; y < yy; y++) {
			int neighbors = checkNeighbor(map, x, y, yy, xx);
			if (map[x][y]) {
				if (neighbors < dlimit)
					map[x][y] = FALSE;
				else
					map[x][y] = TRUE;
			} else {
				if (neighbors > blimit)
					map[x][y] = TRUE;
				else
					map[x][y] = FALSE;
			}
		}
	}
}

void growCaves(int map[][MAXTILES_X], int newmap[][MAXTILES_X], int xx, int yy, int blimit, int dlimit) {
	int x, y = 0;

	for (x = 0; x < xx; x++) {
		for (y = 0; y < yy; y++) {
			int neighbors = checkNeighbor(map, x, y, yy, xx);
			if (map[x][y]) {
				if (neighbors < dlimit)
					newmap[x][y] = FALSE;
				else
					newmap[x][y] = TRUE;
			} else {
				if (neighbors > blimit)
					newmap[x][y] = TRUE;
				else
					newmap[x][y] = FALSE;
			}
			

		}
	}
}

int checkNeighbor(int map[][MAXTILES_X], int x, int y, int yy, int xx) {
	int count = 0;
	int i, j = 0;

	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			int neigh_x = x + i;
			int neigh_y = y + j;

			if (i == 0 && j == 0) {
			} else
			// Don't count ourselves.
			if (neigh_x < 0 || neigh_y < 0 || neigh_x >= xx  || neigh_y >= yy) {
				// Are we looking at an edge?
				count += 1;
				continue;
			} else
			// log_info("Checking %d %d\n", neigh_x, neigh_y)
			if (map[neigh_x][neigh_y]) {
				count += 1;
			}
			
		}
	}
	return count;
}

void fixWalls(Level *level) {
	// Find alls and corners and fix them up.
	// 
	// 0 == Open space
	// 1 == Filled space
	// 2 == vertical wall left
	// 3 == vertical wall right
	// 4 == horizontal wall left
	// 5 == horizontal wall right
	// 6 == top left corner
	// 7 == top right corner
	// 8 == bottom left corner
	// 9 == bottom right corner

	int x, y = 0;
	int xtiles = level->levelX / TILE_WIDTH;
	int ytiles = level->levelY / TILE_HEIGHT;
	Level tmplevel;

	char *neighbors;
	copyMap(tmplevel.level, level->level, xtiles, ytiles);

	for (x = 0; x < xtiles; x++) {
		for (y = 0; y < ytiles; y++) {
			neighbors = findTileType(&tmplevel, x, y, xtiles, ytiles);
			level->level[x][y] = getTileType(neighbors, tmplevel.level[x][y]);
			log_info("Map: %dx%d %s -> %d", x, y, neighbors, level->level[x][y]);
			SDL_free(neighbors);
		}
	}
}

int getTileType(char *pattern, int value) {
	if (!strcmp(pattern, "000000000")) {
		// completely open
		// 
		// . . .
		// . . .
		// . . .
		log_info("Open space", NULL);
		return TILE_OPEN;
	}
	if (!strcmp(pattern, "111111111")) {
		// Fully surrounded
		//
		// 1 4 7
		// 2 5 8
		// 3 6 9
		log_info("Closed space", NULL);
		return TILE_CLOSE;
	}
	if (!strcmp(pattern, "111000000")) {
		// Left vertical wall
		//
		// 1 . .
		// 2 . .
		// 3 . .
		log_info("Left vertical wall", NULL);
		return TILE_LVERT;
	}
	if (!strcmp(pattern, "000000111")) {
		// Right vertical wall
		//
		// . . 7
		// . . 8
		// . . 9
		log_info("Right vertical wall", NULL);
		return TILE_RVERT;
	}
	if (!strcmp(pattern, "100100100")) {
		// Up horizontal wall
		//
		// 1 4 7
		// . . .
		// . . .
		log_info("Up horizontal wall", NULL);
		return TILE_DHORZ;
	}
	if (!strcmp(pattern, "001001001")) {
		// Up horizontal wall
		//
		// . . .
		// . . .
		// 3 6 9
		log_info("Down horizontal wall", NULL);
		return TILE_UHORZ;
	}
	if (!strcmp(pattern, "000011011")) {
		// Top left corner
		//
		// . . .
		// . 6 8
		// . 7 9
		log_info("Top left corner", NULL);
		return TILE_TLCORN;
	}
	if (!strcmp(pattern, "011001100")) {
		// Top right corner
		//
		// . . .
		// 2 6 .
		// 3 7 .
		log_info("Top right corner", NULL);
		return TILE_TRCORN;
	}


	log_info("Original value.", NULL);
	return value;
}

char *findTileType(Level *level, int x, int y, int xx, int yy) {
	int i, j = 0;
	int occupied = 0;
	char *ret;
	
	ret = SDL_malloc(10);
	SDL_memset(ret, 0, 10);

	/*
	Order of processing.
	1 4 7
	2 5 8
	3 6 9
	*/

	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			int neigh_x = x + i;
			int neigh_y = y + j;

			if (neigh_x < 0 || neigh_y < 0 || neigh_x >= xx || neigh_y >= yy) {
					log_info("At level edge\n", NULL);
					ret[occupied] = '1';
			} else {
				// log_info("Checking %d %d\n", neigh_x, neigh_y)
				if (level->level[neigh_x][neigh_y]) {
					ret[occupied] = '1';
				} else {
					ret[occupied] = '0';
				}
			}
			occupied++;
		}
	}
	ret[10] = '\0';
	return ret;
}
