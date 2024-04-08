#pragma once
#include <array>
#include <SFML/Graphics.hpp>

class Ticketomat {
public:
	void renderHomeWindow(sf::RenderWindow& window, sf::Font& font, sf::Text& welcomeText);	
	void renderTicketWindow(std::array<sf::Text, 5>& textArray, std::array<sf::RectangleShape, 5>& buttonArray, sf::RenderWindow& window, sf::Font& font);	
};