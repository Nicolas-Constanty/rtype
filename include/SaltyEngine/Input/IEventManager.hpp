//
// Created by wery_a on 28/11/16.
//

#ifndef RTYPE_IEVENTMANAGER_HPP
#define RTYPE_IEVENTMANAGER_HPP

#include "Common/DLLexport.hpp"

namespace SaltyEngine {
    namespace Input {
        class LIB_EXPORT IEventManager {
        public:
            virtual ~IEventManager() {};

            virtual void Update() = 0;
        };
    }
}
#endif //RTYPE_IEVENTMANAGER_HPP
