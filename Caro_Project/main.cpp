#include <SFML/Graphics.hpp>
#include "View.h"
#include "Model.h"
#include "Control.h"
#include "Globals.h"
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    FixConsoleWindow();

    sf::RenderWindow window(sf::VideoMode(1366, 768), "Caro", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        int menuChoice = mainScreen(window);

        switch (menuChoice) {
            //Chế độ
        case 1:
        {
            GameRule rule;
            int choice = modeChoosing(window);

            switch (choice) {
            case 1: rule = GameRule::FREESTYLE; break;
            case 2: rule = GameRule::STANDARD; break;
            case 3: rule = GameRule::BLOCKED_TWO_ENDS; break;
            default: continue;
            }

            // ======= BẮT ĐẦU GAME =======
            window.close();
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
            break;
        }
        //Mới
        case 2:
            break;
            //Tải
        case 3:
            break;
            //Thoát
        case 4:
        {
            // Mở cửa sổ Setting bằng SFML
            //sf::RenderWindow settingsWindow(sf::VideoMode(1366, 768), "Settings", sf::Style::Close);
            sf::Font font;
            if (!font.loadFromFile("Assets/font/regular.ttf")) {
                cerr << "Khong the tai font!\n";
            }
            handleSettings(window, font);
            break;
        }
        default:
            continue;

        }
    }
    return 0;
}
