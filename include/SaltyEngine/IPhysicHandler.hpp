//
// Created by nicolas-constanty on 17/12/16.
//

#ifndef RTYPE_IPHYSICHANDLER_HPP
#define RTYPE_IPHYSICHANDLER_HPP

#include "Common/DLLexport.hpp"

namespace SaltyEngine
{
    class LIB_EXPORT IPhysicsHandler
    {
    public:
        virtual void Clear() = 0;
        virtual void Update() = 0;
        virtual void Run() = 0;
        virtual void Display() = 0;
        virtual void Collide() = 0;
    };

    class LIB_EXPORT APhysicsHandler : IPhysicsHandler
    {
    public:
        APhysicsHandler(unsigned int x, unsigned int y) : m_size(x, y) {};
        unsigned int GetSizeX() const
        {
            return m_size.x;
        }

        unsigned int GetSizeY() const
        {
            return m_size.y;
        }

        const Vector2ui &GetSize() const {
            return m_size;
        }

        virtual void Clear() = 0;
        virtual void Update() = 0;
        virtual void Run() = 0;
        virtual void Display() = 0;
        virtual void Collide() = 0;

    protected:
        Vector2ui m_size;
    };
}

#endif //RTYPE_IPHYSICHANDLER_H
