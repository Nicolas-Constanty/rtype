//
// Created by wery_a on 24/11/16.
//

#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include "KeyCodes.hpp"

namespace SaltyEngine {
    namespace Input {
#include "KeyCodesString.inl"
        template <class Input>
        class InputManager {
        public:
            static bool GetKey(KeyCode::Key key) {
                Input::isKey(key);
            }

            static bool GetKeyDown(KeyCode::Key key) {
                Input::isKeyDown(key);
            }

            static bool GetKeyUp(KeyCode::Key key) {
                Input::isKeyUp(key);
            }

            static bool GetKey(std::string const &key) {
                GetKey(m_keycodes.find(key)->second);
            }

            static bool GetKeyDown(std::string const &key) {
                GetKeyDown(m_keycodes.find(key)->second);
            }

            static bool GetKeyUp(const std::string &key) {
                GetKeyUp(m_keycodes.find(key)->second);
            }

            static std::vector<KeyCode::Key>    GetCurrentKeys() {
                return Input::GetCurrentKeys();
            }
        };
    }
}

#endif //INPUTMANAGER_HPP
