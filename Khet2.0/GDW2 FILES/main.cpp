#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <io.h>
#include <fcntl.h>

#include <sstream>
#include <fstream>
#include <codecvt>

#include <cwchar>

#include <ctime>

#include "InputManager.h"
#include "ConsoleManager.h"
#include "Pieces.h"
#include "button.h"
#include "Laser.h"


#define COLS 150
#define ROWS 50

enum State {
	MENU = 0,
	INSTRUCT = 1,
	GAME = 2,
	WIN = 3
};

void changeGameState(State);
void initBoard(int);
void initPieces();
void drawBoard();
void printPiece(Piece piece, int x, int y);
bool movePiece();
void switchTurns();


bool running = true;

std::wstring map = L"";
std::wstring menu;
std::wstring instructions;

// List that contains all of the piece objects
std::vector<Piece> pieceList(26);

bool doUpdate = true;

int currentId = 0;
int turn = 1;
bool doTurnSwap = false;

State state = MENU;

// Classic board setup
// the pieces are listed from 1 to 26
// 1 & 14 = sphinx
// 2 - 8 & 15 - 21 = pyramid
// 9 - 10 & 22 - 23 = scarab
// 11 - 12 & 24 - 25 = anubis
// 13 & 26 = pharoah
int board[8][10];

int classicBoard[8][10] = {
	{1,0,0,0,11,13,12,5,0,0},
	{0,0,4,0,0,0,0,0,0,0},
	{0,0,0,21,0,0,0,0,0,0},
	{2,0,20,0,9,10,0,6,0,16},
	{3,0,19,0,23,22,0,7,0,15},
	{0,0,0,0,0,0,8,0,0,0},
	{0,0,0,0,0,0,0,17,0,0},
	{0,0,18,25,26,24,0,0,0,14} };

int dynastyBoard[8][10] = {
	{1,0,0,0,2,11,3,0,0,0},
	{0,0,0,0,0,13,0,0,0,0},
	{4,0,0,0,5,12,9,0,0,0},
	{6,0,10,0,21,0,20,0,0,0},
	{0,0,0,7,0,8,0,23,0,19},
	{0,0,0,22,25,18,0,0,0,17},
	{0,0,0,0,26,0,0,0,0,0},
	{0,0,0,16,24,15,0,0,0,14} };

int imhotepBoard[8][10] = {
	{1,0,0,0,11,13,12,10,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,21,0,0,2,0,0,0},
	{3,20,0,0,19,9,0,0,4,18},
	{5,17,0,0,23,6,0,0,7,16},
	{0,0,0,15,0,0,8,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,22,25,26,24,0,0,0,14} };

// Array that holds the direction information for the pieces.
// The piece numbering is set up so that the second team's directions
// can just be mirrors of the first team's directions
int boardDir[13];

int classicDir[13] = { 3, 1, 4, 3, 4, 4, 1, 4, 1, 2, 3, 3, 3 };

int dynastyDir[13] = { 3, 3, 4, 1, 3, 4, 2, 4, 2, 1, 3, 3, 3 };

int imhotepDir[13] = { 3, 1, 1, 4, 4, 2, 1, 4, 2, 2, 3, 3, 3 };


