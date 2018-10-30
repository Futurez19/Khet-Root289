#include "Pieces.h"

#include "ConsoleManager.h"

#include <io.h>
#include <fcntl.h>

#include <sstream>
#include <fstream>
#include <codecvt>

using namespace Events;

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