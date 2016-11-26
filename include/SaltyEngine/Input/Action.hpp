//
// Created by wery_a on 24/11/16.
//

#ifndef ACTION_HPP
#define ACTION_HPP

#include "KeyCodes.hpp"

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
            bool    Pressed() const;
            bool    Released() const;
        };
    }
}

#endif //ACTION_HPP
