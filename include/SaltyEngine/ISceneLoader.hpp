//
// Created by veyrie_f on 31/12/16.
//

#ifndef RTYPE_IENGINESFML_HPP
#define RTYPE_IENGINESFML_HPP

#include "SaltyEngine/AScene.hpp"
namespace SaltyEngine
{
    class ISceneLoader
    {
    public:
        virtual ~ISceneLoader()
        {}

        virtual void LoadScene(std::string const &sceneName) = 0;
        virtual Vector2 GetSceneScale(void) const = 0;
        virtual std::list<std::pair<std::string, Vector2f>> const &GetSceneObjects(void) const = 0;
    };
}
#endif //RTYPE_IENGINESFML_HPP
