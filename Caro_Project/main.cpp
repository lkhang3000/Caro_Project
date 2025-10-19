#include "View.h"
#include "Model_2ends.h"
#include "Control.h"
#include "Globals.h"
#include <iostream>
#include <cctype>
using namespace std;

int main() {
	FixConsoleWindow();
	int x = 0, y = 0;
	if (mainScreen(x, y) == 0) return 0;

	StartGame();
	bool validEnter = true;
	while (1)
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27)
		{
			ExitGame();
			return 0;
		}
		else {
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 13) {
				switch (CheckBoard(_X, _Y)) {
				case -1:
					cout << "X"; break;
				case 1:
					cout << "O"; break;
				case 0: validEnter = false;
				}
				if (validEnter == true) {
					switch (ProcessFinish(TestBoard_BlockedTwoEnds())) {
					case -1: case 1: case 0:
						if (AskContinue() != 'Y') {
							ExitGame(); 
							return 0;
						}
						else StartGame();
					}
				}
				validEnter = true;

			}
		}
	}
	return 0;
}