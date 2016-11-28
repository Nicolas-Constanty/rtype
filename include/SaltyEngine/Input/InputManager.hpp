//
// Created by wery_a on 24/11/16.
//

#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include "SaltyEngine/Input/KeyCodes.hpp"

namespace SaltyEngine {
    namespace Input {
#include "KeyCodesString.inl"
        template <class Input>
        class InputManager {
        public:
            static inline bool GetKey(KeyCode::Key key) {
                return Input::IsKey(key);
            }

            static inline bool GetKeyDown(KeyCode::Key key) {
                return Input::IsKeyDown(key);
            }

            static inline bool GetKeyUp(KeyCode::Key key) {
                return Input::isKeyUp(key);
            }

            static inline bool GetKey(std::string const &key) {
                return GetKey(m_keycodes.find(key)->second);
            }

            static inline bool GetKeyDown(std::string const &key) {
                return GetKeyDown(m_keycodes.find(key)->second);
            }

            static inline bool GetKeyUp(const std::string &key) {
                return GetKeyUp(m_keycodes.find(key)->second);
            }

            static inline std::vector<KeyCode::Key>    GetCurrentKeys() {
                return Input::GetCurrentKeys();
            }

            static inline bool     GetButtonPressed(Mouse::Button button) {
                return Input::GetButtonPressed(button);
            }

            static inline Vector2i GetPosition() {
                return Input::GetPosition();
            }

            static inline Vector2i GetPositionRelative() {
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
