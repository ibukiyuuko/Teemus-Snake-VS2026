#pragma once
#include "SDL.h"
#include<stdexcept>
#include <string>
class Window {
	SDL_Window* window = nullptr; 

	public:
		explicit Window(std::string title ,int width, int height) 
		{
			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WindowFlags::SDL_WINDOW_RESIZABLE);

			if (window == nullptr) {
				throw std::runtime_error(SDL_GetError()); //TODO: catch error in main
			}
		}

		~Window() {
			SDL_DestroyWindow(window);
		}

		Window(const Window&) = delete;
		Window operator=(const Window&) = delete;

		Window(Window&&) = delete;
		Window operator=(Window&&) = delete;
		
		SDL_Window* GetPointer()  const noexcept{
			return window;
		}
};