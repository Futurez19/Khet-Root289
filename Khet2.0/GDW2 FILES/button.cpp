#include "button.h"

#include <iostream>

#include "InputManager.h"
#include "ConsoleManager.h"

Button::Button(int x, int y, std::string text) {
	this->x = x;
	this->y = y;
	this->text = text;
}

void Button::drawButton() {
	if (!isPressed()) {
		setCursorPos(this->x - 1, this->y);
		std::wcout << L" " << text.c_str() << L" ";
	}
	else {
		setCursorPos(this->x - 1, this->y);
		std::wcout << L">" << text.c_str() << L"<";
	}
}

bool Button::isPressed() {
	if (this->y == getMouseY() / 16 && getMouseX() / 8 > this->x && getMouseX() / 8 < this->x + text.length())
		return true;
	else return false;
}
