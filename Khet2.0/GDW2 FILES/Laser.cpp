#include <iostream>
#include <vector>

#include "Laser.h"
#include "Pieces.h"
#include "ConsoleManager.h"

bool Laser::nextOccupied(int id)
{
	//bool interaction = false;

	//if (!((board[x + y * 10] - 1) % 13 == 0)) // if the board square is not empty(0)
	//{
	//	interaction = true;
	//}
	//else
	//	interaction = false;

	return (!(id) % 13 == 0);
}

void Laser::deflected(int &direction, Piece& p1)
{
	if (p1.hasMirror)
	{
		switch (direction)//dependant on incoming laser
		{
		case 1:		  //laser is going up;
			if (p1.isScarab) {
				if (p1.angle % 2 == 0) {
					direction = 4;
				}
				else {
					direction = 2;
				}
				break;
			}
			if (p1.down)
			{//first checks that it can recieve the laser
				if (p1.left)//sets the laser's direction depending on resultant mirror
				{
					direction = 2;
				}
				else if (p1.right)
				{
					direction = 4;
				}
				else if (p1.isAnubis || p1.isSphinx)
					break;
				else
					p1.destroyed = true;
			}
			else
			{
				p1.destroyed = true;
				break;
			}
			break;

		case 2:		 // laser going left
			if (p1.isScarab) {
				if (p1.angle % 2 == 0) {
					direction = 1;
				}
				else {
					direction = 3;
				}
				break;
			}
			if (p1.right)
			{//first checks that it can recieve the laser
				if (p1.up)//sets the laser's direction depending on resultant mirror
				{
					direction = 1;
				}
				else if (p1.down)
				{
					direction = 3;
				}
				else if (p1.isAnubis || p1.isSphinx)
					break;
				else
					p1.destroyed = true;
			}
			else
			{
				p1.destroyed = true;
				break;
			}
			break;
		case 3:		 // laser going down
			if (p1.isScarab) {
				if (p1.angle % 2 == 0) {
					direction = 2;
				}
				else {
					direction = 4;
				}
				break;
			}
			if (p1.up)
			{//first checks that it can recieve the laser
				if (p1.left)//sets the laser's direction depending on resultant mirror
				{
					direction = 2;
				}
				else if (p1.right)
				{
					direction = 4;
				}
				else if (p1.isAnubis)
					break;//stop the laser
				else
					p1.destroyed = true;
			}
			else
			{
				p1.destroyed = true;
				break;
			}
			break;
		case 4:		  //laser going right
			if (p1.isScarab) {
				if (p1.angle % 2 == 0) {
					direction = 1;
				}
				else {
					direction = 3;
				}
				break;
			}
			if (p1.left)
			{//first checks that it can recieve the laser
				if (p1.up)//sets the laser's direction depending on resultant mirror
				{
					direction = 1;
				}
				else if (p1.down)
				{
					direction = 3;
				}
				else if (p1.isAnubis)
					break;//stop the laser
				else
					p1.destroyed = true;
			}
			else
			{
				p1.destroyed = true;
				break;
			}
			break;
		}
	}
	else
		p1.destroyed = true;
}




void Laser::fireLaser(Piece sphinx, int board[8][10], std::vector<Piece> pieceList)
{
	this->dir = sphinx.angle;
	this->teamLaser = sphinx.player;

	//int incrementX = 7;	// Im supposed to be incrementing this 1 by to print the laser in the line,
	//int incrementY = 4;

	int startX = this->teamLaser == 0 ? 0 : 9;
	int startY = this->teamLaser == 0 ? 0 : 7;

	bool inBounds = true;
	bool isFiring = true;
	
	int newX = startX, newY = startY;

	while (inBounds && isFiring) {

		if (this->dir % 2 == 0) {
			newX += this->dir == 2 ? -1 : 1;
		}
		else {
			newY += this->dir == 1 ? -1 : 1;
		}

		if (newX < 0 || newX > 9 || newY < 0 || newY > 7) {
			inBounds = false;
			continue;
		}

		if (nextOccupied(board[newY][newX])) {
			deflected(this->dir, pieceList[board[newY][newX] - 1]);
			if (pieceList[board[newY][newX] - 1].destroyed) {
				board[newY][newX] = 0;
				isFiring = false;
			}
			else if (pieceList[board[newY][newX] - 1].isAnubis ||
					 pieceList[board[newY][newX] - 1].isSphinx)
				isFiring = false;
		}

		setCursorPos(newX * 8 + 4, newY * 4 + 3);
		std::wcout << L"-";

	}
}

