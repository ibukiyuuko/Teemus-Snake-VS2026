#include "SDL.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Transform.h"
#include "Image.h"
#include "Window.h"
#include "SDLsystem.hpp"
#include "SDLrenderer.hpp"

#undef main

// ResourceManager 

struct ResourceImpl
{
	//TO DO: instead of raw pointer use unique/shared pointer to wrap them
	ResourceImpl(SDL_Renderer* renderer) : renderer(renderer) {};
	std::vector<std::pair<std::string, SDL_Texture*>> textures; //TO DO: use structure binding instead of std::pair
	SDL_Renderer* renderer;
	SDL_Texture* GetTexture(unsigned int id)
	{
		if (id < textures.size())
			return textures[id].second;
		else
			return nullptr;
	}
};

bool ResourceManager::LoadImageFromFile(Image& image, const std::string &filePath) //TO DO: use filesystem::path instead of std::string
{
	auto it = impl.textures.begin();
	unsigned int index = 0;
	while (it != impl.textures.end()) //TO DO: std::find_if
	{
		if ((*it).first == filePath)
		{
			image.id = index;
			return true;
		}
		it++;
		index++; //TO DO: use lambda inside
	}
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str()); //TO DO: use struct SDL_Deleter for SDL_surface ptr
	if (surface != nullptr)// TODO: if(surface == nullptr) {return ....}
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(impl.renderer, surface);
		if (texture != nullptr)
		{
			impl.textures.push_back(std::pair<std::string, SDL_Texture*>(filePath, texture));//TODO: structure binding
			image.id = static_cast<unsigned int>(impl.textures.size() - 1);
			image.width = surface->w;
			image.height = surface->h;
			return true;
		}
		else
		{
			const char* error = SDL_GetError(); //TODO: have throw function to call it here when the error exist?
			return false;
		}
	}
	else
	{
		const char* error = SDL_GetError();
		return false;
	}
	return false;
};

// RenderManager
//TODO: it would be nice to put in their own cpp files
struct RenderImpl
{
	SDL_Renderer* renderer; //TODO: use RAII

};

void RenderManager::Render(const Sprite& sprite, const Transform& trans)
{
	spriteEntries.push_back({ sprite, trans });
}

void RenderManager::Render(const Rectangle& rect, const Color& color, const Transform& trans)
{
	rectEntries.push_back({ rect, color, trans });
}

void RenderManager::Clear()
{
	spriteEntries.clear();
	rectEntries.clear();
}

KeyCode TranslateKeyCode(SDL_Keycode code)
{
	switch (code)
	{//TO DO: clarify in switch //just use SDL key, no need to convert from sdl to your keyboard
	case SDLK_ESCAPE: return KeyCode::ESCAPE; break;
	case SDLK_SPACE: return KeyCode::SPACE; break;
	case SDLK_RETURN: return KeyCode::ENTER; break;
	case SDLK_RETURN2: return KeyCode::ENTER; break;
	case SDLK_a: return KeyCode::A; break;
	case SDLK_b: return KeyCode::B; break;
	case SDLK_c: return KeyCode::C; break;
	case SDLK_d: return KeyCode::D; break;
	case SDLK_e: return KeyCode::E; break;
	case SDLK_f: return KeyCode::F; break;
	case SDLK_g: return KeyCode::G; break;
	case SDLK_h: return KeyCode::H; break;
	case SDLK_i: return KeyCode::I; break;
	case SDLK_j: return KeyCode::J; break;
	case SDLK_k: return KeyCode::K; break;
	case SDLK_l: return KeyCode::L; break;
	case SDLK_m: return KeyCode::M; break;
	case SDLK_n: return KeyCode::N; break;
	case SDLK_o: return KeyCode::O; break;
	case SDLK_p: return KeyCode::P; break;
	case SDLK_q: return KeyCode::Q; break;
	case SDLK_r: return KeyCode::R; break;
	case SDLK_s: return KeyCode::S; break;
	case SDLK_t: return KeyCode::T; break;
	case SDLK_u: return KeyCode::U; break;
	case SDLK_v: return KeyCode::V; break;
	case SDLK_w: return KeyCode::W; break;
	case SDLK_x: return KeyCode::X; break;
	case SDLK_y: return KeyCode::Y; break;
	case SDLK_z: return KeyCode::Z; break;
	case SDLK_LEFT: return KeyCode::LEFT_ARROW; break;
	case SDLK_RIGHT: return KeyCode::RIGHT_ARROW; break;
	case SDLK_UP: return KeyCode::UP_ARROW; break;
	case SDLK_DOWN: return KeyCode::DOWN_ARROW; break;
	default: return KeyCode::INVALID; break;
	}
}

