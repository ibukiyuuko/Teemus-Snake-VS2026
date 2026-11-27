#pragma once

struct Rectangle
{
	//TODOL can use struct size() for better accessing rectangle values, instead of writing all of them as paremeters
	int x{}; 
	int y{};
	int w{}; 
	int h{};

	Rectangle();
	Rectangle(const Rectangle& rhs);
	Rectangle(int x, int y, int w, int h);

	void SetBounds(int x, int y, int w, int h);
};