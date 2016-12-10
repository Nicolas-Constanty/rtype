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
#include "Prefabs/Monster/MonsterController.hpp"
#include "SaltyEngine/SFML/Scene.hpp"

#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine {
#define AssetManager SFML::AssetManager::Instance()
}

int main() {
    SaltyEngine::AssetManager.LoadAssets();
    SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
    SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
    // Set Renderer and EventManager
    Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);
    Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);

    // Create Scene
    SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

    SaltyEngine::Instantiate();
    SaltyEngine::GameObject *monster = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster");
    SaltyEngine::GameObject *player = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Player");

    std::cout << "Monster = " << monster << std::endl;
    std::cout << "Player = " << player << std::endl;

    *scene << player;
    *scene << monster;

    // Push scene int SaltyEngine
    Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

    // Run the SaltyEngine with default Scene 0
    Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
    return (0);
}