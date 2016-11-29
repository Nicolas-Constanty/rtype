//
// Created by wery_a on 24/11/16.
//

#ifndef ACTION_HPP
#define ACTION_HPP

#include "SaltyEngine/Input/KeyCodes.hpp"

namespace SaltyEngine {
    namespace Input {
        enum ActionType {
            Pressed,
            Released
        };
        class Action {
        public:
            Action(KeyCode::Key key, bool shift = false, bool ctrl = false, bool alt = false, bool cmd = false);
            virtual ~Action();

        private:
            const KeyCode::Key  m_key;
            const bool          m_shift;
            const bool          m_ctrl;
            const bool          m_alt;
            const bool          m_cmd;

        public:
            KeyCode::Key    getKey() const;

            template <class Input>
            bool    Pressed() const {
                return Input::IsKeyDown(m_key);
            }

            template <class Input>
            bool    Released() const {
                return Input::IsKeyUp(m_key);
            }
        };
    }
}

#endif //ACTION_HPP
