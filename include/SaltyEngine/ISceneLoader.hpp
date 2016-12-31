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

        virtual AScene *CreateScene(void) const = 0;
        virtual Vector2 GetSceneScale(std::string const &sceneName) const = 0;
        virtual std::list<std::pair<std::string, Vector2f> > const& CreateSceneDefault(std::string const &sceneName) const = 0;
    };
}
#endif //RTYPE_IENGINESFML_HPP
