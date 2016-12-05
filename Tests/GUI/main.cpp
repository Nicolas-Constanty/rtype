#include <SFML/Graphics.hpp>
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/Input.hpp"
#include "Player/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Animation.hpp"
#include "Monster/MonsterController.hpp"
#include "SaltyEngine/SFML/Scene.hpp"

#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine {
    #define AssetManager SFML::AssetManager::Instance()
}

SaltyEngine::GameObject *monster() {
    SaltyEngine::SFML::Texture *texture = SaltyEngine::AssetManager.GetTexture("monster");
    // Create monster with sprites
    SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
    monster->AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)), SaltyEngine::Layout::normal);
    monster->AddComponent<SaltyEngine::PlayerController>();
    monster->AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
    clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)));
    clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(34, 0, 34, 34)));
    clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(68, 0, 34, 34)));
    clip->SetFrameRate(5);
    monster->GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");
    return monster;
}

SaltyEngine::GameObject *explosion() {
    SaltyEngine::SFML::Texture *texture = SaltyEngine::AssetManager.GetTexture("nacelle2");
    // Create monster with sprites
    SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
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
	SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	// Set Renderer and EventManager
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);

	// Set SFML Renderer
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);
	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	//SaltyEngine::GameObject *player = new SaltyEngine::GameObject("Player");
	//player->AddComponent<SaltyEngine::PlayerController>();
	//player->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);

	/*SaltyEngine::GameObject *toto = (SaltyEngine::GameObject*)::SaltyEngine::Instantiate("Monster");
	toto->AddComponent<SaltyEngine::SFML::BoxCollider2D>();*/
	//toto->transform.position = SaltyEngine::Vector2(300, 300);
	// Create monster with sprites
	SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
	SaltyEngine::GameObject *player = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Player");

	std::cout << "Monster = " << monster << std::endl;
	std::cout << "Player = " << player << std::endl;

	rect = new SaltyEngine::SFML::Rect(100, 10, 100, 100);
	spr = new SaltyEngine::SFML::Sprite(texture, rect);
	SaltyEngine::GameObject *monster2 = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
	monster2->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);
	monster2->AddComponent<SaltyEngine::SFML::BoxCollider2D>();
	monster2->transform.position.x = 800;
	monster2->transform.position.y = 200;

    //std::cout << "xx" << monster->GetComponent<MonsterController>() << std::endl;
    //std::cout << monster2->GetComponent<MonsterController>() << std::endl;
	//*scene << player;

	/**scene << monster;
	*scene << monster2;*/
	// Push scene int SaltyEngine

	*scene << player;
	*scene << monster;

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
	return (0);
}
