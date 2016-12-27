//
// Created by wery_a on 28/11/16.
//

#ifndef RTYPE_DEFAULTEVENTMANAGER_HPP
#define RTYPE_DEFAULTEVENTMANAGER_HPP

#include "IEventManager.hpp"

namespace SaltyEngine {
    namespace Input {
        class LIB_EXPORT DefaultEventManager : public IEventManager {
        public:
            DefaultEventManager() {};

            virtual ~DefaultEventManager() {};

            void Update() {};
        };
    }
}
#endif //RTYPE_DEFAULTEVENTMANAGER_HPP
