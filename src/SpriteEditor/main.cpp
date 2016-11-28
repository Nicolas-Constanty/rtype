#include <SFML/Graphics.hpp>
#include <iostream>
#include "SpriteEditor/Button.hpp"
#include "SpriteEditor/ExportButton.hpp"
#include "SpriteEditor/SelectRect.hpp"
#include "SpriteEditor/DialogBox.hpp"
#include "SpriteEditor/Texture.hpp"

#define ASSET_DIRECTORY "../../../Assets/"

void run(SpriteEditor::Texture texture)
{
	float margin_left = 30;
	float margin_top = 30;
	sf::Sprite sprite;
	sf::Vector2u size = texture.getSize();
	sprite.setTexture(texture);
	sprite.move(sf::Vector2f(0.01f, 0.01f));
	
	// SELECT BUTTON
	// SELECT NORM
	sf::Texture select_norm;
	if (!select_norm.loadFromFile(ASSET_DIRECTORY "Textures/Select.png"))
		std::cout << "Bad diretory" << std::endl;
	// SELECT OVER
	sf::Texture select_over;
	if (!select_over.loadFromFile(ASSET_DIRECTORY "Textures/SelectOver.png"))
		std::cout << "Bad diretory" << std::endl;
	SpriteEditor::Button select_button(select_norm, select_over);
	sprite.setPosition(margin_left, select_button().getGlobalBounds().height + 1 + margin_top);
	// DIALOGBOX
	SpriteEditor::DialogBox box("Enter filename here :");
	// EXPORT BUTTON
	// EXPORT NORM
	sf::Texture export_norm;
	if (!export_norm.loadFromFile(ASSET_DIRECTORY "Textures/Export.png"))
		std::cout << "Bad diretory" << std::endl;
	// EXPORT OVER
	sf::Texture export_over;
	if (!export_over.loadFromFile(ASSET_DIRECTORY "Textures/ExportOver.png"))
		std::cout << "Bad diretory" << std::endl;
	SpriteEditor::ExportButton export_button(export_norm, export_over, box);
	export_button.SetPosition(sf::Vector2f(size.x + margin_left * 2 - export_button().getGlobalBounds().width, 0));
	// PANEL
	sf::RectangleShape panel(sf::Vector2f(size.x + margin_left * 2, select_button().getGlobalBounds().height + 1));
	panel.setFillColor(sf::Color(80, 80, 80, 255));
	sf::Color background = sf::Color(50, 50, 50, 255);
	// WINDOW
	sf::RenderWindow window(sf::VideoMode(size.x + static_cast<unsigned int>(margin_left * 2), size.y + static_cast<unsigned int>(select_button().getGlobalBounds().height + 2 + margin_top * 2)), "Salty Sprite Editor");
	// SELECTRECT
	SpriteEditor::SelectRect select_rect(sprite.getGlobalBounds());
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				select_rect.OnClic(event);
				export_button.OnClic(event);
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				select_button.OnMouseOver(event);
				export_button.OnMouseOver(event);
				select_rect.Update(event);
			}
		}
		while (box.isOpen() && box.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				box.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					box.close();
				else if (event.key.code == sf::Keyboard::Return)
				{
					std::string fn = texture.GetFilename();
					export_button.Export(box.OnValidate(), select_rect.GetExport(), fn);
					box.close();
				}
			}
			else if (event.type == sf::Event::TextEntered)
			{
				if (box.isOpen())
					box.OnWrite(event);
			}
		}
		window.clear(background);
		window.draw(panel);
		window.draw(select_button());
		window.draw(export_button());
		window.draw(sprite);
		window.draw(select_rect);
		window.display();
		if (box.isOpen())
			box.display();
	}
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "USAGE : ./SpriteEditor [FILENAME]";
		return (0);
	}
	SpriteEditor::Texture texture;
	if (!texture.loadFromFile(av[1]))
	{
		std::cout << "Bad diretory" << std::endl;
		return (1);
	}
	run(texture);
	return 0;
}