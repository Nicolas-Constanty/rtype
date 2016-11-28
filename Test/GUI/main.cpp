#include <SFML/Graphics.hpp>
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Debug.hpp"

int main(int ac, char **av)
{
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(500, 500), "R-Type Launcher");

	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

	SaltyEngine::SFML::Texture *texture = new SaltyEngine::SFML::Texture();
	if (!texture->loadFromFile("../../Assets/Textures/Image.png"))
	{
		SaltyEngine::Debug::PrintError("Failed to load texture");
		return (1);
	}
	SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(texture);
	player->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::GUI);
	// Set SFML Renderer
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);

	// Create Scene
	SaltyEngine::Scene *scene(new SaltyEngine::Scene());

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return (0);
}

//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//
//	//std::shared_ptr<SaltyEngine::Object> go = SaltyEngine::Object::Instantiate("DefaultMonster");
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//
//	return 0;
//}
