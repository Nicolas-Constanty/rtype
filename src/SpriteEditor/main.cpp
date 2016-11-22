#include <SFML/Graphics.hpp>
#include <iostream>
#include "SpriteEditor/Button.hpp"

#define ASSET_DIRECTORY "../../../Assets/Textures/"

void run(sf::Texture texture)
{
	sf::Sprite sprite;
	sf::Vector2u size = texture.getSize();
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Salty Sprite Editor");
	sprite.setTexture(texture);
	sprite.move(sf::Vector2f(0.01, 0.01));
	sf::Texture select;
	if (!select.loadFromFile(ASSET_DIRECTORY "Select.png"))
		std::cout << "Bad diretory" << std::endl;
	SpriteEditor::Button select_button(select);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.draw(select_button());
		window.display();
	}
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "USAGE : ./SpriteEditor [FILENAME]";
		return (0);
	}
	sf::Texture texture;
	if (!texture.loadFromFile(av[1]))
	{
		std::cout << "Bad diretory" << std::endl;
		return (1);
	}
	run(texture);
	return 0;
}