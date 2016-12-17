//
// Created by nicolas-constanty on 17/12/16.
//

#ifndef RTYPE_IPHYSICHANDLER_HPP
#define RTYPE_IPHYSICHANDLER_HPP

namespace SaltyEngine
{
    class IPhysicsHandler
    {
    public:
        virtual void Clear() = 0;
        virtual void Update() = 0;
        virtual void Run() = 0;
        virtual void Display() = 0;
    };
}

#endif //RTYPE_IPHYSICHANDLER_H
