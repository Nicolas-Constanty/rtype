#pragma once

#ifndef SALTENGINESFML_HPP_
#define SALTENGINESFML_HPP_

#include "SaltyEngine/SFML/Scene.hpp"
#include "SaltyEngine/ISceneLoader.hpp"
#include "AAssetManager.hpp"

namespace SaltyEngine
{
	class EngineSFML : public ISceneLoader
	{
	public:
		EngineSFML();
		virtual ~EngineSFML();

        AScene *CreateScene(void) const override;

        Vector2 GetSceneScale(std::string const &sceneName) const override;

        std::list<std::pair<string, Vector2f>> const& GetSceneObjects(std::string const &sceneName) const override;
	};

}

#endif // !SALTENGINESFML_HPP_