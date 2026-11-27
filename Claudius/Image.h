#pragma once

struct Image
{
	//TODO: there is no texture, rid of it
	Image();
	Image(const Image& rhs);
	Image(unsigned int id, int width, int height);

	unsigned int id; //TODO: initialize values
	int width; //TODO: initialize values
	int height; //TODO: initialize values

	unsigned int GetID();
	int GetWidth();
	int GetHeight();
};