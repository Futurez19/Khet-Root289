#include <iostream>
#include <string>
#include "Pieces.h"
using namespace std;

Piece selectPiece();
void movePiece(Piece);

Piece piece;

//int main()
//{
//	selectPiece();
//	movePiece(piece);
//	return 0;
//}

Piece selectPiece()
{
	//this section needs to be changed depending on how pieces are named
	string token;
	Piece piece;

	cout << "Enter the piece's name and number to pick it" << std::endl; //ex. Scarab1
	cin >> token;

	/*
	//run a while loop until the piece selected is valided
	while (token!= enemy token or immovable token)
	{
		//cout<< "Invalid input, enter a valid piece <<std::endl;
		cin >> token;
	}

	//selected piece is now valid

	//either do this long repetitive way of typing a lot of if statements
	if ( token=="Scarab1")
	{
		piece = the 1st scarab
	}
	else if (token=="Scarab2")
	{
		piece = the 2nd scarab
	}
	//or something else more efficient I can't figure out

	*/

	//returns the selected piece
	return piece;
}

void movePiece(Piece token)
{
	int xVal;
	int yVal;

	cout << "Enter the x coordinate" << std::endl;
	cin >> xVal;
	cout << "Enter the y coordinate" << std::endl;
	cin >> yVal;

	//check if spots are available based on if:
	//space is occupied 
	//token can move to that space
	/*
	if (board[x][y].occupied==true)
	{
		//space not available, try again
	}
	else if (x and y > amount that the piece can move)
	{
		//can't reach space, try again
	}
	else
	{
		//movement is valid

		//make the old space unoccupied
		board[token.x][token.y].setOccupiedFalse;

		//and make the new space occupied
		board[xVal][yVal].setOccupiedTrue;

		//change the piece's x and y coordinates to new space
		token.x = xVal;
		token.y = yVal;
	}
	*/
}