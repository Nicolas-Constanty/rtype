//
// Created by wery_a on 24/11/16.
//

#ifndef ACTION_HPP
#define ACTION_HPP

#include <utility>
#include "SaltyEngine/Input/KeyCodes.hpp"
#include "SaltyEngine/Input/ActionType.hpp"

namespace SaltyEngine {
    namespace Input {
        class Action {
        public:
            Action(KeyCode::Key key, bool shift = false, bool ctrl = false, bool alt = false, bool cmd = false);
            Action(KeyCode::Key key, std::pair<unsigned int, int> joystick, bool shift = false, bool ctrl = false, bool alt = false, bool cmd = false);
            Action(std::pair<unsigned int, int> joystick);
            virtual ~Action();

        private:
            const KeyCode::Key  m_key;
            const bool          m_shift;
            const bool          m_ctrl;
            const bool          m_alt;
            const bool          m_cmd;
            const std::pair<unsigned int, int> m_joystick;

        public:
            KeyCode::Key    getKey() const;
            const std::pair<unsigned int, int>   &getJoystick() const;

            template <class Input>
            bool    Pressed() const {
                bool ret = false;
                if (m_key != KeyCode::Unknown) {
                    ret = Input::IsKeyDown(m_key);
                }
                if (m_joystick.second != -1 && Input::IsJoystickConnected(m_joystick.first) && Input::GetButtons(m_joystick.first) > (unsigned int)m_joystick.second) {
                    ret = Input::IsButtonPressed(m_joystick.first, m_joystick.second);
                }
                return ret;
            }

            template <class Input>
            bool    Released() const {
                return Input::IsKeyUp(m_key);
            }
        };
    }
}

#endif //ACTION_HPP