// Main function, execution starts here
int main()
{
	// Initialize console settings
	initConsole(COLS, ROWS);
	setCursorVisibility(false);
	setConsoleWindowTitle("Khet 2.0");

	// Enable Unicode Functionality
	_setmode(_fileno(stdout), _O_U16TEXT);


	// Get the image for the board and the menu
	map = readFile("board");

	menu = readFile("menu");

	instructions = readFile("khet rules");

	int newMouseX, newMouseY;

	// Initialize buttons
	Button m1(41, 17, "Classic Mode"),
		m2(41, 18, "Dynasty Mode"),
		m3(41, 19, "Imhotep Mode"),
		m4(34, 20, "Instructions / How to Play");

	Button g1(95, 7, "Rotate ClockWise (Right)"),
		g2(95, 5, "Rotate CounterClockWise (Left)");

	Button i1(30, 1, "Back to Menu");

	Button w1(30, 1, "Back to Menu");

	Laser laser;

	bool doLaser = true;

	auto bTime = clock();
	bool doTime = false;

	// Main Game Loop
	while (running) {
		// if escape is pressed, Go back to the menu and uninitialize all data
		if (isButton(Events::Escape)) {
			changeGameState(MENU);
		}

		// vv Input Checking vv

		// Convert mouse coords into game board coords
		newMouseX = (getMouseX() - 4) / 64;
		newMouseY = (getMouseY() - 24) / 64;

		// INPUT FOR MENU

		// Menu button checking
		if (state == MENU) {
			if (m1.isPressed()) {
				initBoard(1);
				changeGameState(GAME);
			}
			else if (m2.isPressed()) {
				initBoard(2);
				changeGameState(GAME);
			}
			else if (m3.isPressed()) {
				initBoard(3);
				changeGameState(GAME);
			}
			else if (m4.isPressed()) changeGameState(INSTRUCT);

			if (state == GAME) {
				initPieces(); 
				turn = 1;
			}
		}

		else if (state == INSTRUCT) {
			if (i1.isPressed()) changeGameState(MENU);
		}

		else if (state == WIN) {
			if (w1.isPressed()) changeGameState(MENU);
		}

		// INPUT FOR MENU


		// LOGIC FOR GAME
		// If the mouse is over a valid piece and the user clicks the left mouse button,
		// print that piece in white, with the background indicating it's colour

		else if (state == GAME) {

			// If the user clicks on a valid piece, select it
			if (isButton(Events::Mouse_Left)) {
				int temp = board[newMouseY][newMouseX];
				if (newMouseX >= 0 && newMouseX < 10 && newMouseY >= 0 && newMouseY < 8 &&
					temp != currentId && temp > 0 && temp <= 26) {
					currentId = board[newMouseY][newMouseX];

					if (turn == 1) currentId = currentId < 14 ? currentId : 0;
					else currentId = currentId >= 14 ? currentId : 0;

					if (currentId != 0)
						doUpdate = true;
				}
			}

			movePiece();

			// Check for user clicking rotation buttons
			if (currentId > 0) {
				if (g1.isPressed()) {
					pieceList[currentId - 1].rotateCW();

					switchTurns();
				}
				else if (g2.isPressed()) {
					pieceList[currentId - 1].rotateCCW();

					switchTurns();
				}

			}
		}
		// INPUT FOR GAME


		// ^^ Input Checking And Logic ^^

		// vv Output vv 

		setCursorPos(0, 1);

		// Print the menu and the buttons
		if (state == MENU) {
			setConsoleColour(Colour::White);
			std::wcout << menu;
			m1.drawButton();
			m2.drawButton();
			m3.drawButton();
			m4.drawButton();

			std::wcout << L"\n\n\n\n\nNote: To allow mouse input,\n1. Right click the top of the console Window and go to properties.\n2. Uncheck the \"Quick Edit\" box and return to the game. \n3. Your mouse input should work.";
		}


		else if (state == INSTRUCT)
		{
			//setCursorPos(0, 1);
			setConsoleColour(Colour::White);
			std::wcout << instructions;
			i1.drawButton();
		}

		// Start of in game state printing
		// Only draw the map if something has changed
		else if (state == GAME) {
			if (doUpdate) {
				drawBoard();
				doUpdate = false;
			}

			// Testing out checking grid with the mouse
			setCursorPos(COLS - 20, ROWS - 4);
			if (turn == 1)
			{
				std::wcout << "Red's Move..";
			}
			else
			{
				std::wcout << "Blue's Move..";
			}
			setCursorPos(COLS - 20, ROWS - 2);
			std::wcout << newMouseX << " " << newMouseY << "              ";
			setCursorPos(COLS - 15, ROWS - 2);
			if (newMouseX > -1 && newMouseX < 10 && newMouseY > -1 && newMouseY < 8) {
				if (board[newMouseY][newMouseX] == 0)
					std::wcout << "Blank Space";
				else if ((board[newMouseY][newMouseX] - 1) % 13 == 0)
					std::wcout << "Sphinx";
				else if ((board[newMouseY][newMouseX] - 1) % 13 < 8)
					std::wcout << "Pyramid";
				else if ((board[newMouseY][newMouseX] - 1) % 13 < 10)
					std::wcout << "Scarab";
				else if ((board[newMouseY][newMouseX] - 1) % 13 < 12)
					std::wcout << "Anubis";
				else if ((board[newMouseY][newMouseX] - 1) % 13 < 14)
					std::wcout << "Pharoah";
			}
			else std::wcout << "Invalid";


			// If a piece is selected, draw the control buttons
			setConsoleColour(Colour::White);
			if (currentId > 0) {
				g1.drawButton();
				g2.drawButton();
			}

			if (doTurnSwap) {
				if (doLaser) {
					laser.fireLaser(pieceList[turn == 2 ? 0 : 13], board, pieceList);
					bTime = clock();
					doTime = true;
					doTurnSwap = false;
				}
				doLaser = false;
			}
			else doLaser = true;
			if (doTime && (float)(clock() - bTime) / (float)CLOCKS_PER_SEC > 2) {
				doTime = false;
				//switchTurns();
				doUpdate = true;
				if (pieceList[12].destroyed || pieceList[25].destroyed) 
					changeGameState(WIN);
			}
		}

		else if (state == WIN) {
			if (doUpdate) {
				setCursorPos(0, 5);

				std::wstring lmao = readFile("p1win");
				std::wstring lmao2 = readFile("p2win");

				if (pieceList[12].destroyed) {
					std::wcout << lmao;
				}
				else
				{
					std::wcout << lmao2;
				}
				w1.drawButton();
			}
		}
	// End of in game state printing

	// Effectively hide the cursor
		setCursorPos(COLS, ROWS);
		// ^^ Output ^^
	}
	return 0;
}

