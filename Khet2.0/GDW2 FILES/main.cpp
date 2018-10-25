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

#include "InputManager.h"
#include "ConsoleManager.h"
#include "Pieces.h"
#include "Laser.h"

#define COLS 200
#define ROWS 50

std::wstring readFile(const char*);

void printPiece(Piece piece, int x, int y);


bool running = true;

std::wstring map = L"";

int main()
{
	initConsole(COLS, ROWS);
	setCursorVisibility(false);
	setConsoleWindowTitle("Khet 2.0");
	
	_setmode(_fileno(stdout), _O_U16TEXT);

//	CONSOLE_FONT_INFOEX cfi;
//cfi.cbSize = sizeof(cfi);
//cfi.nFont = 0;
//cfi.dwFontSize.X = 12;                   // Width of each character in the font
//cfi.dwFontSize.Y = 12;                  // Height
//cfi.FontFamily = FF_DONTCARE;
//cfi.FontWeight = FW_NORMAL;
//std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
//SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	//Piece sca1;
	//initScarab(sca1, 0, 1);

	//Piece sca2;
	//initScarab(sca2, 0, 2);

	//Piece sca3;
	//initScarab(sca3, 0, 3);

	//Piece sca4;
	//initScarab(sca4, 0, 4);

	map = readFile("board.txt");

	char boardState[100];
	for (int i = 0; i < 100; i++)
		switch (i % 3) {
			case 0:
				boardState[i] = '&';
				break;
			case 1:
				boardState[i] = '#';
				break;
			case 2: 
				boardState[i] = '*';
				break;
		}


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
		//cls();

		//printf("x: %d y: %d           \n", getMouseX(), getMouseY());

		setCursorPos(0, 1);

		std::wcout << map;

		//for (int i = 0; i < 10; i++) {
		//	for (int j = 0; j < 10; j++) {
		//				//setCursorPos(i * 8 + k * 2, j * 4 + l + 1);
		//				switch ((i + j * 10) % 4) {
		//					case 0:
		//						printPiece(sca1, i, j);
		//						break;
		//						case 1:
		//						printPiece(sca2, i, j);
		//						break;
		//						case 2:
		//						printPiece(sca3, i, j);
		//						break;
		//						case 3:
		//						printPiece(sca4, i, j);
		//						break;
		//		}
		//	}
		//}

		while (!isButton(Events::Space));
	
		setCursorPos(COLS, ROWS);
		// ^^ Output ^^
	}
	return 0;
}

// CREDIT: https://stackoverflow.com/questions/4775437/read-unicode-utf-8-file-into-wstring
std::wstring readFile(const char* filename) {
    std::wifstream wif(filename);
    wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}

void printPiece(Piece piece, int x, int y) {
		//for (int i = 1; i <= 3; i++) {
		//	setCursorPos(x * 8 + i * 2, y * 4 + 2);
		//	switch (piece.angle) {
		//		case 1:
		//			std::wcout << piece.line_1Orient1.c_str()[i - 1];
		//			break;
		//			case 2:
		//			std::wcout << piece.line_1Orient2.c_str()[i - 1];
		//			break;
		//			case 3:
		//			std::wcout << piece.line_1Orient3.c_str()[i - 1];
		//			case 4:
		//			std::wcout << piece.line_1Orient4.c_str()[i - 1];
		//			break;
		//	}
		//}

		//for (int i = 1; i <= 3; i++) {
		//	setCursorPos(x * 8 + i * 2, y * 4 + 3);
		//	switch (piece.angle) {
		//		case 1:
		//			std::wcout << piece.line_2Orient1.c_str()[i - 1];
		//			break;
		//			case 2:
		//			std::wcout << piece.line_2Orient2.c_str()[i - 1];
		//			break;
		//			case 3:
		//			std::wcout << piece.line_2Orient3.c_str()[i - 1];
		//			break;
		//			case 4:
		//			std::wcout << piece.line_2Orient4.c_str()[i - 1];
		//			break;
		//	}
		//}

		//for (int i = 1; i <= 3; i++) {
		//	setCursorPos(x * 8 + i * 2, y * 4 + 4);
		//	switch (piece.angle) {
		//		case 1:
		//			std::wcout << piece.line_3Orient1.c_str()[i - 1];
		//			break;
		//		case 2:
		//			std::wcout << piece.line_3Orient2.c_str()[i - 1];
		//			break;
		//			case 3:
		//			std::wcout << piece.line_3Orient3.c_str()[i - 1];
		//			break;
		//			case 4:
		//			std::wcout << piece.line_3Orient4.c_str()[i - 1];
		//			break;
		//	}
		//}
}
