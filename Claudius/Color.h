#pragma once

struct Color
{ //TODO: rule of zero/six, or just use SDL color
	unsigned char r, g, b, a;

	Color();
	Color(const Color& rhs);
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
};