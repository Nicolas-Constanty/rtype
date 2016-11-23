#include <iostream>
//#include <SFML/Graphics.hpp>
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/Object.hpp"
#include "Common/DllLoader.hpp"

/**
 * If there is no window, see : http://stackoverflow.com/questions/2627900/what-can-explain-stdcout-not-to-display-anything
 */

int main()
{
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	std::shared_ptr<SaltyEngine::Object> go = SaltyEngine::Instantiate("DefaultMonster", SaltyEngine::Vector(10, 10), 10);
	DllLoader *dll = new DllLoader();

	dll->Load("Monster.dll");
	SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)dll->Call("GetMonster");
	std::cout << monster->GetName() << std::endl;
	dll->Unload();

	//while (window.isOpen())
	//{
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//	}

	//	window.clear();
	//	window.draw(shape);
	//	window.display();
	//}

	return 0;
}
