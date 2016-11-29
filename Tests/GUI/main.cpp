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
#include "Monster/MonsterController.hpp"

int main(int ac, char **av)
{
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());

	SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");

	// Create Button
	SaltyEngine::SFML::Texture *texture = new SaltyEngine::SFML::Texture();
	if (!texture->loadFromFile("../../Assets/Textures/Image.png"))
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
	MonsterController *c = monster->GetComponent<MonsterController>();
	c->enabled = false;
	monster->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);
	SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>("WalkAnim", 10);
	for (int i = 10; i < 20; ++i)
	{
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(10 * i, 10 * i, 100, 100)));
	}
	*clip << new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(20, 20, 100, 100));
	monster->AddComponent < SaltyEngine::Animation<sf::Vector2i> >(true, SaltyEngine::AnimationConstants::WrapMode::PING_PONG);
	monster->GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");

	*scene << player;
	*scene << monster;
	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return (0);
}
