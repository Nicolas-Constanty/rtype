//
// Created by wery_a on 24/11/16.
//

#ifndef AXIS_HPP
#define AXIS_HPP

#include <map>
#include <iostream>
#include "SaltyEngine/Input/KeyCodes.hpp"

namespace SaltyEngine {
    namespace Input {
        class Axis {
        public:
            Axis(std::map<KeyCode::Key, float> keys);
            Axis(std::map<KeyCode::Key, float> keys, std::pair<unsigned int, MotionController::Axis> joystick);
            Axis(std::pair<unsigned int, MotionController::Axis> joystick);
            virtual ~Axis();

        private:
            const std::map<KeyCode::Key, float> m_keys;
            const std::pair<unsigned int, MotionController::Axis>   m_joystick;
        public:
            const std::map<KeyCode::Key, float> &getKeys() const;
            const std::pair<unsigned int, MotionController::Axis>   &getJoystick() const;

            template <class Input>
            float getValue() const {
                float   ret = 0;

                if (!m_keys.empty()) {
                    for (std::map<KeyCode::Key, float>::const_iterator it = m_keys.begin(); it != m_keys.end(); ++it) {
                        if (Input::IsKeyDown(it->first)) {
                            ret = it->second;
                        }
                    }
                }
                if (Input::IsJoystickConnected(m_joystick.first) && Input::HasAxis(m_joystick.first, m_joystick.second)) {
                    ret = Input::GetAxisPosition(m_joystick.first, m_joystick.second) / 100.0f;
                }
                return ret;
            }
        };
    }
}

#endif //AXIS_HPP
