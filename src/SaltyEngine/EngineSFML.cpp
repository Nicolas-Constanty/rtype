#include "SaltyEngine/EngineSFML.hpp"
#include "SaltyEngine/SFML.hpp"

namespace SaltyEngine
{
	/**
	 * @fn	SaltyEngine::SaltyEngine()
	 *
	 * @brief	Default constructor init m_fps at DEFAULT_FRAME_RATE.
	 */

	EngineSFML::EngineSFML()
	{
    }

	/**
	 * @fn	SaltyEngine::~SaltyEngine()
	 *
	 * @brief	Destructor.
	 */

	EngineSFML::~EngineSFML()
	{
	}

    AScene *EngineSFML::CreateScene(void) const
    {
		return new SaltyEngine::SFML::Scene();
    }

    std::list<std::pair<string, Vector2f>> const& EngineSFML::GetSceneObjects(std::string const &sceneName) const
    {
		return SaltyEngine::SFML::AssetManager::Instance().LoadScene(sceneName)->objects;
    }

    Vector2 EngineSFML::GetSceneScale(std::string const &sceneName) const
    {
        return SaltyEngine::SFML::AssetManager::Instance().LoadScene(sceneName)->scale;
    }
}
