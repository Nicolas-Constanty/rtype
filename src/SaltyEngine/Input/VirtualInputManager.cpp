//
// Created by wery_a on 09/12/16.
//

#include "SaltyEngine/Input/VirtualInutManager.hpp"

namespace SaltyEngine {
    namespace Input {
        std::map<std::string, float>        VirtualInputManager::m_axis;
        std::map<std::string, ActionType>   VirtualInputManager::m_actions;

        float VirtualInputManager::GetAxis(const std::string &name) {
            float value = m_axis[name];
            m_axis[name] = 0;
            return value;
        }

        bool VirtualInputManager::GetAction(const std::string &name, ActionType actionType) {
            bool act = m_actions[name] == actionType;
            m_actions[name] = ActionType::None;
            return act;
        }

        void VirtualInputManager::SetAxis(const std::string &name, float value) {
            m_axis[name] = value;
        }

        void VirtualInputManager::SetAction(const std::string &name, ActionType actionType) {
            m_actions[name] = actionType;
        }
    }
}