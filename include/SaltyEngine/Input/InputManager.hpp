//
// Created by wery_a on 24/11/16.
//

#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include "SaltyEngine/Input/Axis.hpp"
#include "SaltyEngine/Input/Action.hpp"
#include "SaltyEngine/Debug.hpp"

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

        private:
            static std::map<std::string, std::unique_ptr<Axis> >    m_axis;
            static std::map<std::string, std::unique_ptr<Action> >  m_actions;

        public:
            static void  AddAxis(std::string const &name, Axis *axis) {
                if (m_axis.find(name) != m_axis.end()) {
                    Debug::PrintWarning("Axis " + name + " is already set, use SetAxis instead.");
                    return;
                }
                m_axis[name] = std::unique_ptr<Axis>(axis);
            }

            static void  AddAction(std::string const &name, Action *action) {
                if (m_actions.find(name) != m_actions.end()) {
                    Debug::PrintWarning("Action " + name + " is already set, use SetAction instead.");
                    return;
                }
                m_actions[name] = std::unique_ptr<Action>(action);
            }

            static void  SetAxis(std::string const &name, Axis *axis) {
                m_axis[name] = std::unique_ptr<Axis>(axis);
            }

            static void  SetAction(std::string const &name, Action *action) {
                m_actions[name] = std::unique_ptr<Action>(action);
            }

            static float GetAxis(std::string const &name) {
                std::map<std::string, std::unique_ptr<Axis>>::const_iterator it = m_axis.find(name);
                if (it == m_axis.end()) {
                    Debug::PrintWarning("Axis " + name + " is not set");
                    return 0;
                }
                return it->second.get()->getValue<Input>();
            }

            static bool  GetAction(std::string const &name, ActionType actionType) {
                std::map<std::string, std::unique_ptr<Action>>::const_iterator it = m_actions.find(name);
                if (it == m_actions.end()) {
                    Debug::PrintWarning("Action " + name + " is not set");
                    return false;
                }
                switch (actionType) {
                    case ActionType::Pressed :
                        return it->second.get()->Pressed<Input>();
                    case ActionType::Released :
                        return it->second.get()->Released<Input>();
                    case ActionType::Once :
                        return it->second.get()->Once<Input>();
                    default:
                        return false;
                }
                return false;
            }
        };
        template <class T>
        std::map<std::string, std::unique_ptr<Axis> >    InputManager<T>::m_axis;

        template <class T>
        std::map<std::string, std::unique_ptr<Action> >  InputManager<T>::m_actions;
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
