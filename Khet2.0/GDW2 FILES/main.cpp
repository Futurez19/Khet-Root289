#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <random>

#include <io.h>
#include <fcntl.h>

#include <sstream>
#include <fstream>
#include <codecvt>

#include <cwchar>

#include "InputManager.h"
#include "ConsoleManager.h"
#include "Pieces.h"
#include "button.h"

#define COLS 150
#define ROWS 40

void printPiece(Piece piece, int x, int y);

bool running = true;

std::wstring map = L"";

// List that contains all of the piece objects
std::vector<Piece> pieceList(26);

std::wstring menu;

bool doUpdate = true;

int currentId = 0;

enum State {
	MENU = 0,
	INSTRUCT = 1,
	GAME = 2
};

State state = MENU;

void changeGameState(State newState) {
	if (state = newState) return;
	state = newState;
	currentId = 0;
	doUpdate = true;
	system("cls");
}

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
	{6,0,10,0,21,10,20,0,0,0},
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

int main()
{
	// Initialize console settings
	initConsole(COLS, ROWS);
	setCursorVisibility(false);
	setConsoleWindowTitle("Khet 2.0");

	// Enable Unicode Functionality
	_setmode(_fileno(stdout), _O_U16TEXT);


	// Get the image for the board
	map = readFile("board");

	menu = readFile("menu");



	int newMouseX, newMouseY;


	bool isSpace = false;

	Button b1(41, 17, "Classic Mode"),
		b2(41, 18, "Dynasty Mode"),
		b3(41, 19, "Imhotep Mode"),
		b4(34, 20, "Instructions / How to Play");

	Button g1(95, 5, "Rotate ClockWise"),
		g2(95, 7, "Rotate CounterClockWise");


	while (running) {

		// if escape is pressed, close the program
		if (isButton(Events::Escape)) {
			changeGameState(MENU);
		}

		// vv Input Checking vv

		// Convert mouse coords into game board coords
		newMouseX = (getMouseX() - 4) / 64;
		newMouseY = (getMouseY() - 24) / 64;

		// INPUT FOR MENU
		if (state == MENU) {
			//if (b1.isPressed())|| b2.isPressed() || b3.isPressed()) state = GAME;
			if (b1.isPressed()) {
				initBoard(1);
				initPieces();
				changeGameState(GAME);
			}
			else if (b2.isPressed()) {
				initBoard(2);
				initPieces();
				changeGameState(GAME);
			}
			else if (b3.isPressed()) {
				initBoard(3);
				initPieces();
				changeGameState(GAME);
			}
			else if (b4.isPressed()) changeGameState(INSTRUCT);
		}
		// INPUT FOR MENU


		// LOGIC FOR GAME
		// If the mouse is over a valid piece and the user clicks the left mouse button,
		// print that piece in white, with the background indicating it's colour

		else if (state == GAME) {
			if (isButton(Events::Mouse_Left)) {
				int temp = board[newMouseY][newMouseX];
				if (newMouseX >= 0 && newMouseX < 10 && newMouseY >= 0 && newMouseY < 8 &&
					temp != currentId && temp > 0 && temp <= 26) {
					currentId = board[newMouseY][newMouseX];
					doUpdate = true;
				}
				//else if (!g1.isPressed() && !g2.isPressed())
				//	currentId = 0;
			}

			if (currentId > 0) {
				if (g1.isPressed()) {
					pieceList[currentId - 1].rotateCW();
					doUpdate = true;
				}
				else if (g2.isPressed()) {
					pieceList[currentId - 1].rotateCCW();
					doUpdate = true;
				}
			}
		}
		// INPUT FOR GAME

		// ^^ Input Checking ^^

		// vv Game Logic vv



		// ^^ Game Logic ^^

		// vv Output vv 

		setCursorPos(0, 1);

		// Print the menu
		if (state == MENU) {
			std::wcout << menu;
			b1.drawButton();
			b2.drawButton();
			b3.drawButton();
			b4.drawButton();
		}

		// Start of in game state printing
		// Only draw the map if something has changed
		else if (state == GAME) {
			if (doUpdate) {
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
				doUpdate = false;
			}

			// Testing out checking grid with the mouse
			setCursorPos(COLS - 20, ROWS - 2);
			std::wcout << newMouseX << " " << newMouseY << "              ";
			setCursorPos(COLS - 10, ROWS - 2);
			if (newMouseX > -1 && newMouseX < 10 && newMouseY > -1 && newMouseY < 8) {
				if ((board[newMouseY][newMouseX] - 1) % 13 == 0)
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

			if (currentId > 0) {
				g1.drawButton();
				g2.drawButton();
			}
		}
		// End of in game state printing


		setCursorPos(COLS, ROWS);
		// ^^ Output ^^
	}
	return 0;
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



//	CONSOLE_FONT_INFOEX cfi;
//cfi.cbSize = sizeof(cfi);
//cfi.nFont = 0;
//cfi.dwFontSize.X = 12;                   // Width of each character in the font
//cfi.dwFontSize.Y = 12;                  // Height
//cfi.FontFamily = FF_DONTCARE;
//cfi.FontWeight = FW_NORMAL;
//std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
//SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);