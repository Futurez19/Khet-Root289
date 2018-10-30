#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "InputManager.h"

//int deflect(laser,piece);

// Scarab Object
class Piece {
public:
	// Initializes base statistics for pieces.
	void initScarab(int, int);
	void initPyramid(int, int);
	void initAnubis(int, int);
	void initSphinx(int, int);
	void initPharoah(int);

	//Piece interactions.
	void rotateCCW();
	void rotateCW();

	//int *move(int,std::vector<Piece>&,unsigned char);

	void loadPieceData(std::string);

	int player; //Which player does this piece belong to? Should be declared upon piece declaration.
	
	bool destroyed = false;	//Not sure how to remove it from board, so just check if destroyed first.

	bool hasMirror = false; // Checks if has mirror

	bool hasLaser = false; // For the sphinx. Otherwise False

	// Denotes what piece it is.
	bool isScarab = false;
	bool isAnubis = false;
	bool isPyramid = false;
	bool isSphinx = false;
	bool isPharoah = false;

	//Checks active mirror intake angles or defense angle.
	bool up = false;	
	bool down = false;
	bool left = false;
	bool right = false;

	int angle; //A int signifying the angle of the mirror , 1 = orient1 , 2 = orient2 etc..
	
    // How the pieces are drawn line by line. includes orientations
	std::wstring Orient1;	//
	std::wstring Orient2;
	std::wstring Orient3;
	std::wstring Orient4;
	
private:
	
};

