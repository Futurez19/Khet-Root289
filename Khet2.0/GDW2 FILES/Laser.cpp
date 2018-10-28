#include <iostream>
#include <vector>

#include "Laser.h"
#include "Pieces.h"
#include "ConsoleManager.h"

bool Laser::nextOccupied(int x,int y,int* board)
{
	bool interaction = false;

	//if (!((*board[x][y] - 1) % 13 == 0)) // if the board square is not empty(0)
	//{
	//	interaction = true;
	//}
	//else
	//	interaction = false;

	return interaction;
}

void Laser::deflected(int &direction, Piece& p1)
{
	if (p1.hasMirror)
	{
		switch (direction)//dependant on incoming laser
		{
		case 1:		  //laser is going up;

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

		case 2:		 // laser going left

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
		case 3:		 // laser going down
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

		case 4:		  //laser going right
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
		}
	}
	else
		p1.destroyed = true;
}




inline void Laser::fireLaser(Piece sphinx,int* board,std::vector<Piece>pieceList)
{
	this->dir = sphinx.angle;
	this->teamLaser = sphinx.player;


	int incrementX = 7;	// Im supposed to be incrementing this 1 by to print the laser in the line,
	int incrementY = 4;

	bool inBounds = true;
	bool isFiring = true;
	
	
		switch (dir)
		{
		case 1:
			this->posX = 9 * 8 + incrementX; // sets the starting point of the laser,
			this->posY = 7 * 4 + incrementY;


				if (nextOccupied(this->posX, this->posY, board)) // Is there a piece that I'm interacting with?
				{

					//Sorry Myles, i need some help figuring out which piece im getting.
					//What this should do:
					//if the next spot the laser should print to is in encroaching on a occupied square
					//We need to get the piece on that square and pass it to the deflected function 

					/*if ((board[newMouseY][newMouseX] - 1) % 13 == 0)
						std::wcout << "Sphinx";
					else if ((board[newMouseY][newMouseX] - 1) % 13 < 8)
						std::wcout << "Pyramid";
					else if ((board[newMouseY][newMouseX] - 1) % 13 < 10)
						std::wcout << "Scarab";
					else if ((board[newMouseY][newMouseX] - 1) % 13 < 12)
						std::wcout << "Anubis";
					else if ((board[newMouseY][newMouseX] - 1) % 13 < 14)
						std::wcout << "Pharoah";*/

					


					//deflected(this->dir, pieceList.at(piece));
				}
				else// if empty just print the laser at the spot
				{
					setCursorPos(posX, posY);
					std::wcout << this->beam1;

				}

			break;
		case 2:

			break;

		case 3:

			break;

		case 4:

			break;
		}

	
}

