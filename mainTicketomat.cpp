#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    
    sf::RenderWindow window(sf::VideoMode(600, 900), "SFML Window");
    std::string pathToFonts = "..\\..\\..\\Ticketomat\\Fonts\\";    
    std::string pathToImages = "..\\..\\..\\Ticketomat\\Images\\";
    

    sf::Texture oneMoneyTxr;
    if (!(oneMoneyTxr.loadFromFile(pathToImages + "oneMoney.png"))) {
        return EXIT_FAILURE;
    }
    
    sf::Font arialFont;    
    if (!(arialFont.loadFromFile(pathToFonts + "ARIAL.TTF"))) {
        return EXIT_FAILURE;
    }

    sf::Text text;    
    text.setFont(arialFont);
    text.setColor(sf::Color::Red);    
    text.setString("Hello from here i am kajetan");
    text.setCharacterSize(40);

    sf::CircleShape oneMoneyBtn(50.f);
    oneMoneyBtn.setTexture(&oneMoneyTxr);   
    oneMoneyBtn.setPosition(300, 300);


    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

      
        window.clear();

        
        
        window.draw(text);
        window.draw(oneMoneyBtn);
        

        
        window.display();
    }

    return 0;
}
