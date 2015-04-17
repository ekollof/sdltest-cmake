#include "gamestate.h"

int handleWindowEvent(SDL_Event *event, Window *window) {

	switch (event->window.event) {
	case SDL_WINDOWEVENT_RESIZED:
		SDL_GetWindowSize(window->window, &window->width, &window->height);
		log_info("Window %d resized to %d x %d", event->window.windowID, window->width, window->height);
		break;
	case SDL_WINDOWEVENT_CLOSE:
		Running = FALSE;
		cleanup(window);
		break;
	default:
		break;
	}

	return TRUE;
}

