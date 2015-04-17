#include "gamestate.h"

Uint8 *scanKeyboard(void) {
	Uint8 *keyboard;
	
	SDL_PumpEvents();
	keyboard = SDL_GetKeyboardState(NULL);
	return keyboard;
}

void handleKeys(Uint8 *keys) {

	/* check which key is pressed */
	if (keys[SDL_SCANCODE_ESCAPE]) {
		log_info("Escape was pressed.\n", NULL);
		Running = FALSE;
	}

}
