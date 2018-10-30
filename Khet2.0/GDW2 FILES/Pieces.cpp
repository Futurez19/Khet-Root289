#include "Pieces.h"

#include "ConsoleManager.h"

#include <io.h>
#include <fcntl.h>

#include <sstream>
#include <fstream>
#include <codecvt>

// Mostly Function definitions

void Piece::initScarab(int team, int angle)
{
	this->isScarab = true;
	this->player = team;

	this->hasMirror = true;
	this->angle = angle;

	this->up = true;
	this->down = true;
	this->left = true;
	this->right = true;

	this->loadPieceData("scarab");
}

void Piece::initPyramid(int team, int angle)
{
	this->isPyramid = true;
	this->player = team;
	this->hasMirror = true;
	this->angle = angle;
	
	switch (this->angle)
	{
	 case 1:
		 this->up = true;
		 this->down = false;
		 this->left = false;
		 this->right = true;
		break;
	 case 2:
		 this->up = true;
		 this->down = false;
		 this->left = true;
		 this->right = false;
		 break;
	 case 3:
		 this->up = false;
		 this->down = true;
		 this->left = true;
		 this->right = false;
		 break;
	 case 4:
		 this->up = false;
		 this->down = true;
		 this->left = false;
		 this->right = true;
		 break;
	 default:
		 std::cout << "OOF something broke.";
		 
	}

	this->loadPieceData("pyramid");

}

void Piece::initAnubis(int team, int angle)
{
	this->isAnubis = true;
	this->player = team;
	this->hasMirror = true; // it doesnt actually have a mirror
	this->angle = angle;

	switch (this->angle)
	{
	case 1:
		this->up = true;
		this->down = false;
		this->left = false;
		this->right = true;
		break;
	case 2:
		this->up = false;
		this->down = false;
		this->left = true;
		this->right = false;
		break;
	case 3:
		this->up = false;
		this->down = true;
		this->left = false;
		this->right = false;
		break;
	case 4:
		this->up = false;
		this->down = false;
		this->left = false;
		this->right = true;
		break;
	default:
		std::cout << "OOF something broke.";

	}

	this->loadPieceData("anubis");

}

void Piece::initSphinx(int team, int angle)
{
	this->isSphinx = true;
	this->player = team;
	this->hasMirror = false;
	this->hasLaser = true;
	this->angle = angle;

	switch (this->angle)
	{
	case 1:
		this->up = true;
		this->down = true;
		this->left = true;
		this->right = true;
		break;
	case 2:
		this->up = true;
		this->down = true;
		this->left = true;
		this->right = true;
		break;
	case 3:
		this->up = true;
		this->down = true;
		this->left = true;
		this->right = true;
		break;
	case 4:
		this->up = true;
		this->down = true;
		this->left = true;
		this->right = true;
		break;
	default:
		std::cout << "OOF something broke.";

	}


	this->loadPieceData("sphinx");
}

void Piece::initPharoah(int team)
{
	this->isPharoah = true;
	this->player = team;
	this->hasMirror = false;
	this->angle = 1;

	this->up = false;
	this->down = false;
	this->left = false;
	this->right = false;

	this->loadPieceData("pharoah");

}

void Piece::rotateCCW()
{	
	if (!(this->angle == 4))
	{
		this->angle += 1;
	}
	else
		this->angle = 1;

	//switch (this->angle)  // may not even need this but just incase
	//{
	//case 1:
	//	//redraw the piece with Orient 1
	//	break;
	//case 2:
	//	//redraw the piece with Orient 2
	//	break;
	//case 3:
	//	//redraw the piece with Orient 3
	//	break;
	//case 4:
	//	//redraw the piece with Orient 4
	//	break;
	//}
	if (this->isPyramid)
		this->initPyramid(this->player, this->angle);
	else if (this->isScarab)
		this->initScarab(this->player, this->angle);
	else if (this->isAnubis)
		this->initAnubis(this->player, this->angle);
	else if (this->isPharoah)
		this->initPharoah(this->player);
	else if (this->isSphinx)
		this->initSphinx(this->player, this->angle);
}

