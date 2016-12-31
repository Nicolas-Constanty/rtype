#pragma once

#ifndef SALTENGINESFML_HPP_
#define SALTENGINESFML_HPP_

#include "Common/DLLexport.hpp"
#include "SaltyEngine/SFML/Scene.hpp"
#include "SaltyEngine/ISceneLoader.hpp"
#include "SaltyEngine/AAssetManager.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        class LIB_EXPORT SFMLSceneLoader : public ISceneLoader
        {
        public:
            SFMLSceneLoader();

            virtual ~SFMLSceneLoader();

            AScene *CreateScene(void) const override;

            Vector2 GetSceneScale(std::string const &sceneName) const override;

            std::list<std::pair<string, Vector2f>> const &GetSceneObjects(std::string const &sceneName) const override;
        };
    }
}

#endif // !SALTENGINESFML_HPP_