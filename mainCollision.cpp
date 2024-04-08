#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collision/Collision.hpp"
#include <SFML/Window.hpp>

enum class direction {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

void move(sf::VertexArray& vertices, triangle& t, direction dir) {
	if (dir == direction::RIGHT) {
		for (int i = 0; i < 3; i++) {
			vertices[i].position.x += 10;
			t.points[i].x += 10;
		}
	}   if (dir == direction::LEFT) {
		for (int i = 0; i < 3; i++) {
			vertices[i].position.x -= 10;
			t.points[i].x -= 10;
		}
	}
	else if (dir == direction::UP) {
		for (int i = 0; i < 3; i++) {
			vertices[i].position.y -= 10;
			t.points[i].y -= 10;
		}
	} if (dir == direction::DOWN) {
		for (int i = 0; i < 3; i++) {
			vertices[i].position.y += 10;
			t.points[i].y += 10;
		}
	}

}

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Collision - two lines segment intersection", sf::Style::Default, settings);
	
	triangle triangle1 = { {
		vec2{400.f, 20.f},
		vec2{350.f, 300.f},
		vec2{300.f, 300.f}
	} };

	triangle triangle2 = { {
		vec2{400.f, 250.f},
		vec2{700.f, 10.f},
		vec2{560.f, 10.f}
	} };

	bool isOverlap = false;
	bool isTriangle1Moving = false;
	bool isTriangle2Moving = false;


	sf::VertexArray verticesT1(sf::Triangles, 3);
	sf::VertexArray verticesT2(sf::Triangles, 3);
	sf::VertexArray tempVertices(sf::Triangles, 3);

	for (int i = 0; i < 3; i++) {
		verticesT1[i].position = sf::Vector2f(triangle1.points[i].x, triangle1.points[i].y);
		verticesT1[i].color = sf::Color::Green;

		verticesT2[i].position = sf::Vector2f(triangle2.points[i].x, triangle2.points[i].y);
		verticesT2[i].color = sf::Color::Blue;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Right) {
					move(verticesT1, triangle1, direction::RIGHT);
					isTriangle1Moving = true;
					isTriangle2Moving = false;
				} if (event.key.code == sf::Keyboard::Left) {
					move(verticesT1, triangle1, direction::LEFT);
					isTriangle1Moving = true;
					isTriangle2Moving = false;
				} if (event.key.code == sf::Keyboard::Up) {
					move(verticesT1, triangle1, direction::UP);
					isTriangle1Moving = true;
					isTriangle2Moving = false;
				} if (event.key.code == sf::Keyboard::Down) {
					move(verticesT1, triangle1, direction::DOWN);
					isTriangle1Moving = true;
					isTriangle2Moving = false;
				}

				if (event.key.code == sf::Keyboard::D) {
					move(verticesT2, triangle2, direction::RIGHT);
					isTriangle1Moving = false;
					isTriangle2Moving = true;
				} if (event.key.code == sf::Keyboard::A) {
					move(verticesT2, triangle2, direction::LEFT);
					isTriangle1Moving = false;
					isTriangle2Moving = true;
				} if (event.key.code == sf::Keyboard::W) {
					move(verticesT2, triangle2, direction::UP);
					isTriangle1Moving = false;
					isTriangle2Moving = true;
				} if (event.key.code == sf::Keyboard::S) {
					move(verticesT2, triangle2, direction::DOWN);
					isTriangle1Moving = false;
					isTriangle2Moving = true;
				}
			}

			isOverlap = isColliding(triangle1, triangle2);

			sf::Color colorT1 = isOverlap && isTriangle1Moving ? sf::Color::Red : sf::Color::Green;
			sf::Color colorT2 = isOverlap && isTriangle2Moving ? sf::Color::Red : sf::Color::Blue;
			
			for (int i = 0; i < 3; i++) {
				verticesT1[i].color = colorT1;
				verticesT2[i].color = colorT2;
			}


		}

		window.clear();
		window.draw(verticesT1);
		window.draw(verticesT2);
		window.display();
	}

	return 0;
}