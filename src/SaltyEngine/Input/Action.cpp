//
// Created by wery_a on 24/11/16.
//

#include "SaltyEngine/Input/Action.hpp"

namespace SaltyEngine {
    namespace Input {
        Action::Action(KeyCode::Key key, bool shift, bool ctrl, bool alt, bool cmd)
                : m_key(key), m_shift(shift), m_ctrl(ctrl), m_alt(alt), m_cmd(cmd) {

        }

        Action::~Action() {

        }

        KeyCode::Key Action::getKey() const {
            return m_key;
        }
    }
}
