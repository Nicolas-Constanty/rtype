//
// Created by wery_a on 24/11/16.
//

#include <iostream>
#include "SaltyEngine/Input/Mapping.hpp"

namespace SaltyEngine {
    namespace Input {
        std::map<KeyCode::Key, std::string>             Mapping::m_keys_axis_binded;
        std::map<KeyCode::Key, std::string>             Mapping::m_keys_actions_binded;

        std::map<std::string, std::unique_ptr<Axis>>    Mapping::m_axis;
        std::map<std::string, std::unique_ptr<Action>>  Mapping::m_actions;

        std::map<std::string, CallbackAxis>                          Mapping::m_axis_bind;
        std::map<std::pair<std::string, ActionType>, CallbackAction> Mapping::m_actions_bind;

        void Mapping::AddAxis(std::string const &name, Axis *axis) {
            const std::map<KeyCode::Key, float> keys = axis->getKeys();
            for (std::map<KeyCode::Key, float>::const_iterator it = keys.begin(); it != keys.end(); ++it) {
                m_keys_axis_binded[it->first] = name;
            }
            m_axis[name] = std::unique_ptr<Axis>(axis);
        }

        void Mapping::AddAction(std::string const &name, Action *action) {
            m_keys_actions_binded[action->getKey()] = name;
            m_actions[name] = std::unique_ptr<Action>(action);
        }

        void Mapping::BindAxis(std::string const &name, CallbackAxis callback) {
            m_axis_bind[name] = callback;
        }

        void Mapping::BindAction(std::string const &name, ActionType actionType, CallbackAction callback) {
            m_actions_bind[std::make_pair(name, actionType)] = callback;
        }

        void Mapping::CallAxis(KeyCode::Key key) {
            std::map<KeyCode::Key, std::string>::const_iterator it_binded = m_keys_axis_binded.find(key);
            if (it_binded != m_keys_axis_binded.end()) {
                std::string name = it_binded->second;
                std::map<std::string, CallbackAxis>::const_iterator it_bind = m_axis_bind.find(name);
                if (it_bind != m_axis_bind.end()) {
                    std::map<std::string, std::unique_ptr<Axis>>::const_iterator it_axis = m_axis.find(name);
                    if (it_axis != m_axis.end()) {
                        // TODO Deprecated
//                        return (it_bind->second(it_axis->second->getValue(key)));
                        return;
                    }
                }
            }
        }

        void Mapping::CallAction(KeyCode::Key key, ActionType actionType) {
            std::map<KeyCode::Key, std::string>::const_iterator it_binded = m_keys_actions_binded.find(key);
            if (it_binded != m_keys_actions_binded.end()) {
                std::string name = it_binded->second;
                std::map<std::pair<std::string, ActionType>, CallbackAction>::const_iterator it_bind = m_actions_bind.find(std::make_pair(name, actionType));
                if (it_bind != m_actions_bind.end()) {
                    return it_bind->second();
                }
            }
        }
    }
}