// Change the game state and modify variables to refelect the change
void changeGameState(State newState) {
	if (state == newState) return;
	state = newState;
	currentId = 0;
	doUpdate = true;
	system("cls");
}

// initialize the correct board configuration into the working board array
void initBoard(int num) {
	switch (num) {
		case 1:
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 8; j++) {
					board[j][i] = classicBoard[j][i];
				}
			for (int i = 0; i < 13; i++)
				boardDir[i] = classicDir[i];
			break;
		case 2:
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 8; j++) {
					board[j][i] = dynastyBoard[j][i];
				}
			for (int i = 0; i < 13; i++)
				boardDir[i] = dynastyDir[i];
			break;
		case 3:
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 8; j++) {
					board[j][i] = imhotepBoard[j][i];
				}
			for (int i = 0; i < 13; i++)
				boardDir[i] = imhotepDir[i];
			break;
	}
}

// Load the array of pieces
void initPieces() {
	// Initialize the different pieces based on their id
	for (int i = 0; i < 26; i++) {
		if (i % 13 == 0)
			pieceList[i].initSphinx(i < 13 ? 0 : 1, i < 13 ? boardDir[i] : (boardDir[i % 13] + 1) % 4 + 1);
		else if (i % 13 < 8)
			pieceList[i].initPyramid(i < 13 ? 0 : 1, i < 13 ? boardDir[i] : (boardDir[i % 13] + 1) % 4 + 1);
		else if (i % 13 < 10)
			pieceList[i].initScarab(i < 13 ? 0 : 1, i < 13 ? boardDir[i] : (boardDir[i % 13] + 1) % 4 + 1);
		else if (i % 13 < 12)
			pieceList[i].initAnubis(i < 13 ? 0 : 1, i < 13 ? boardDir[i] : (boardDir[i % 13] + 1) % 4 + 1);
		else if (i % 13 < 14)
			pieceList[i].initPharoah(i < 13 ? 0 : 1);
	}
}

void drawBoard() {
	setConsoleColour(Colour::White);
	std::wcout << map;

	// Print out the board pieces
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j] > 0) {
				if (board[i][j] == currentId)
					setConsoleColour(pieceList.at(board[i][j] - 1).player == 0 ? Colour::WhiteRedBack : Colour::WhiteBlueBack);
				else
					setConsoleColour(pieceList.at(board[i][j] - 1).player == 0 ? Colour::Red : Colour::Blue);
				printPiece(pieceList.at(board[i][j] - 1), j, i);
			}
		}
	}
}

void printPiece(Piece piece, int x, int y) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			setCursorPos(x * 8 + i * 2, y * 4 + j + 1);
			int index = (i - 1) + (j - 1) * 3;
			switch (piece.angle) {
				case 1:
					std::wcout << piece.Orient1[index < piece.Orient1.size() ? index : 0];
					break;
				case 2:
					std::wcout << piece.Orient2[index < piece.Orient2.size() ? index : 0];
					break;
				case 3:
					std::wcout << piece.Orient3[index < piece.Orient3.size() ? index : 0];
					break;
				case 4:
					std::wcout << piece.Orient4[index < piece.Orient4.size() ? index : 0];
					break;
			}
		}
	}

	// Colour in the spaces in between the pieces if the piece is selected
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			setCursorPos(x * 8 + i * 2 + 1, y * 4 + j + 2);
			std::wcout << L' ';
		}
	}
}

bool inBounds(int x, int y) {
	if (x < 0 || y < 0 || x > 9 || y > 7) return false;
	else return true;
}

