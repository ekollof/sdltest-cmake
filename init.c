#include "gamestate.h"

int init(Window *window) {
	int success = TRUE;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = FALSE;
	} else {
		//Create window
		window->window = SDL_CreateWindow("SDL experiments", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window->window == NULL) {
			log_error("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = FALSE;
		} else {

			//Get window surface
			window->mainsurface = SDL_GetWindowSurface(window->window);
			window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!window->renderer) {
				log_error("Could not get renderer! SDL Error %s\n", SDL_GetError());
				success = FALSE;
			} else {
				SDL_SetRenderDrawColor(window->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}

		}
	}

	return success;
}

void cleanup(Window *window) {
	//Destroy window
	SDL_DestroyWindow(window->window);

	//Quit SDL subsystems
	SDL_Quit();
}

void init_img(void) {
	int flags = IMG_INIT_PNG;
	int initflags = IMG_Init(flags);

	if ((initflags & flags) != flags) {
		log_error("SDL image init failed: %s", IMG_GetError());
	}
}