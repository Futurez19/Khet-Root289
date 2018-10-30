#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Pieces.h"

class Laser
{
public:

	void fireLaser(Piece,int[8][10],std::vector<Piece>);
	bool nextOccupied(int);
	void deflected(int&,Piece&);

	int dir;   // laser direction, 1-4 : 1 = up, 2 = Left, 3 = Down, 4 = Right.
	
	int posX;
	int posY;
	int teamLaser;

	char beam1 = '|'; // up or down
	char beam2 = '-'; // left or right

private:

};