bool movePiece() {
	if (isButton(Events::NumPad1)) // Movement Downward-Left
	{
		int x, y = 0;

		if (currentId && !(currentId == 1) && !(currentId == 14))	  // if something is selected THAT IS NOT A SPHINX
		{

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (currentId == board[i][j]) // Finds pieces location on the board
					{
						y = i;
						x = j;

						if (inBounds(x - 1, y + 1) && board[y + 1][x - 1] == 0)  //if there is nothing in the way.
						{
							board[y + 1][x - 1] = board[y][x];
							board[y][x] = 0;
							doUpdate = true;

							switchTurns();

							currentId = 0;
							return true;
						}
						else {
							//currentId = 0;
							return false;
						}

					}
				}
			}
		}
	}

	if (isButton(Events::NumPad2)) // Movement Downward
	{
		int x, y = 0;

		if (currentId && !(currentId == 1) && !(currentId == 14))	  // if something is selected
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (currentId == board[i][j]) // Finds pieces location on the board
					{
						y = i;
						x = j;

						if (inBounds(x, y + 1) && board[y + 1][x] == 0)  //if there is nothing in the way.
						{
							board[y + 1][x] = board[y][x];
							board[y][x] = 0;
							doUpdate = true;

							switchTurns();

							currentId = 0;
							return true;
						}
						else {
							//currentId = 0;
							return false;
						}

					}
				}
			}
		}
	}

	if (isButton(Events::NumPad3)) // Movement Downward-Right
	{
		int x, y = 0;

		if (currentId && !(currentId == 1) && !(currentId == 14))	  // if something is selected
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (currentId == board[i][j]) // Finds pieces location on the board
					{
						y = i;
						x = j;

						if (inBounds(x + 1, y + 1) && board[y + 1][x + 1] == 0)  //if there is nothing in the way.
						{
							board[y + 1][x + 1] = board[y][x];
							board[y][x] = 0;
							doUpdate = true;

							switchTurns();

							currentId = 0;
							return true;
						}
						else {
							//currentId = 0;
							return false;
						}

					}
				}
			}
		}
	}

	if (isButton(Events::NumPad4)) // Movement Left
	{
		int x, y = 0;

		if (currentId && !(currentId == 1) && !(currentId == 14))	  // if something is selected
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (currentId == board[i][j]) // Finds pieces location on the board
					{
						y = i;
						x = j;

						if (inBounds(x - 1, y) && board[y][x - 1] == 0)  //if there is nothing in the way.
						{
							board[y][x - 1] = board[y][x];
							board[y][x] = 0;
							doUpdate = true;

							switchTurns();

							currentId = 0;
							return true;
						}
						else {
							//currentId = 0;
							return false;
						}

					}
				}
			}
		}
	}

	if (isButton(Events::NumPad6)) // Movement Right
	{
		int x, y = 0;

		if (currentId && !(currentId == 1) && !(currentId == 14))	  // if something is selected
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (currentId == board[i][j]) // Finds pieces location on the board
					{
						y = i;
						x = j;

						if (inBounds(x + 1, y) && board[y][x + 1] == 0)  //if there is nothing in the way.
						{
							board[y][x + 1] = board[y][x];
							board[y][x] = 0;
							doUpdate = true;

							switchTurns();

							currentId = 0;
							return true;
						}
						else {
							//currentId = 0;
							return false;
						}
					}
				}
			}
		}
	}

	if (isButton(Events::NumPad7))	// Movement Upward-Left
	{
		int x, y = 0;

		if (currentId > 0 && !(currentId == 1) && !(currentId == 14))	  // if something is selected
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (currentId == board[i][j]) // Finds pieces location on the board
					{
						y = i;
						x = j;

						if (inBounds(x - 1, y - 1) && board[y - 1][x - 1] == 0)  //if there is nothing in the way.
						{
							board[y - 1][x - 1] = board[y][x];
							board[y][x] = 0;
							doUpdate = true;

							switchTurns();

							currentId = 0;
							return true;
						}
						else {
							//currentId = 0;
							return false;
						}

					}
				}
			}
		}
	}

	if (isButton(Events::NumPad8)) // Movement Upward
	{
		int x, y = 0;

		if (currentId > 0 && !(currentId == 1) && !(currentId == 14))	  // if something is selected
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (currentId == board[i][j]) // Finds pieces location on the board
					{
						y = i;
						x = j;

						if (inBounds(x, y - 1) && board[y - 1][x] == 0)  //if there is nothing in the way.
						{
							board[y - 1][x] = board[y][x];
							board[y][x] = 0;
							doUpdate = true;

							switchTurns();

							currentId = 0;
							return true;
						}
						else {
							//currentId = 0;
							return false;
						}

					}
				}
			}
		}
	}

	if (isButton(Events::NumPad9))	// Movement Upward-Right
	{
		int x, y = 0;

		if (currentId > 0 && !(currentId == 1) && !(currentId == 14))	  // if something is selected
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (currentId == board[i][j]) // Finds pieces location on the board
					{
						y = i;
						x = j;

						if (inBounds(x + 1, y - 1) && board[y - 1][x + 1] == 0)  //if there is nothing in the way.
						{
							board[y - 1][x + 1] = board[y][x];
							board[y][x] = 0;
							doUpdate = true;

							switchTurns();

							currentId = 0;
							return true;
						}
						else {
							//currentId = 0;
							return false;
						}

					}
				}
			}
		}
	}
	return false;
}

void switchTurns() {
	turn = turn == 1 ? 2 : 1;
	currentId = 0;
	doUpdate = true;
	doTurnSwap = true;
}