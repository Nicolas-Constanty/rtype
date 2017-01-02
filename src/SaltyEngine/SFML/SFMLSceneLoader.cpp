#include "SaltyEngine/SFML/SFMLSceneLoader.hpp"
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/AAssetManager.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		/**
         * @fn	SaltyEngine::SaltyEngine()
         *
         * @brief	Default constructor init m_fps at DEFAULT_FRAME_RATE.
         */

		SFMLSceneLoader::SFMLSceneLoader()
		{
		}

		/**
         * @fn	SaltyEngine::~SaltyEngine()
         *
         * @brief	Destructor.
         */

		SFMLSceneLoader::~SFMLSceneLoader()
		{
//			SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();
//			SaltyEngine::SFML::Scene *scene2 = new SaltyEngine::SFML::Scene();
//			SaltyEngine::SFML::Scene *scene3 = new SaltyEngine::SFML::Scene();
//
//			scene->SetName("sceneConnection");
//			scene3->SetName("scene2");
//			scene2->SetName("sceneRoom");
//
//			SaltyEngine::Engine::Instance().SetArguments(ac, (const char**)av);
//			SaltyEngine::Engine::Instance() << scene;
//			SaltyEngine::Engine::Instance() << scene2;
//			SaltyEngine::Engine::Instance() << scene3;
//
//			SaltyEngine::SceneDefault *sceneDefault = SaltyEngine::SFML::AssetManager::Instance().LoadSize(map);
//
//			unsigned int x = (unsigned int) sceneDefault->size.x; // 1920
//			unsigned int y = (unsigned int) sceneDefault->size.y; // 1080
//			SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(x * 2, y * 2), "R-Type Launcher");
//			SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer);
//			SaltyEngine::SFML::PhysicsHandler *ph = new SaltyEngine::SFML::PhysicsHandler(x, y, false);
//			SaltyEngine::Engine::Instance().SetPhysicsHandler(ph);
//			// Set Renderer and EventManager
//			Singleton<SaltyEngine::Engine>::Instance().SetRenderer(renderer);
//			Singleton<SaltyEngine::Engine>::Instance().SetEventManager(event_manager);
//
////	SaltyEngine::Engine::Instance().SetFrameRate(30);
//
//			// Create Scene
//			sceneDefault = SaltyEngine::SFML::AssetManager::Instance().LoadScene(map);
//			scene->SetScale(sceneDefault->scale);
		}

        AScene *SFMLSceneLoader::LoadScene(std::string const &sceneName)
		{
            AScene *scene = SaltyEngine::Engine::Instance().GetSceneByName(sceneName);
			if (!scene)
			{
				scene = new SaltyEngine::SFML::Scene();
				scene->SetName(sceneName);
				SaltyEngine::Engine::Instance() << scene;
			}
			m_scene = SaltyEngine::SFML::AssetManager::Instance().LoadSize(sceneName);
			Renderer *renderer = dynamic_cast<Renderer *>(SaltyEngine::Engine::Instance().GetRenderer());
			unsigned int x = (unsigned int) m_scene->size.x;
			unsigned int y = (unsigned int) m_scene->size.y;
			if (renderer)
			{
				renderer->setSize(sf::Vector2u(x * 2, y * 2));
				renderer->setView(sf::View(sf::FloatRect(0.f, 0.f, x * 2, y * 2)));
			} else {

				renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(x * 2, y * 2), "R-Type Launcher");
				SaltyEngine::Engine::Instance().SetRenderer(renderer);
			}
			if (SaltyEngine::Engine::Instance().GetEventManager() == nullptr)
			{
				SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer);
				SaltyEngine::Engine::Instance().SetEventManager(event_manager);
			}
			if (SaltyEngine::Engine::Instance().GetPhysicsHandler() == nullptr)
			{
				SaltyEngine::SFML::PhysicsHandler *ph = new PhysicsHandler(x, y, false);
				SaltyEngine::Engine::Instance().SetPhysicsHandler(ph);
			}
			PhysicsHandler *a = dynamic_cast<PhysicsHandler *>(SaltyEngine::Engine::Instance().GetPhysicsHandler());
			if (a)
				a->SetSize((unsigned int) m_scene->size.x, (unsigned int) m_scene->size.y);
			m_scene = SaltyEngine::SFML::AssetManager::Instance().LoadScene(sceneName);
			for (std::pair<std::string, SaltyEngine::PrefabDefault> it :  m_scene->objects)
            {
				Debug::PrintInfo("Try Load");
                if (it.second.instantiate) {
					Debug::PrintInfo("Instantiate");
                    SaltyEngine::Instantiate(it.first, it.second.pos, 0);
                }
            }
            return scene;
		}

		std::list<std::pair<std::string, PrefabDefault>> const &SFMLSceneLoader::GetSceneObjects(void) const
		{
			return m_scene->objects;
		}

		Vector2 SFMLSceneLoader::GetSceneScale(void) const
		{
			return m_scene->scale;
		}
	}
}
