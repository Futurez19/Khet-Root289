#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

#include "InputManager.h"

#define COLS 200
#define ROWS 50

using namespace std;

HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

bool running = true;

int main()
{
	SetConsoleScreenBufferSize(consoleHandle, { COLS, ROWS });
	SMALL_RECT windowSize = { 0, 0, COLS - 1, ROWS - 1 };

	if(!SetConsoleWindowInfo(consoleHandle, TRUE, &windowSize)) {
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
		return -1;
	}

	if(!SetConsoleTitle(L"TEST")) {
		cout << "SetConsoleTitle failed with error " << GetLastError() << endl;
		return -1;
	}

	CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	DWORD prev_mode;
	GetConsoleMode(consoleHandle, &prev_mode);
	SetConsoleMode(consoleHandle, prev_mode & !ENABLE_QUICK_EDIT_MODE);

	while (running) {

		updateButtons();

		if (isButton(Events::Escape)) {
			running = false;
			continue;
		}

		if (isButton(Events::Mouse_Left)) {
			cout << "Hello!";
		}


		// Input Checking //



		// Input Checking //

		// Logic //

		printf("x: %d y: %d\n", getMouseX(), getMouseY());

		Sleep(32);

		system("cls");

		SetConsoleCursorPosition(consoleHandle, { 5, 0 });

		// Logic //
	}
	return 0;
}