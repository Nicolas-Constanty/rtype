//
// Created by wery_a on 24/11/16.
//

#ifndef AXIS_HPP
#define AXIS_HPP

#include <map>
#include "SaltyEngine/Input/KeyCodes.hpp"

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

            template <class Input>
            float getValue() const {
                float   ret = 0;
                for (std::map<KeyCode::Key, float>::const_iterator it = m_keys.begin(); it != m_keys.end(); ++it) {
                    if (Input::IsKeyDown(it->first)) {
                        ret = it->second;
                    }
                }
                return ret;
            }
        };
    }
}

#endif //AXIS_HPP
