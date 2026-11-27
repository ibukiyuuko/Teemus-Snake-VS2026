#pragma once
#pragma once
#include "SDL.h"

class SDLsystem {
public:
	explicit SDLsystem(){
		SDL_Init(SDL_INIT_EVERYTHING);
	}

	~SDLsystem() {
		SDL_Quit();
	}

	SDLsystem(const SDLsystem&) = delete;
	SDLsystem operator=(const SDLsystem&) = delete;

	SDLsystem(SDLsystem&&) = delete;
	SDLsystem operator=(SDLsystem&&) = delete;
};