#include <SFML/Graphics.hpp>
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/Input.hpp"
#include "Player/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Animation.hpp"
#include "SaltyEngine/SFML/Scene.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine {
    #define AssetManager SFML::AssetManager::Instance()
}

SaltyEngine::GameObject *explosion() {
	SaltyEngine::SFML::Texture *texture = SaltyEngine::AssetManager.GetTexture("nacelle2");
	// Create monster with sprites
	SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
	monster->AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)), SaltyEngine::Layout::normal);
	monster->AddComponent<SaltyEngine::PlayerController>();
	monster->AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
	SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
	clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-150, 70, 30, 20)));
	clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-120, 70, 30, 20)));
	clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-90, 70, 30, 20)));
	clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-60, 70, 30, 20)));
	clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-30, 70, 30, 20)));
	clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270, 70, 30, 20)));
	clip->SetFrameRate(20);
	monster->GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");
	return monster;
}

int main()
{
	SaltyEngine::AssetManager.LoadAssets();
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	// Set Renderer and EventManager
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	// Create monster with sprites
//	SaltyEngine::Instantiate();
	SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
	//SaltyEngine::GameObject *player = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Player");

	std::cout << "Monster = " << monster << std::endl;
	//std::cout << "Player = " << player << std::endl;

    std::cout << "Pos = " << monster->transform.position << std::endl;

	// Push scene int SaltyEngine

	//*scene << player;
	*scene << monster;

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return (0);
}