int main()
{
	SDLsystem sdlWindow{};
	Window window{"snake", 500, 500};
	/*try {
	}
	catch (std::runtime_error(SDL_GetError())) {

	}*/

	auto renderer = SDLrenderer{window};
	bool running = true;
	
	RenderManager renderManager;
	ResourceImpl resourceImpl(renderer.GetPointer());
	ResourceManager resourceManager(resourceImpl);
	Game game(resourceManager);

	int width = 500; //TODO: const
	int height = 500; //TODO: const
	std::string title = "";
	game.Enter(width, height, title);

	
	float dt = 1.0f / 60.0f; //TODO: magic numbers 60 name as FPS
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{//TODO: switch clarity
			case SDL_QUIT: running = false; break;
			case SDL_KEYDOWN: game.OnKeyDown(TranslateKeyCode(e.key.keysym.sym)); break;
			case SDL_KEYUP: game.OnKeyUp(TranslateKeyCode(e.key.keysym.sym)); break;
			}
		}

		game.Update(dt);
		game.Render(renderManager);

		SDL_SetRenderDrawColor(renderer.GetPointer(),0,0,0,0); //TODO: use struct for the colors
		SDL_RenderClear(renderer.GetPointer());
		for (auto &&entry : renderManager.spriteEntries) //TODO: use for each
		{
			if (entry.sprite.image != nullptr)
			{
				//TO DO: make new function for static_cast
				//TODO: check if the calls can be minimized: entry.sprite.source.x
				SDL_Rect src{ entry.sprite.source.x, entry.sprite.source.y, entry.sprite.source.w, entry.sprite.source.h };
				SDL_Rect dst{ static_cast<int>(entry.trans.position.x),
							  static_cast<int>(entry.trans.position.y),
							  static_cast<int>(entry.sprite.image->width),
							  static_cast<int>(entry.sprite.image->height) };
				SDL_RenderCopy(renderer.GetPointer(), resourceImpl.GetTexture(entry.sprite.image->id), &src, &dst);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer.GetPointer(), entry.sprite.color.r, entry.sprite.color.g, entry.sprite.color.b, entry.sprite.color.a);
				SDL_Rect rect{ static_cast<int>(entry.trans.position.x),
							   static_cast<int>(entry.trans.position.y),
							   entry.sprite.source.w,
							   entry.sprite.source.h };
				SDL_RenderDrawRect(renderer.GetPointer(), &rect);
			}
		}
		for (auto&& entry : renderManager.rectEntries)
		{
			SDL_SetRenderDrawColor(renderer.GetPointer(), entry.color.r, entry.color.g, entry.color.b, entry.color.a);
			SDL_Rect rect{ static_cast<int>(entry.trans.position.x),
						   static_cast<int>(entry.trans.position.y),
						   entry.rect.w,
						   entry.rect.h };
			//SDL_RenderDrawRect(renderer, &rect);	// <- If you want to draw the "outline" of the rectangle.
			SDL_RenderFillRect(renderer.GetPointer(), &rect);  // <- If you want to draw a "filled" rectangle. 
		}
		SDL_RenderPresent(renderer.GetPointer());
		renderManager.Clear();
		SDL_Delay(1000 / 20); //<- "Framerate". //TO DO: name magic numbers, don't use comment 'Framerate'
	}
	
	return 0;
}
