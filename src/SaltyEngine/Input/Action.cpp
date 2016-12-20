//
// Created by wery_a on 24/11/16.
//

#include "SaltyEngine/Input/Action.hpp"

namespace SaltyEngine {
    namespace Input {
        Action::Action(KeyCode::Key key, bool shift, bool ctrl, bool alt, bool cmd)
                : m_key(key), m_shift(shift), m_ctrl(ctrl), m_alt(alt), m_cmd(cmd), m_joystick(std::make_pair<unsigned int, int>(0, -1)) {

        }

        Action::Action(KeyCode::Key key, std::pair<unsigned int, int> joystick, bool shift, bool ctrl, bool alt, bool cmd)
                : m_key(key), m_shift(shift), m_ctrl(ctrl), m_alt(alt), m_cmd(cmd), m_joystick(joystick) {

        }

        Action::Action(std::pair<unsigned int, int> joystick)
                : m_key(KeyCode::Unknown), m_shift(false), m_ctrl(false), m_alt(false), m_cmd(false), m_joystick(joystick) {

        }

        Action::~Action() {

        }

        KeyCode::Key Action::getKey() const {
            return m_key;
        }

        const std::pair<unsigned int, int>& Action::getJoystick() const {
            return m_joystick;
        }
    }
}
