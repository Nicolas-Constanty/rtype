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
