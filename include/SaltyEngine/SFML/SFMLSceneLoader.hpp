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

            AScene *LoadScene(std::string const &sceneName) override;

            Vector2 GetSceneScale(void) const override;

            std::list<std::pair<std::string, PrefabDefault>> const &GetSceneObjects(void) const override;

        private:
            SceneDefault *m_scene = nullptr;
        public:
            SceneDefault *GetScene() const;
        };
    }
}

#endif // !SALTENGINESFML_HPP_