#include <SFML/Graphics.hpp>
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/Input.hpp"
#include "ClientLauncher/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Animation.hpp"

int main(int ac, char **av)
{
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());

	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

	// Create Button
	SaltyEngine::SFML::Texture *texture = new SaltyEngine::SFML::Texture();
	if (!texture->loadFromFile("../../../Assets/Textures/Image.png"))
	{
		SaltyEngine::Debug::PrintError("Failed to load texture");
		return (1);
	}
	SaltyEngine::SFML::Rect *rect = new SaltyEngine::SFML::Rect(10, 10, 100, 100);
	SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(texture, rect);
	player->AddComponent<SaltyEngine::GUI::SFML::Button>(spr);
	player->AddComponent<SaltyEngine::PlayerController>();
	// Set SFML Renderer
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);
	// Create Scene
	SaltyEngine::Scene *scene(new SaltyEngine::Scene());

	// Create monster with sprites
	SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
	std::cout << "Monster = " << monster << std::endl;
	SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
	clip->AddSprite(new SaltyEngine::SFML::Sprite(texture));
	*clip << new SaltyEngine::SFML::Sprite(texture);
	SaltyEngine::Animation<sf::Vector2i> anim(monster);
	anim.AddClip(clip, "Walk");

	*scene << player;
	*scene << monster;
	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return (0);
}
