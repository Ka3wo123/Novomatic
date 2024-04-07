#pragma once
#include <array>
#include <SFML/Graphics.hpp>

class Ticketomat {
public:
	void renderHomeWindow(sf::RenderWindow& window, sf::Font& font, sf::Text& welcomeText);
	void renderMoneyWindow(sf::RenderWindow& window, sf::Font& font, sf::Text& promptText);	
	void renderTicketWindow(std::array<sf::Text, 5>& textArray, std::array<sf::RectangleShape, 5>& buttonArray, sf::RenderWindow& window, sf::Font& font);
	void renderEndWindow(sf::RenderWindow& window, sf::Font& font, sf::Text& infoText, sf::Text& exchangeText, sf::RectangleShape& endBtn);
};