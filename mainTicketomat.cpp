#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <stack>
#include <sstream>
#include <map>
#include "Ticketomat/Ticketomat.hpp"


bool countExchange(sf::RectangleShape& button, sf::Vector2i& mousePos, size_t ticketPrice, std::map<size_t, size_t>& exchangeMap, size_t sum) {
	if (button.getGlobalBounds().contains(sf::Vector2f(mousePos)) && sum >= ticketPrice) {
		size_t diff = sum - ticketPrice;
		while (diff > 0) {
			if (diff >= 5) {
				exchangeMap[5]++;
				diff -= 5;
			}
			else if (diff >= 2) {
				exchangeMap[2]++;
				diff -= 2;
			}
			else {
				exchangeMap[1]++;
				diff--;
			}

		}
		return true;
	}
	else {
		return false;
	}
}

void setTextPosition(sf::Text& text, float x, float y) {
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	text.setPosition(x, y);

}

int main() {

	constexpr size_t WINDOW_WIDTH = 600;
	constexpr size_t WINDOW_HEIGHT = 900;
	size_t moneyInput;
	std::map<size_t, size_t> exchangeMap = { {1, 0}, {2, 0}, {5, 0} };
	size_t sum = 0;
	std::ostringstream ss;
	std::ostringstream moneyOutput;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	std::array<sf::RenderWindow, 4> windows = {
	   sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ticketomat", sf::Style::Default, settings),
	   sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wrzuc pienadze", sf::Style::Default, settings),
	   sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wybierz bilet",sf::Style::Default, settings),
	   sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Odbierz bilet", sf::Style::Default, settings)
	};

	sf::ConvexShape nextBtn;
	sf::ConvexShape backBtn;
	sf::RectangleShape logo(sf::Vector2f(250.f, 350.f));
	sf::Texture logoTexture;

	sf::Color colorTop(0, 128, 255);  
	sf::Color colorBottom(255, 255, 255);
	sf::VertexArray vertices(sf::Quads, 4);

	vertices[0].position = sf::Vector2f(0, 0);              
	vertices[1].position = sf::Vector2f(WINDOW_WIDTH, 0);   
	vertices[2].position = sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT); 
	vertices[3].position = sf::Vector2f(0, WINDOW_HEIGHT);

	vertices[0].color = colorTop;
	vertices[1].color = colorTop;
	vertices[2].color = colorBottom;
	vertices[3].color = colorBottom;


	if (!(logoTexture.loadFromFile("..\\..\\..\\Ticketomat\\Images\\logo.png"))) {
		throw std::runtime_error("Failed to load image logo");
	}

	logo.setFillColor(sf::Color::White);
	logo.setTexture(&logoTexture);
	logo.setPosition((WINDOW_WIDTH - logo.getSize().x) / 2.f, (WINDOW_HEIGHT - logo.getSize().y) / 2.f);
	

	nextBtn.setPointCount(5);
	nextBtn.setPoint(0, sf::Vector2f(0, 0));
	nextBtn.setPoint(1, sf::Vector2f(150.f, 0));
	nextBtn.setPoint(2, sf::Vector2f(200.f, 30.f));
	nextBtn.setPoint(3, sf::Vector2f(150.f, 60.f));
	nextBtn.setPoint(4, sf::Vector2f(0, 60.f));
	nextBtn.setFillColor(sf::Color::Blue);
	nextBtn.setPosition(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 200);


	backBtn.setPointCount(5);
	backBtn.setPoint(0, sf::Vector2f(0, 30.f));
	backBtn.setPoint(1, sf::Vector2f(50.f, 0));
	backBtn.setPoint(2, sf::Vector2f(200.f, 0));
	backBtn.setPoint(3, sf::Vector2f(200.f, 60.f));
	backBtn.setPoint(4, sf::Vector2f(50.f, 60.f));
	backBtn.setFillColor(sf::Color::Blue);
	backBtn.setPosition(0, WINDOW_HEIGHT - 200);


	sf::Font arialFont;
	if (!arialFont.loadFromFile("..\\..\\..\\Ticketomat\\Fonts\\ARIAL.TTF")) {
		throw std::runtime_error("Failed to load font");
	}

	std::array<sf::Text, 5> textArray;
	std::array<sf::RectangleShape, 5> buttonArray;
	std::array<bool, 4> visibleArr = { true, false, false, false };


	sf::Text welcomeText;
	sf::Text promptText;
	sf::Text insufficientText;
	sf::Text moneyText;
	sf::Text changeText;
	sf::Text printingTicketText;

	promptText.setFont(arialFont);
	promptText.setCharacterSize(24);
	promptText.setColor(sf::Color::Black);
	promptText.setString("Wrzuc pieniadze (podaj liczbe z klawiatury)\nTwoje saldo wynosi: 0");

	moneyText.setFont(arialFont);
	moneyText.setCharacterSize(24);
	moneyText.setColor(sf::Color::Black);
	moneyText.setString("");

	insufficientText.setFont(arialFont);
	insufficientText.setCharacterSize(28);
	insufficientText.setColor(sf::Color::Red);
	insufficientText.setString("Wrzuc wiecej pieniedzy, by kupic ten bilet");

	changeText.setFont(arialFont);
	changeText.setCharacterSize(24);
	changeText.setColor(sf::Color::Black);	

	printingTicketText.setFont(arialFont);
	printingTicketText.setCharacterSize(20);
	printingTicketText.setColor(sf::Color::Red);
	printingTicketText.setString("Trwa drukowanie biletu...");

	setTextPosition(promptText, WINDOW_WIDTH / 2.f, 100);
	setTextPosition(insufficientText, WINDOW_WIDTH / 2.f, 200);
	setTextPosition(moneyText, WINDOW_WIDTH / 2.f, 200);
	setTextPosition(printingTicketText, WINDOW_HEIGHT / 2.f, 50);
	setTextPosition(changeText, WINDOW_WIDTH / 2.f - 70, 200);


	Ticketomat homeW;
	homeW.renderHomeWindow(windows[0], arialFont, welcomeText);


	Ticketomat ticketW;
	ticketW.renderTicketWindow(textArray, buttonArray, windows[2], arialFont);



	int windowNumber = 0;
	bool isPicked = false;
	while (windows[windowNumber].isOpen()) {

		sf::Event event;
		while (windows[windowNumber].pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				for (auto& w : windows)
					w.close();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && windowNumber == 2) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(windows[windowNumber]);
				std::string tempText = "";

				if (backBtn.getGlobalBounds().contains(sf::Vector2f(mousePos))) {

					visibleArr[windowNumber] = false;
					visibleArr[--windowNumber] = true;

					for (int i = 0; i < 4; i++) {
						windows[i].clear();
					}
				}
				else {
					bool c1 = countExchange(buttonArray[0], mousePos, 3, exchangeMap, sum);
					bool c2 = countExchange(buttonArray[1], mousePos, 4, exchangeMap, sum);
					bool c3 = countExchange(buttonArray[2], mousePos, 8, exchangeMap, sum);
					bool c4 = countExchange(buttonArray[3], mousePos, 10, exchangeMap, sum);
					bool c5 = countExchange(buttonArray[4], mousePos, 15, exchangeMap, sum);

					if (c1 || c2 || c3 || c4 || c5) {
						for (const auto& pair : exchangeMap) {
							tempText.append(std::to_string(pair.second)).append("x").append(std::to_string(pair.first)).append("zl\n");
						}
						changeText.setString("Odbierz swoj bilet\nTwoja reszta:\n" + tempText);
						exchangeMap[5] = 0;
						exchangeMap[2] = 0;
						exchangeMap[1] = 0;

						visibleArr[windowNumber] = false;
						visibleArr[++windowNumber] = true;

						float progressBarWidth = 0.0f;
						sf::RectangleShape progressBar(sf::Vector2f(0, 20));
						progressBar.setFillColor(sf::Color::Green);
						progressBar.setPosition(50, 100);

						sf::Clock progressBarClock;
						for (int i = 0; i < 4; i++) {
							float elapsedTime = progressBarClock.getElapsedTime().asSeconds();
							float progress = elapsedTime / 3.0f;
							progressBarWidth = progress * (WINDOW_WIDTH - 100);
							progressBar.setSize(sf::Vector2f(progressBarWidth, 20));


							windows[2].clear(sf::Color::White);
							windows[2].draw(progressBar);
							windows[2].draw(printingTicketText);
							windows[2].display();

							sf::sleep(sf::seconds(1));
						}
									


						for (int i = 0; i < 4; i++) {
							windows[i].clear();
						}
					}
					else {										
						isPicked = true;
						windows[2].clear(sf::Color::White);
						windows[2].draw(insufficientText);
						windows[2].display();
					}
				}
			}

			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(windows[windowNumber]);

				if (nextBtn.getGlobalBounds().contains(sf::Vector2f(mousePos)) && windowNumber == 3) {

					windowNumber = 0;
					for (int i = 0; i < 4; i++) {
						visibleArr[i] = false;							
					}					
					visibleArr[0] = true;
					sum = 0;
					promptText.setString("Wrzuc pieniadze (podaj liczbe z klawiatury)\nTwoje saldo wynosi: 0");
				}

				else if (backBtn.getGlobalBounds().contains(sf::Vector2f(mousePos)) && windowNumber > 0 && backBtn.getGlobalBounds().contains(sf::Vector2f(mousePos)) && windowNumber < 3) {
					if (windowNumber == 1) {
						sum = 0;
						moneyOutput.str("");
						promptText.setString("Wrzuc pieniadze (podaj liczbe z klawiatury)\nTwoje saldo wynosi: 0");
						moneyText.setString("");
					}
					visibleArr[windowNumber] = false;
					visibleArr[--windowNumber] = true;

					for (int i = 0; i < 4; i++) {
						windows[i].clear();
					}
				}

				else if (nextBtn.getGlobalBounds().contains(sf::Vector2f(mousePos)) && windowNumber < 3) {
					visibleArr[windowNumber] = false;
					visibleArr[++windowNumber] = true;

					/*for (int i = 0; i < 4; i++) {
						windows[i].clear();
					}*/

				}
			}

			else if (event.type == sf::Event::TextEntered && windowNumber == 1) {
				if (event.text.unicode == '\b') {
					if (!ss.str().empty()) {
						ss.str(ss.str().substr(0, ss.str().size() - 1));
					}

					if (!moneyOutput.str().empty()) {
						moneyOutput.str(moneyOutput.str().substr(0, moneyOutput.str().size() - 1));
					}
				}
				else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
					if (!ss.str().empty()) {
						int number;
						if (!(std::istringstream(ss.str()) >> number)) {
							windows[windowNumber].draw(insufficientText);
						}
						else {
							sum += number;
							ss.str("");
							moneyOutput.str("");
						}
					}
				}
				else if (event.text.unicode >= '0' && event.text.unicode <= '9') {

					ss << static_cast<char>(event.text.unicode);
					moneyOutput << static_cast<char>(event.text.unicode);
				}
				promptText.setString("Wrzuc pieniadze (podaj liczbe z klawiatury)\nTwoje saldo wynosi: " + std::to_string(sum));
				moneyText.setString(moneyOutput.str());
			}



			// clear section
			for (int i = 0; i < 4; i++) {
				windows[i].setVisible(visibleArr[i]);
				windows[i].clear(sf::Color::White);
			}

			if (isPicked) {
				isPicked = false;
				sf::sleep(sf::seconds(2));
				continue;
			}


			// draw section		
			for (auto& w : windows) {
				w.draw(vertices);
				if (windowNumber == 0 || windowNumber == 3) {
					w.draw(nextBtn);
				}
				else if (windowNumber == 2) {
					w.draw(backBtn);
				}
				else {
					w.draw(nextBtn);
					w.draw(backBtn);

				}
			}
			windows[0].draw(logo);
			windows[0].draw(welcomeText);
			windows[1].draw(promptText);
			windows[1].draw(moneyText);
			windows[3].draw(changeText);			

			
			for (auto& b : buttonArray) {
				windows[2].draw(b);
			}

			for (auto& t : textArray) {
				windows[2].draw(t);
			}

			// display section
			for (auto& w : windows) {
				w.display();
			}
		}
	}
	return 0;
}
