#include "gamestate.h"

void loadTileMap(char *path, Window *window, Tilemap *tilemap) {
	int i;

	tilemap->tilemap = IMG_Load(path);
	
	if (!tilemap->tilemap) {
	  log_error("Could not load image %s!\n", path);
	  return;
	}

#if 0
	tilemap->tilemap = SDL_ConvertSurface(tmp, window->mainsurface->format, 0);
	if (!tilemap->tilemap) {
		log_error("Optimization failed: %s\n", SDL_GetError());
		return;
	}
	SDL_FreeSurface(tmp);
#endif
	
	// Fill out tilemap struct
	tilemap->maxX = tilemap->tilemap->w / TILE_WIDTH - 1;
	tilemap->maxY = tilemap->tilemap->h / TILE_HEIGHT - 1;
	tilemap->numtiles = tilemap->maxX * tilemap->maxY;

	log_info("\nTilemap width: %d tiles\nTilemap height: %d tiles\n%d Tiles total.\n", tilemap->maxX, tilemap->maxY, tilemap->numtiles);
	for (i = 0; i < tilemap->numtiles; i++) {
		int xx = i % tilemap->maxX;
		int yy = i / tilemap->maxX;
		// log_info("X: %d Y: %d\n", xx, yy)
		tilemap->tile[xx][yy]= getTile(tilemap->tilemap, xx, yy);
	}
}

SDL_Surface *getTile(SDL_Surface *tilemap, int indexX, int indexY) {

	assert(tilemap != NULL);

	SDL_Surface *tile = SDL_CreateRGBSurface(0, TILE_WIDTH, TILE_HEIGHT, 32, 0xFF000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	SDL_Rect tileRect;

	int maxhtiles = tilemap->w / TILE_WIDTH - 1;
	int maxvtiles = tilemap->h / TILE_HEIGHT - 1;

	if (indexX > maxhtiles || indexY > maxvtiles) {
		log_error("Tile index (%d, %d) out of bounds. Max X: %d  Max Y; %d",
			indexX,
			indexY,
			maxhtiles,
			maxvtiles);
	}

	tileRect.x = indexX * TILE_WIDTH;
	tileRect.y = indexY * TILE_HEIGHT;
	tileRect.w = TILE_WIDTH;
	tileRect.h = TILE_HEIGHT;

	if (SDL_BlitSurface(tilemap, &tileRect, tile, NULL) < 0) {
		log_error("Tilerec failed. %s", SDL_GetError());
		return NULL;
	}

	return tile;
}