void Piece::rotateCW()
{
	if (!(this->angle == 1))
	{
		this->angle -= 1;
	}
	else
		this->angle = 4;

	//switch (this->angle)
	//{
	//case 1:
	//	//redraw the piece with Orient 1
	//	break;
	//case 2:
	//	//redaw the piece with Orient 2
	//	break;
	//case 3:
	//	//redraw the piece with Orient 3
	//	break;
	//case 4:
	//	//redraw the piece with Orient 4
	//	break;
	//}
	if (this->isPyramid)
		this->initPyramid(this->player, this->angle);
	else if (this->isScarab)
		this->initScarab(this->player, this->angle);
	else if (this->isAnubis)
		this->initAnubis(this->player, this->angle);
	else if (this->isPharoah)
		this->initPharoah(this->player);
	else if (this->isSphinx)
		this->initSphinx(this->player, this->angle);
}

void Piece::loadPieceData(std::string title) {
	std::wstring temp = readFile(title);
	for (int i = 0, count = 0; i < temp.size(); i++) {
		if (temp[i] == '\n') {
			count++;
			continue;
		}
		switch (count) {
			case 0:
				this->Orient1 += temp[i];
				break;
			case 1:
				this->Orient2 += temp[i];
				break;
			case 2:
				this->Orient3 += temp[i];
				break;
			case 3:
				this->Orient4 += temp[i];
				break;
		}
	}
}



//Needs a laser class//obj//struct that has a variable that represents it's direct.
//In this case i used 1-4 to represent the cardinal directions. (1 = up / 2 = left / 3 = down / 4 = right)
//I apologize for the messy switches.

//int deflect(Laser laser, Piece p1)
//{
	//if (p1.hasMirror)
	//{
	//	switch (laser.angle)//dependant on incoming laser
	//	{
	//	case 1:		  //laser is going up;

	//		if (p1.down)
	//		{//first checks that it can recieve the laser
	//			if (p1.left)//sets the laser's direction depending on resultant mirror
	//			{
	//				laser.angle = 2;
	//			}
	//			else if (p1.right)
	//			{
	//				laser.angle = 4;
	//			}
	//			else if (p1.isAnubis)
	//				stop();//stop the laser
	//			else
	//				// piece dies
	//		}
	//		else
	//			//piece dies

	//		break;
	//	case 2:		 // laser going left

	//		if (p1.right)
	//		{//first checks that it can recieve the laser
	//			if (p1.up)//sets the laser's direction depending on resultant mirror
	//			{
	//				laser.angle = 1;
	//			}
	//			else if (p1.down)
	//			{
	//				laser.angle = 3;
	//			}
	//			else if (p1.isAnubis || p1.isSphinx)
	//				stop();//stop the laser
	//			else
	//				// piece dies
	//		}
	//		else
	//			//piece dies
	//		break;
	//	case 3:		 // laser going down
	//		if (p1.up)
	//		{//first checks that it can recieve the laser
	//			if (p1.left)//sets the laser's direction depending on resultant mirror
	//			{
	//				laser.angle = 2;
	//			}
	//			else if (p1.right)
	//			{
	//				laser.angle = 4;
	//			}
	//			else if (p1.isAnubis)
	//				stop();//stop the laser
	//			else
	//				// piece dies
	//		}
	//		else
	//			//piece dies
	//		break;
	//	case 4:		  //laser going right
	//		if (p1.left)
	//		{//first checks that it can recieve the laser
	//			if (p1.up)//sets the laser's direction depending on resultant mirror
	//			{
	//				laser.angle = 1;
	//			}
	//			else if (p1.down)
	//			{
	//				laser.angle = 3;
	//			}
	//			else if (p1.isAnubis)
	//				stop();//stop the laser
	//			else
	//				// piece dies
	//		}
	//		else
	//			//piece dies
	//		break;
	//	}
 //   }
	//else
	//	//piece dies

//}
