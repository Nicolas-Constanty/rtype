//
// Created by wery_a on 24/11/16.
//
#include "SaltyEngine/Input/Axis.hpp"


namespace SaltyEngine {
    namespace Input {
        Axis::Axis(std::map<KeyCode::Key, float> keys) :m_keys(keys) {

        }

        Axis::Axis(std::map<KeyCode::Key, float> keys, std::pair<unsigned int, MotionController::Axis> joystick)
                : m_keys(keys), m_joystick(joystick) {

        }

        Axis::Axis(std::pair<unsigned int, MotionController::Axis> joystick)
                : m_joystick(joystick) {

        }

        Axis::~Axis() {

        }

        const std::map<KeyCode::Key, float>& Axis::getKeys() const {
            return m_keys;
        }

        const std::pair<unsigned int, MotionController::Axis>& Axis::getJoystick() const {
            return m_joystick;
        }
    }
}
