#include <SFML/Graphics.hpp>
#include <algorithm>
#include "View.h"
#include "Model.h"
#include "Globals.h"

#define scaleX 4.26875f
#define scaleY 4.267f


void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

int mainScreen(sf::RenderWindow& window) {

	window.setVerticalSyncEnabled(true);

	// Khởi tạo font tại đây
	sf::Font font;
	if (!font.loadFromFile("Assets/font/regular.ttf")) {
		std::cerr << "Không thể tải font!\n";
	}

	sf::Texture backgroundT;
	if (!backgroundT.loadFromFile("Assets/background/background_menu.png")) {
	}

	sf::Sprite bg(backgroundT);
	bg.setScale(scaleX, scaleY);

	sf::Texture titleT;
	if (!titleT.loadFromFile("Assets/background/title_menu.png")) {
	}

	sf::Sprite titleS(titleT);
	titleS.setScale(scaleX, scaleY);
	//Tính vị trí title Caro
	double titleWidth = titleT.getSize().x * 4.26875f;
	double titleX = (1366.f - titleWidth) / 2.f;
	titleS.setPosition(titleX, 1.f);

	//Nút được chọn
	sf::Texture modeButtonT;
	sf::Texture newButtonT;
	sf::Texture loadButtonT;
	sf::Texture quitButtonT;
	sf::Texture settingButtonT;

	modeButtonT.loadFromFile("Assets/button/mode_menu.png");
	newButtonT.loadFromFile("Assets/button/new_menu.png");
	loadButtonT.loadFromFile("Assets/button/load_menu.png");
	quitButtonT.loadFromFile("Assets/button/quit_menu.png");
	settingButtonT.loadFromFile("Assets/button/setting.png");

	sf::Sprite modeButton(modeButtonT);
	sf::Sprite newButton(newButtonT);
	sf::Sprite loadButton(loadButtonT);
	sf::Sprite quitButton(quitButtonT);
	sf::Sprite settingButton(settingButtonT);

	modeButton.setScale(scaleX, scaleY);
	newButton.setScale(scaleX, scaleY);
	loadButton.setScale(scaleX, scaleY);
	quitButton.setScale(scaleX, scaleY);
	settingButton.setScale(scaleX - 1, scaleY - 1);

	//Nút màu tối
	sf::Texture darkModeButtonT;
	sf::Texture darkNewButtonT;
	sf::Texture darkLoadButtonT;
	sf::Texture darkQuitButtonT;
	sf::Texture darkSettingButtonT;

	darkModeButtonT.loadFromFile("Assets/button/mode_dark.png");
	darkNewButtonT.loadFromFile("Assets/button/new_dark.png");
	darkLoadButtonT.loadFromFile("Assets/button/load_dark.png");
	darkQuitButtonT.loadFromFile("Assets/button/quit_dark.png");
	darkSettingButtonT.loadFromFile("Assets/button/setting_dark.png");

	sf::Sprite darkModeButton(darkModeButtonT);
	sf::Sprite darkNewButton(darkNewButtonT);
	sf::Sprite darkLoadButton(darkLoadButtonT);
	sf::Sprite darkQuitButton(darkQuitButtonT);
	sf::Sprite darkSettingButton(darkSettingButtonT);

	darkModeButton.setScale(scaleX, scaleY);
	darkNewButton.setScale(scaleX, scaleY);
	darkLoadButton.setScale(scaleX, scaleY);
	darkQuitButton.setScale(scaleX, scaleY);
	darkSettingButton.setScale(scaleX - 1, scaleY - 1);

	//Set vị trí các nút 
	//Nút được chọn
	double ButtonWidth = modeButtonT.getSize().x * 4.26875f;
	double buttonX = (1366.f - ButtonWidth) / 2.f;
	double buttonY = 5.f; //Khoảng cách từ title
	double buttonSpace = 70.f;
	float settingX = 1300.f;
	if (settingButtonT.getSize().x > 0) {
		settingX = 1370.f - settingButtonT.getSize().x * 3.26875f - 20.f; // 20px margin
	} else {
		// fallback to previous hardcoded value, but log that texture size was zero
		std::cerr << "Warning: settingButton texture size is zero; using fallback X=1250\n";
		settingX = 1300.f;
	}
	float settingY = 10.f;

	modeButton.setPosition(buttonX, buttonY);
	newButton.setPosition(buttonX, buttonY);
	loadButton.setPosition(buttonX, buttonY);
	quitButton.setPosition(buttonX, buttonY);
	settingButton.setPosition(settingX, settingY);

	// Nút màu tối
	darkModeButton.setPosition(buttonX, buttonY);
	darkNewButton.setPosition(buttonX, buttonY);
	darkLoadButton.setPosition(buttonX, buttonY);
	darkQuitButton.setPosition(buttonX, buttonY);
	darkSettingButton.setPosition(settingX, settingY);

	int choice = 0;
	const int totalOptions = 5;
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
					choice = (choice - 1 + totalOptions) % totalOptions;
					break;

				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					choice = (choice + 1) % totalOptions;
					break;

				case sf::Keyboard::A:
				case sf::Keyboard::Left:
					choice = (choice - 1 + totalOptions) % totalOptions;
					break;

				case sf::Keyboard::D:
				case sf::Keyboard::Right:
					choice = (choice + 1) % totalOptions;
					break;

				case sf::Keyboard::Enter:
					if (choice == 4) { // Settings
						handleSettings(window, font);
						break;
					}
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
			window.draw(darkSettingButton);
			break;
		}
		case 1:
		{
			window.draw(darkModeButton);
			window.draw(newButton);
			window.draw(darkLoadButton);
			window.draw(darkQuitButton);
			window.draw(darkSettingButton);
			break;
		}
		case 2: {
			window.draw(darkModeButton);
			window.draw(darkNewButton);
			window.draw(loadButton);
			window.draw(darkQuitButton);
			window.draw(darkSettingButton);
			break;
		}
		case 3: {
			window.draw(darkModeButton);
			window.draw(darkNewButton);
			window.draw(darkLoadButton);
			window.draw(quitButton);
			window.draw(darkSettingButton);
			break;
		}
		case 4: { // Setting được chọn
			window.draw(darkModeButton);
			window.draw(darkNewButton);
			window.draw(darkLoadButton);
			window.draw(darkQuitButton);
			window.draw(settingButton); // sáng
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

int AskContinue() {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	printf("Nhan 'y/n' de tiep tuc/dung: ");
	return toupper(_getch());
}


// Hàm xử lý màn hình Settings
void handleSettings(sf::RenderWindow& window, sf::Font& font) {
	enum VolumeLevel { MUTED, LOW, MEDIUM, MAX };

	// ==== NÚT EXIT (X) ====
	sf::Texture tabExitT, tabExitDarkT;
	if (!tabExitDarkT.loadFromFile("Assets/button/exit_dark.png")) std::cerr << "Failed load exit_dark\n";
	if (!tabExitT.loadFromFile("Assets/button/exit.png")) std::cerr << "Failed load exit\n";

	sf::Sprite tabExit(tabExitT), tabExitDark(tabExitDarkT);
	tabExitDark.setScale(scaleX, scaleY);
	tabExit.setScale(scaleX, scaleY);

	// CÁC LỰA CHỌN TAB
	const int totalChoices = 5;
	int tabChoice = 0;     // Lựa chọn hiện tại (0-4)
	int lastTabChoice = 0; // Tab cuối cùng được chọn (0-3), dùng để giữ đúng background

	// TẢI ẢNH NỀN CHO CÁC TAB
	vector<sf::Texture> tabBGs(4);
	if (!tabBGs[0].loadFromFile("Assets/background/setting_audio.png")) std::cerr << "Failed load setting_audio\n";
	if (!tabBGs[1].loadFromFile("Assets/background/setting_key.png")) std::cerr << "Failed load setting_key\n";
	if (!tabBGs[2].loadFromFile("Assets/background/setting_rule.png")) std::cerr << "Failed load setting_rule\n";
	if (!tabBGs[3].loadFromFile("Assets/background/setting_info.png")) std::cerr << "Failed load setting_info\n";

	sf::Sprite bg(tabBGs[0]);
	bg.setScale(scaleX, scaleY);
	bg.setPosition(0, 0);

	// CÀI ĐẶT ÂM THANH
	int soundLevel = MEDIUM;
	int affectLevel = MEDIUM;
	int soundChoice = 0; // 0 = sound, 1 = effect
	bool editing = false; // Enter toggles edit mode for the focused control

	// Tải texture cho các mức
	using TexMap = map<string, sf::Texture>;
	TexMap soundLevelT, affectLevelT;
	TexMap soundLevelDarkT, affectLevelDarkT;

	vector<string> levels = { "muted", "low", "medium", "max" };
	for (auto& l : levels) {
		if (!soundLevelT[l].loadFromFile("Assets/button/sound_" + l + ".png")) std::cerr << "Failed load sound_" + l + "\n";
		if (!affectLevelT[l].loadFromFile("Assets/button/affect_" + l + ".png")) std::cerr << "Failed load affect_" + l + "\n";
		if (!soundLevelDarkT[l].loadFromFile("Assets/button/sound_" + l + "_dark.png")) std::cerr << "Failed load sound_" + l + "_dark\n";
		if (!affectLevelDarkT[l].loadFromFile("Assets/button/affect_" + l + "_dark.png")) std::cerr << "Failed load affect_" + l + "_dark\n";
	}

	sf::Sprite soundBar, affectBar;
	// base scale used previously is large; adjust visual scale a bit for highlight when editing
	const float baseScaleX = scaleX;
	const float baseScaleY = scaleY;
	const float editZoom = 0.15f; // slight zoom when editing to indicate state

	soundBar.setScale(baseScaleX, baseScaleY);
	affectBar.setScale(baseScaleX, baseScaleY);
	soundBar.setPosition(3.f, 0.f);
	affectBar.setPosition(0.f, 0.f);

	sf::Texture affectChosenT, soundChosenT;
	if (!affectChosenT.loadFromFile("Assets/background/affect_chosen.png"))
		std::cerr << "Failed load Assets/background/affect_chosen.png\n";
	if (!soundChosenT.loadFromFile("Assets/background/sound_chosen.png"))
		std::cerr << "Failed load Assets/background/sound_chosen.png\n";


	sf::Sprite affectChosen(affectChosenT), soundChosen(soundChosenT);
	soundChosen.setScale(scaleX, scaleY);
	affectChosen.setScale(scaleX, scaleY);
	soundChosen.setPosition(0.f, 0.f);
	affectChosen.setPosition(0.f, 0.f);

	// 1. Text cho Tab Phím chơi
	sf::Text keybindsText;
	keybindsText.setFont(font);
	keybindsText.setString(L"Di chuyển / Thay đổi\n\n\n\n\n\nChọn / Xác nhận");
	keybindsText.setCharacterSize(30); 
	keybindsText.setFillColor(sf::Color(80, 48, 32)); 
	keybindsText.setPosition(580.f, 330.f);

	// 2. Text cho Tab Luật chơi
	sf::Text rulesText;
	rulesText.setFont(font);
	std::wstring rulesString = 
		L"					LUẬT CHƠI:\n\n"
		L"1. Mỗi người đi một nước, X đi trước, O đi sau.\n\n"
		L"2. Bên nào có 5 quân liên tiếp trên một hàng, cột, hoặc\n"
		L"   đường chéo là THẮNG.\n\n"
		L"3. Khi có người thắng -> ván cờ kết thúc, hiển thị kết quả.\n\n"
		L"4. Nếu bàn cờ đầy mà không ai có 5 liên tiếp -> HOÀ\n";
	rulesText.setString(rulesString);
	rulesText.setCharacterSize(30);
	rulesText.setFillColor(sf::Color(80, 48, 32));
	rulesText.setPosition(235.f, 250.f); 

	// 3. Text cho Tab Thông tin
	sf::Text infoText;
	infoText.setFont(font);
	std::wstring infoString = 
		L"Trường Đại học Khoa học Tự nhiên - ĐHQGHCM\n"
		L"		ĐỒ ÁN GAME CARO - 25C10\n\n"
		L"		  Giáo viên hướng dẫn: \n"
		L"	   < ThS.Trương Toàn Thịnh >\n\n"
		L"	    Game được thực hiện bởi:\n"
		L"     24127132 - Nguyễn Thị Ngọc Trâm\n"
		L"     24127158 - Nguyễn Trần Lan Duy\n"
		L"     24127164 - Lê Kim Hằng\n"
		L"     24127262 - Đỗ Thành Vinh\n"
		L"     24127465 - Tạ Mai Như Ngọc\n\n";
	infoText.setString(infoString);
	infoText.setCharacterSize(30);
	infoText.setFillColor(sf::Color(80, 48, 32));
	infoText.setPosition(350.f, 235.f);

	// === Main loop ===
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) return;

			if (event.type == sf::Event::KeyPressed) {
				// Only A S W D and Enter are used
				auto key = event.key.code;

				// ESC (optional) keeps previous behavior: exit settings
				if (key == sf::Keyboard::Escape) return;

				// ENTER: if Exit is selected exit; otherwise toggle edit mode in audio tab
				if (key == sf::Keyboard::Enter) {
					if (tabChoice == 4) return; // Exit button selected
					if (tabChoice == 0) {
						editing = !editing; // toggle editing mode for focused control
					}
					// If not audio tab, Enter does nothing (tabs are navigated with A/D)
				}
				// W/S: inside audio tab, change focus between sound and effect (only when not editing)
				else if (key == sf::Keyboard::W) {
					if (tabChoice == 0 && !editing) {
						soundChoice = (soundChoice - 1 + 2) % 2;
					}
				}
				else if (key == sf::Keyboard::S) {
					if (tabChoice == 0 && !editing) {
						soundChoice = (soundChoice + 1) % 2;
					}
				}
				// A/D: behave as:
				// - if in audio tab and editing == true -> change value of focused control
				else if (key == sf::Keyboard::A) {
					if (tabChoice == 0 && editing) {
						// decrease focused value
						if (soundChoice == 0)
							soundLevel = std::max(static_cast<int>(MUTED), soundLevel - 1);
						else
							affectLevel = std::max(static_cast<int>(MUTED), affectLevel - 1);
					}
					else {
						// move to previous tab
						tabChoice = (tabChoice - 1 + totalChoices) % totalChoices;
						// leaving edit mode when switching tabs
						editing = false;
					}
				}
				else if (key == sf::Keyboard::D) {
					if (tabChoice == 0 && editing) {
						// increase focused value
						if (soundChoice == 0)
							soundLevel = std::min(static_cast<int>(MAX), soundLevel + 1);
						else
							affectLevel = std::min(static_cast<int>(MAX), affectLevel + 1);
					}
					else {
						// move to next tab
						tabChoice = (tabChoice + 1) % totalChoices;
						editing = false;
					}
				}

				// Update lastTabChoice to keep the right background shown
				if (tabChoice < 4) lastTabChoice = tabChoice;
			}
		}

		// Draw
		bg.setTexture(tabBGs[lastTabChoice]);
		window.clear();
		window.draw(bg);

		// Exit button (bright when selected)
		if (tabChoice == 4) window.draw(tabExit);
		else window.draw(tabExitDark);

		// Audio tab content drawing
		if (lastTabChoice == 0) {
			string currentSoundLvl = levels[soundLevel];
			string currentAffectLvl = levels[affectLevel];

			// Select textures for bright/dark states
			if (tabChoice == 0) {
				// audio tab is active
				if (soundChoice == 0) { // sound focus
					soundBar.setTexture(soundLevelT[currentSoundLvl]);
					affectBar.setTexture(affectLevelDarkT[currentAffectLvl]);
					window.draw(soundChosen);
				}
				else { // effect focus
					soundBar.setTexture(soundLevelDarkT[currentSoundLvl]);
					affectBar.setTexture(affectLevelT[currentAffectLvl]);
					window.draw(affectChosen);
				}
			}
			else {
				// audio tab not active -> both dark
				soundBar.setTexture(soundLevelDarkT[currentSoundLvl]);
				affectBar.setTexture(affectLevelDarkT[currentAffectLvl]);
			}

			// Visual cue for editing: slightly scale up focused control while editing
			if (tabChoice == 0 && editing && soundChoice == 0) {
				soundBar.setScale(baseScaleX + editZoom, baseScaleY + editZoom);
				affectBar.setScale(baseScaleX, baseScaleY);
				soundBar.setPosition(-8.f, -15.f);
			}
			else if (tabChoice == 0 && editing && soundChoice == 1) {
				soundBar.setScale(baseScaleX, baseScaleY);
				affectBar.setScale(baseScaleX + editZoom, baseScaleY + editZoom);
				affectBar.setPosition(-10.f, -10.f);
			}
			else {
				soundBar.setScale(baseScaleX, baseScaleY);
				soundBar.setPosition(3.f, 0.f);
				affectBar.setScale(baseScaleX, baseScaleY);
				affectBar.setPosition(0.f, 0.f);
			}
			window.draw(soundBar);
			window.draw(affectBar);
		}
		else if (lastTabChoice == 1) {
			// Tab Phím chơi
			window.draw(keybindsText);
		}
		else if (lastTabChoice == 2) {
			// Tab Luật chơi
			window.draw(rulesText);
		}
		else if (lastTabChoice == 3) {
			// Tab Thông tin
			window.draw(infoText);
		}

		window.display();
	}
}

int modeChoosing(sf::RenderWindow& window) {
	//Tải background
	sf::Texture backgroundT;
	if (!backgroundT.loadFromFile("Assets/background_menu.png")) {
	}

	sf::Sprite bg(backgroundT);
	bg.setScale(scaleX, scaleY);

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
			double scale_X = baseScale;
			double scale_Y = baseScale;
			bool showFront = isCard1Flipped;

			if (isFlipping) {
				double angle = flipProcess * 3.14159;
				scale_X = baseScale * std::abs(std::cos(angle));

				double zoomFactor = 1.0 + 0.3 * std::sin(flipProcess * 3.14159);
				scale_Y = baseScale * zoomFactor;

				if (flipProcess < 0.5f) {
					showFront = isCard1Flipped;
				}
				else {
					showFront = !isCard1Flipped;
				}
			}

			if (showFront) {
				card1F.setScale(scale_X, scale_Y);
				window.draw(card1F);
			}
			else {
				card1B.setScale(scale_X, scale_Y);
				window.draw(card1B);
			}

		}

		window.display();
	}

	return -1;

}
