//
// Created by wery_a on 24/11/16.
//

#include "SaltyEngine/Input/Axis.hpp"
#include "SaltyEngine/Input/Mapping.hpp"

namespace SaltyEngine {
    namespace Input {
        Axis::Axis(std::map<KeyCode::Key, float> keys) :m_keys(keys) {

        }

        Axis::~Axis() {

        }

        const std::map<KeyCode::Key, float>& Axis::getKeys() {
            return m_keys;
        }

        float Axis::getValue(KeyCode::Key key) {
            return m_keys.find(key)->second;
        }
    }
}
