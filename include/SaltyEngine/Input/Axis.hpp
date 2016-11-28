//
// Created by wery_a on 24/11/16.
//

#ifndef AXIS_HPP
#define AXIS_HPP

#include <map>
#include "KeyCodes.hpp"

namespace SaltyEngine {
    namespace Input {
        class Axis {
        public:
            Axis(std::map<KeyCode::Key, float> keys);
            virtual ~Axis();

        private:
            const std::map<KeyCode::Key, float> m_keys;
        public:
            const std::map<KeyCode::Key, float> &getKeys();
            float getValue(KeyCode::Key key);
        };
    }
}

#endif //AXIS_HPP
