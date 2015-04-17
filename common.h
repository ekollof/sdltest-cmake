#ifndef _COMMON_H
#define _COMMON_H


#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define FPS_MAX 60
#define MAXTILES 500 // Arbitrary value.
#define MAXTILES_X MAXTILES / 2
#define MAXTILES_Y MAXTILES / 2

#define log_error(x, ...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, x, __VA_ARGS__)
#define log_info(x, ...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, x, __VA_ARGS__)
#define log_debug(x, ...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, x, __VA_ARGS__)

/* struct for keeping things together */

typedef struct window {
	SDL_Window *window;
	SDL_Surface *mainsurface;
	SDL_Renderer *renderer;
	int fullscreen;
	int width;
	int height;
	int bpp;
} Window;

typedef struct tilemap {
	SDL_Surface *tilemap;
	SDL_Surface *tile[MAXTILES_X][MAXTILES_Y];
	int **map;
	int maxX;
	int maxY;
	int numtiles;
} Tilemap;

typedef struct level {
	int level[MAXTILES_X][MAXTILES_Y];
	char *levelname;
	int levelX;
	int levelY;
	size_t size;
} Level;

typedef struct viewport {
	int vw; // Viewport width
	int vh; // Viewport height
	int x; // Viewport origin x
	int y; // Viewport origin y
} Viewport;

/* Globals (USE SPARINGLY PLEASE)*/
extern int Running;

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


#endif
