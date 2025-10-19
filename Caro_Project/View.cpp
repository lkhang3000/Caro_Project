#include "View.h"
#include "Model_2ends.h"
#include "Globals.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

int mainScreen(int& x, int& y) {

	bool valid;

	const int top = 18;
	const int left = 55;

	x = top;
	y = left;

	system("cls");

	GotoXY(55, 18);
	cout << "Start";
	Sleep(100);

	GotoXY(55, 24);
	cout << "Exit Game";
	Sleep(100);

	while (1)
	{
		valid = 0;
		int COMMAND = _getch();
		switch (COMMAND)
		{
		case 13:
			valid = 1;
			break;
		case 87: case 119: case 72:
			if (y != top)
			{
				y -= 1;
				Cursor(1, x, y);
			}
			break;
		case 83: case 115: case 80:
			if (y < top + 6)
			{
				y += 1;
				Cursor(0, x, y);
			}
			break;
		case 27:
			exit(0);
		default:
			break;
		}

		if (valid == 1) return y - top + 1;
	}

}

void PrintXY(int x, int y, const string& message)
{
	GotoXY(x, y);
	std::cout << message;
}

void Cursor(bool is_up, int POSX, int POSY)
{
	if (is_up)
	{
		PrintXY(POSX - 3, POSY + 1, "   ");
		PrintXY(POSX - 3, POSY, "=> ");
		GotoXY(POSX - 4, POSY);
	}
	else
	{
		PrintXY(POSX - 3, POSY - 1, "   ");
		PrintXY(POSX - 3, POSY, "=> ");
		GotoXY(POSX - 4, POSY);
	}
}



void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBoard(int pSize) {
	for (int i = 0; i <= pSize; i++) {
		for (int j = 0; j <= pSize; j++) {
			GotoXY(LEFT + 4 * i, TOP + 2 * j);
			cout << ".";
		}
	}
}


int ProcessFinish(int pWhoWin) {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2); 
	switch (pWhoWin) {
	case -1:
		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", true, false);
		break;
	case 1:
		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", false, true);
		break;
	case 0:
		printf("Nguoi choi %d da hoa nguoi choi %d\n", false, true);
		break;
	case 2:
		_TURN = !_TURN; 
	}
	GotoXY(_X, _Y); 
	return pWhoWin;
	
}

int AskContinue(){
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	printf("Nhan 'y/n' de tiep tuc/dung: ");
	return toupper(_getch());
}

