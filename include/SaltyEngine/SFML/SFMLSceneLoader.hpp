#pragma once

#ifndef SALTENGINESFML_HPP_
#define SALTENGINESFML_HPP_

#include "SaltyEngine/SFML/Scene.hpp"
#include "SaltyEngine/ISceneLoader.hpp"
#include "SaltyEngine/AAssetManager.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        class SFMLSceneLoader : public ISceneLoader
        {
        public:
            SFMLSceneLoader();

            virtual ~SFMLSceneLoader();

            void LoadScene(std::string const &sceneName) override;

            Vector2 GetSceneScale(void) const override;

            std::list<std::pair<std::string, Vector2f>> const &GetSceneObjects(void) const override;

        private:
            SceneDefault *m_scene = nullptr;
        };
    }
}

#endif // !SALTENGINESFML_HPP_