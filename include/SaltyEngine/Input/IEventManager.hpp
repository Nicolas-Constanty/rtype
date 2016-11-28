//
// Created by wery_a on 28/11/16.
//

#ifndef RTYPE_IEVENTMANAGER_HPP
#define RTYPE_IEVENTMANAGER_HPP

namespace SaltyEngine {
    namespace Input {
        class IEventManager {
        public:
            virtual ~IEventManager() {};

            virtual void Update() = 0;
        };
    }
}
#endif //RTYPE_IEVENTMANAGER_HPP
