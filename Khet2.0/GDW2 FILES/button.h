#pragma once

#include <string>

class Button
{
public:
	Button(int, int, std::string);

	void drawButton();

	bool isOver();

	bool isPressed();

	int getX() { return x; }
	int getY() { return y; }
	std::string getText() { return text; }
	
private:
	int x, y;

	std::string text;
};

