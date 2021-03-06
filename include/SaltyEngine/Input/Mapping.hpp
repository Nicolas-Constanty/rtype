//
// Created by wery_a on 24/11/16.
//

#ifndef MAPPING_HPP
#define MAPPING_HPP

#include <functional>
#include <memory>
#include "Axis.hpp"
#include "Action.hpp"
#include "KeyCodes.hpp"

namespace SaltyEngine {
    namespace Input {
        typedef std::function<void(float)>  CallbackAxis;
        typedef std::function<void()>       CallbackAction;
        class LIB_EXPORT Mapping {
        private:
            static std::map<std::string, std::unique_ptr<Axis>>     m_axis;
            static std::map<std::string, std::unique_ptr<Action>>   m_actions;

        public:
            static void AddAxis(std::string const &name, Axis *axis);
            static void AddAction(std::string const &name, Action *action);

        private:
            static std::map<std::string, CallbackAxis>                          m_axis_bind;
            static std::map<std::pair<std::string, ActionType>, CallbackAction> m_actions_bind;

        public:
            static void BindAxis(std::string const &name, CallbackAxis callback);
            static void BindAction(std::string const &name, ActionType actionType, CallbackAction callback);

        private:
            // TODO use vector on name
            static std::map<KeyCode::Key, std::string>              m_keys_axis_binded;
            static std::map<KeyCode::Key, std::string>              m_keys_actions_binded;

        public:
            static void CallAxis(KeyCode::Key key);
            static void CallAction(KeyCode::Key key, ActionType actionType);
        };
    }
}

/// Example Binding
/// SaltyEngine::Input::Mapping::AddAction("Act", new SaltyEngine::Input::Action(SaltyEngine::Input::KeyCode::A));
/// SaltyEngine::Input::Mapping::BindAction("Act", SaltyEngine::Input::ActionType::Pressed, [] () { std::cout << "Act" << std::endl; });
///
/// Example


#endif //MAPPING_HPP
