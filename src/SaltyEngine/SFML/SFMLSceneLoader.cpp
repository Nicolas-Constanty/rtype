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

		AScene *SFMLSceneLoader::CreateScene(void) const
		{
			return new SaltyEngine::SFML::Scene();
		}

		std::list<std::pair<string, Vector2f>> const &SFMLSceneLoader::GetSceneObjects(std::string const &sceneName) const
		{
			return SaltyEngine::SFML::AssetManager::Instance().LoadScene(sceneName)->objects;
		}

		Vector2 SFMLSceneLoader::GetSceneScale(std::string const &sceneName) const
		{
			return SaltyEngine::SFML::AssetManager::Instance().LoadScene(sceneName)->scale;
		}
	}
}
