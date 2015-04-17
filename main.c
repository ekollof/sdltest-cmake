#include "gamestate.h"

int main(int argc, char* args[]) {

	// Main game loop
	Window window;
	window.height = SCREEN_HEIGHT;
	window.width = SCREEN_WIDTH;
	window.bpp = 32;
	int angle = 0;
	int pastfps = 0;
	int past = 0;
	int i = 0;
	

	if (init(&window)) {


		// SDL_Image (for tilemaps)
		init_img();

		// Seed RNG
		srand((int)time(NULL));

		// Game assets
		Gamestate game;
		game.fps = 0;
		Tilemap cavemap;
		Level cavelevel;
		loadTileMap("assets/cave.png", &window, &cavemap);
		

		// Generate map.
		// TODO(emiel): move this somewhere else. Make blimit, dlimit and simsteps configurable
		cavelevel.levelX = window.width;
		cavelevel.levelY = window.height;

		initMap(cavelevel.level, cavelevel.levelX / TILE_WIDTH, cavelevel.levelY / TILE_HEIGHT, 0.3f);
		
		for (i = 0; i < 5; i++) {
			int newmap[MAXTILES_X][MAXTILES_Y];
			growCaves(cavelevel.level, newmap, cavelevel.levelX / TILE_WIDTH, cavelevel.levelY / TILE_HEIGHT, 3, 3);
			copyMap(cavelevel.level, newmap, cavelevel.levelX / TILE_WIDTH, cavelevel.levelY / TILE_HEIGHT);
		}

		fixWalls(&cavelevel);



		SDL_Surface *level = genCaveLevel(&window, &cavemap, &cavelevel);

		SDL_Texture *frame = loadTexture(&window, level);

		Running = TRUE;
		while (Running) {
			int curtime = SDL_GetTicks();
			uint8_t *keys;

			if (curtime - past >= 16) {
				past = SDL_GetTicks();
			}

			if (curtime - pastfps >= 1000) {
				log_info("%d fps\n", game.fps);
				game.fps = 0;
				pastfps = curtime;
			}
		
			keys = scanKeyboard();
			handleKeys(keys);
			handleEvents(&window);

			render(&window, frame, angle);
	
			game.fps++;
		}
		cleanup(&window);
	}	

	return 0;
}
