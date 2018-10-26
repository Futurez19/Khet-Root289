#pragma once
#include <iostream>
#include <string>

class Laser
{
public:

	int dir;   // laser direction, 1-4 : 1 = up, 2 = Left, 3 = Down, 4 = Right.
	
	int posX;
	int posY;

	char beam1 = '|';
	char beam2 = '-';

private:

};