#include <SFML/Graphics.hpp>

#include "View.h"
#include "Model.h"
#include "Globals.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

int mainScreen(int& x, int& y) {
	const int top = 18;
	const int left = 55;

	x = top;
	y = left;

	sf::RenderWindow window(sf::VideoMode(1366, 768), "Caro", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::Texture backgroundT;
	if (!backgroundT.loadFromFile("Assets/background_menu.png")) {
	}

	sf::Sprite bg(backgroundT);
	bg.setScale(4.26875f, 4.267f);

	sf::Texture titleT;
	if (!titleT.loadFromFile("Assets/title_menu.png")) {
	}

	sf::Sprite titleS(titleT);
	titleS.setScale(4.26875f, 4.267f);
	//Tính vị trí title Caro
	double titleWidth = titleT.getSize().x * 4.26875f;
	double titleX = (1366.f - titleWidth) / 2.f;
	titleS.setPosition(titleX, 1.f);

	//Nút được chọn
	sf::Texture modeButtonT;
	sf::Texture newButtonT;
	sf::Texture loadButtonT;
	sf::Texture quitButtonT;

	modeButtonT.loadFromFile("Assets/mode_menu.png");
	newButtonT.loadFromFile("Assets/new_menu.png");
	loadButtonT.loadFromFile("Assets/load_menu.png");
	quitButtonT.loadFromFile("Assets/quit_menu.png");

	sf::Sprite modeButton(modeButtonT);
	sf::Sprite newButton(newButtonT);
	sf::Sprite loadButton(loadButtonT);
	sf::Sprite quitButton(quitButtonT);

	modeButton.setScale(4.26875f, 4.267f);
	newButton.setScale(4.26875f, 4.267f);
	loadButton.setScale(4.26875f, 4.267f);
	quitButton.setScale(4.26875f, 4.267f);

	//Nút màu tối
	sf::Texture darkModeButtonT;
	sf::Texture darkNewButtonT;
	sf::Texture darkLoadButtonT;
	sf::Texture darkQuitButtonT;

	darkModeButtonT.loadFromFile("Assets/mode_dark.png");
	darkNewButtonT.loadFromFile("Assets/new_dark.png");
	darkLoadButtonT.loadFromFile("Assets/load_dark.png");
	darkQuitButtonT.loadFromFile("Assets/exit_dark.png");

	sf::Sprite darkModeButton(darkModeButtonT);
	sf::Sprite darkNewButton(darkNewButtonT);
	sf::Sprite darkLoadButton(darkLoadButtonT);
	sf::Sprite darkQuitButton(darkQuitButtonT);

	darkModeButton.setScale(4.26875f, 4.267f);
	darkNewButton.setScale(4.26875f, 4.267f);
	darkLoadButton.setScale(4.26875f, 4.267f);
	darkQuitButton.setScale(4.26875f, 4.267f);

	//Set vị trí các nút 
	//Nút được chọn
	double ButtonWidth = modeButtonT.getSize().x * 4.26875f;
	double buttonX = (1366.f - ButtonWidth) / 2.f;
	double buttonY = 5.f; //Khoảng cách từ title
	double buttonSpace = 70.f;

	modeButton.setPosition(buttonX, buttonY);
	newButton.setPosition(buttonX, buttonY);
	loadButton.setPosition(buttonX, buttonY);
	quitButton.setPosition(buttonX, buttonY);

	// Nút màu tối
	darkModeButton.setPosition(buttonX, buttonY);
	darkNewButton.setPosition(buttonX, buttonY);
	darkLoadButton.setPosition(buttonX, buttonY);
	darkQuitButton.setPosition(buttonX, buttonY);

	int choice = 0;
	//Toggle menu
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0; //Thoát
			}

			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					choice = (choice - 1 + 4) % 4;
					break;

				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					choice = (choice + 1) % 4;
					break;

				case sf::Keyboard::Enter:
					window.close();
					return choice + 1;

				//ESC
				case sf::Keyboard::Escape:
					window.close();
					return 0;
				default:
					break;

				}
			}
		}

		if (backgroundT.getSize().x > 0) {
			window.draw(bg);
		}

		if (titleT.getSize().x > 0) {
			window.draw(titleS);
		}

		switch (choice) {
		case 0:
		{
			window.draw(modeButton);
			window.draw(darkNewButton);
			window.draw(darkLoadButton);
			window.draw(darkQuitButton);
			break;
		}
		case 1:
		{
			window.draw(darkModeButton);
			window.draw(newButton);
			window.draw(darkLoadButton);
			window.draw(darkQuitButton);
			break;
		}
		case 2: {
			window.draw(darkModeButton);
			window.draw(darkNewButton);
			window.draw(loadButton);
			window.draw(darkQuitButton);
			break;
		}
		case 3: {
			window.draw(darkModeButton);
			window.draw(darkNewButton);
			window.draw(darkLoadButton);
			window.draw(quitButton);
			break;
		}
		}

		window.display();
	}
	return 0;
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
			GotoXY(BOARD_LEFT + 4 * i, BOARD_TOP + 2 * j);
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

