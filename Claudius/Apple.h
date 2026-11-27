#pragma once

#include "KeyCode.h"
#include "Rectangle.h"
#include "Color.h"
#include "Transform.h"

struct RenderManager; //<- Kinda like #include "RenderManager.h", not exactly. Can't use functions. Google forward declaration.

struct Apple
{

	Apple();
	void Render(RenderManager& renderManager);
	void Initialize(unsigned int width, unsigned int height);

	Rectangle rect; //TODO: initialize values
	Color color; //TODO: initialize values
	Transform trans; //TODO: initialize values

	bool new_apple = false; //TO DO use setter and getter and make this value private?
};