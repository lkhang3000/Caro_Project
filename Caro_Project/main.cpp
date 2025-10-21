#include "View.h"
#include "Model.h"
#include "Control.h"
#include "Globals.h"
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    FixConsoleWindow();

    int x = 0, y = 0;
    if (mainScreen(x, y) == 0) return 0;

    // ======= CHỌN LUẬT CHƠI =======
    GameRule rule;
    int choice;
    do {
        system("cls");
        cout << "===== CHON LUAT CHOI =====\n";
        cout << "1. Freestyle (Tu do, >=5 la thang)\n";
        cout << "2. Standard (Tieu chuan, dung 5 la thang)\n";
        cout << "3. Chan 2 dau (>=5 va khong bi chan ca 2 dau)\n";
        cout << "============================\n";
        cout << "Nhap lua chon (1-3): ";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    switch (choice) {
    case 1: rule = GameRule::FREESTYLE; break;
    case 2: rule = GameRule::STANDARD; break;
    case 3: rule = GameRule::BLOCKED_TWO_ENDS; break;
    }

    // ======= BẮT ĐẦU GAME =======
    StartGame();
    bool validEnter = true;

    while (true)
    {
        _COMMAND = toupper(_getch());
        if (_COMMAND == 27) // ESC
        {
            ExitGame();
            return 0;
        }
        else {
            if (_COMMAND == 'A') MoveLeft();
            else if (_COMMAND == 'W') MoveUp();
            else if (_COMMAND == 'S') MoveDown();
            else if (_COMMAND == 'D') MoveRight();
            else if (_COMMAND == 13) // ENTER
            {
                switch (CheckBoard(_X, _Y)) {
                case -1: cout << "X"; break;
                case 1:  cout << "O"; break;
                case 0:  validEnter = false;
                }
                if (validEnter == true) {
                    int result = 2;
                    switch (rule)
                    {
                    case GameRule::FREESTYLE:
                        result = TestBoard_Freestyle(); break;
                    case GameRule::STANDARD:
                        result = TestBoard_Standard(); break;
                    case GameRule::BLOCKED_TWO_ENDS:
                        result = TestBoard_BlockedTwoEnds(); break;
                    }

                    switch (ProcessFinish(result)) {
                    case -1: case 1: case 0:
                        if (AskContinue() != 'Y') {
                            ExitGame();
                            return 0;
                        }
                        else {
                            StartGame();
                        }
                    }
                }
                validEnter = true;
            }
        }
    }
    return 0;
}
