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

#define COLS 200
#define ROWS 50

enum State {
	MENU = 0,
	INSTRUCTIONS = 1,
	GAME = 2,
	GAMEOVER = 3
};

void printPiece(Piece piece, int x, int y);

bool running = true;

std::wstring map = L"";

std::vector<Piece> pieceList;

int main()
{
	initConsole(COLS, ROWS);
	setCursorVisibility(false);
	setConsoleWindowTitle("Khet 2.0");
	
	_setmode(_fileno(stdout), _O_U16TEXT);

	State gameState = MENU;
	int count = 0;
	
	std::wstring pieceInfo = readFile("Classic_Start");

	//for (int i = 0, pos = 0; i < pieceInfo.size(); i++) {
	//	Piece tempPiece;
	//	std::wstring temp = pieceInfo.substr(0, pieceInfo.find(L' '));
	//	if (temp == "")

	//}

	map = readFile("board");

	while (running) {

		if (isButton(Events::Escape)) {
			running = false;
			continue;
		}

		// vv Input Checking vv



		// ^^ Input Checking ^^

		// vv Game Logic vv



		// ^^ Game Logic ^^

		// vv Output vv 

		setCursorPos(0, 0);

		//printf("x: %d y: %d           \n", getMouseX(), getMouseY());

		setCursorPos(0, 1);

		std::wcout << map;

		printPiece(pieceList[1], 1, 1);

		while (!isButton(Events::Space));	
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