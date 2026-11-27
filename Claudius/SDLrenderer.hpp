#pragma once
#pragma once
#pragma once
#include "SDL.h"
#include<stdexcept>
#include "Window.h"

class SDLrenderer {

	SDL_Renderer* renderer = nullptr;

public:
	explicit SDLrenderer(const Window& window) {
		renderer = SDL_CreateRenderer(window.GetPointer(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);

		if (renderer == nullptr) {
			throw std::runtime_error(SDL_GetError()); //TODO: catch error in main
		}
	}

	~SDLrenderer() {
		SDL_DestroyRenderer(renderer);
	}

	SDLrenderer(const SDLrenderer&) = delete;
	SDLrenderer operator=(const SDLrenderer&) = delete;

	SDLrenderer(SDLrenderer&&) = delete;
	SDLrenderer operator=(SDLrenderer&&) = delete;

	SDL_Renderer* GetPointer()  const noexcept {
		return renderer;
	}
};