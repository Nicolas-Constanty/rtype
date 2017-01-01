#include "SaltyEngine/SFML/SFMLSceneLoader.hpp"
#include "SaltyEngine/SFML.hpp"

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
		}

		void SFMLSceneLoader::LoadScene(std::string const &sceneName)
		{
			m_scene = SaltyEngine::SFML::AssetManager::Instance().LoadSize(sceneName);
			Renderer *r = dynamic_cast<Renderer *>(SaltyEngine::Engine::Instance().GetRenderer());
			r->setSize(sf::Vector2u((unsigned int) m_scene->size.x * 2, (unsigned int) m_scene->size.y * 2));
			r->setView(sf::View(sf::FloatRect(0.f, 0.f, m_scene->size.x * 2, m_scene->size.y * 2)));
			PhysicsHandler *a = dynamic_cast<PhysicsHandler *>(SaltyEngine::Engine::Instance().GetPhysicsHandler());
			if (a)
				a->SetSize((unsigned int) m_scene->size.x, (unsigned int) m_scene->size.y);
			m_scene = SaltyEngine::SFML::AssetManager::Instance().LoadScene(sceneName);
		}

		std::list<std::pair<std::string, Vector2f>> const &SFMLSceneLoader::GetSceneObjects(void) const
		{
			return m_scene->objects;
		}

		Vector2 SFMLSceneLoader::GetSceneScale(void) const
		{
			return m_scene->scale;
		}
	}
}
