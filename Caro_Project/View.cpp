//#include <SFML/Graphics.hpp>

#include "View.h"
#include "Model.h"
#include "Globals.h"

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

int mainScreen(sf::RenderWindow& window) {
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
	//double buttonSpace = 70.f;

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
		window.clear();

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

int modeChoosing(sf::RenderWindow& window) {
	//Tải background
	sf::Texture backgroundT;
	if (!backgroundT.loadFromFile("Assets/background_menu.png")) {
	}

	sf::Sprite bg(backgroundT);
	bg.setScale(4.26875f, 4.267f);

	//Tải ảnh từ folder
	sf::Texture card1Front, card1Back, card2Front, card2Back, card3Front, card3Back;
	card1Front.loadFromFile("Assets/card1.png");
	card1Back.loadFromFile("Assets/card1_back.png");
	card2Front.loadFromFile("Assets/card1.png");
	card2Back.loadFromFile("Assets/card1_back.png");
	card3Front.loadFromFile("Assets/card1.png");
	card3Back.loadFromFile("Assets/card1_back.png");

	double baseScale = 3.0f;
	//Size và position card 1
	double card1Width = card1Back.getSize().x * baseScale;
	double card1Height = card1Back.getSize().y * baseScale;
	double card1X = -300.0f;
	double card1Y = 100.0f;

	//Size và position card 2
	double card2Width = card2Back.getSize().x * baseScale;
	double card2Height = card2Back.getSize().y * baseScale;
	double card2X = -90.0f;
	double card2Y = 100.0f;

	//Size và position card 3
	double card3Width = card3Back.getSize().x * baseScale;
	double card3Height = card3Back.getSize().y * baseScale;
	double card3X = 100.0f;
	double card3Y = 100.0f;

	//Tạo sprite từng card
	sf::Sprite card1F(card1Front);
	sf::Sprite card1B(card1Back);
	sf::Sprite card2F(card1Front);
	sf::Sprite card2B(card1Back);
	sf::Sprite card3F(card1Front);
	sf::Sprite card3B(card1Back);

	//set origin của object
	//card 1
	card1F.setOrigin(card1Front.getSize().x / 2.0f, card1Front.getSize().y / 2.0f);
	card1B.setOrigin(card1Back.getSize().x / 2.0f, card1Back.getSize().y / 2.0f);

	float centerX = card1X + card1Width / 2.0f;
	float centerY = card1Y + card1Height / 2.0f;

	card1F.setPosition(centerX, centerY);
	card1B.setPosition(centerX, centerY);

	//card 2
	card2F.setOrigin(card2Front.getSize().x / 2.0f, card2Front.getSize().y / 2.0f);
	card2B.setOrigin(card2Back.getSize().x / 2.0f, card2Back.getSize().y / 2.0f);

	float center2X = card2X + card2Width / 2.0f;
	float center2Y = card2Y + card2Height / 2.0f;

	card2F.setPosition(center2X, center2Y);
	card2B.setPosition(center2X, center2Y);

	//card 3
	card3F.setOrigin(card3Front.getSize().x / 2.0f, card3Front.getSize().y / 2.0f);
	card3B.setOrigin(card3Back.getSize().x / 2.0f, card3Back.getSize().y / 2.0f);

	float center3X = card3X + card3Width / 2.0f;
	float center3Y = card3Y + card3Height / 2.0f;

	card3F.setPosition(center3X, center3Y);
	card3B.setPosition(center3X, center3Y);


	int cardChoice = 1;
	bool isCard1Flipped = false;
	bool isFlipping = false;
	double flipProcess = 0.0f;
	const double flipSpeed = 4.0f;
	bool showFront = false;

	sf::Clock clock;
	
	while (window.isOpen()) {
		float time = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return -1; //Thoát
			}

			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
					cardChoice = (cardChoice - 1 + 3) % 3;
					break;

				case sf::Keyboard::D:
				case sf::Keyboard::Right:
					cardChoice = (cardChoice + 1) % 3;
					break;

				case sf::Keyboard::Space:
					if (!isFlipping && cardChoice == 1) {  
						isFlipping = true;                 
						flipProcess = 0.0f;                
					}
					break;

				case sf::Keyboard::Enter:
					return cardChoice + 1;

					//ESC
				case sf::Keyboard::Escape:
					return -1;
				default:
					break;

				}
			}
		}

		if (isFlipping) {
			flipProcess += flipSpeed * time;

			if (flipProcess >= 1.0f) {
				flipProcess = 1.0f;
				isFlipping = false;
				isCard1Flipped = !isCard1Flipped;
			}
		}

		window.clear();

		if (backgroundT.getSize().x > 0) {
			window.draw(bg);
		}

		if (cardChoice == 1) {
			double scaleX = baseScale;
			double scaleY = baseScale;
			bool showFront = isCard1Flipped;

			if (isFlipping) {
				double angle = flipProcess * 3.14159;
				scaleX = baseScale * std::abs(std::cos(angle));

				double zoomFactor = 1.0 + 0.3 * std::sin(flipProcess * 3.14159); 
				scaleY = baseScale * zoomFactor;

				if (flipProcess < 0.5f) {
					showFront = isCard1Flipped;
				}
				else {
					showFront = !isCard1Flipped;
				}
			}

			if (showFront) {
				card1F.setScale(scaleX, scaleY);
				window.draw(card1F);
			}
			else {
				card1B.setScale(scaleX, scaleY);
				window.draw(card1B);
			}
		
		}

		window.display();
	}
	
	return -1;

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

