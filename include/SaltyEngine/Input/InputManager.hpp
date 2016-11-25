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

            static bool     GetButtonPressed(Mouse::Button button) {
                return Input::GetButtonPressed(button);
            }

            static Vector2i GetPosition() {
                return Input::GetPosition();
            }

            static Vector2i GetPositionRelative() {
                return Input::GetPositionRelative();
            }
        };
    }
}

/// Example Usage
/// std::vector<SaltyEngine::Input::KeyCode::Key> keys = InputKey::GetCurrentKeys();
/// for (std::vector<SaltyEngine::Input::KeyCode::Key>::const_iterator it = keys.begin(); it != keys.end(); ++it) {
/// std::cout << *it << std::endl;
/// }
///
/// if (InputKey::GetKey("A")) {
/// std::cout << "A Once" << std::endl;
/// }
/// if (InputKey::GetKeyDown("A")) {
/// std::cout << "A Down" << std::endl;
/// }
/// if (InputKey::GetKeyUp("A")) {
/// std::cout << "A Up" << std::endl;
/// }
///
/// std::cout << InputKey::GetButtonPressed(SaltyEngine::Input::Mouse::Left) << std::endl;
/// std::cout << InputKey::GetPosition() << std::endl;
/// std::cout << InputKey::GetPositionRelative() << std::endl;


#endif //INPUTMANAGER_HPP
