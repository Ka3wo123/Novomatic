#include "Ticketomat.hpp"


void Ticketomat::renderTicketWindow(std::array<sf::Text, 5>& textArray, std::array<sf::RectangleShape, 5>& buttonArray, sf::RenderWindow& window, sf::Font& font) {	
	
	for (int i = 0; i < 5; i++) {
		std::string value;
		switch (i)
		{
		case 0:
			value = "3";
			break;
		case 1:
			value = "4";
			break;
		case 2:
			value = "8";
			break;
		case 3:
			value = "10 ";
			break;
		case 4:
			value = "15";
			break;
		default:
			break;
		}
		sf::Text text;				
		text.setFont(font);
		text.setColor(sf::Color::Red);
		text.setString("Bilet " + value + " zl");
		text.setCharacterSize(20);

		textArray[i] = text;

		sf::RectangleShape button(sf::Vector2f(300.f, 60.f));
		button.setPosition((window.getSize().x - button.getSize().x) / 2, 100 + 120 * i);
		button.setOutlineThickness(2);
		button.setOutlineColor(sf::Color::Black);

		buttonArray[i] = button;

		sf::FloatRect textBounds = text.getLocalBounds();
		textArray[i].setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
		textArray[i].setPosition(button.getPosition().x + button.getSize().x / 2.f, button.getPosition().y + button.getSize().y / 2.f);
	}
}

void Ticketomat::renderHomeWindow(sf::RenderWindow& window, sf::Font& font, sf::Text& welcomeText) {
	welcomeText.setFont(font);
	welcomeText.setColor(sf::Color::Red);
	welcomeText.setString("Ticketomat");
	welcomeText.setCharacterSize(50);

	sf::FloatRect textBounds = welcomeText.getLocalBounds();
	welcomeText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	welcomeText.setPosition(window.getSize().x / 2.f, 100);
	
	
	
}

