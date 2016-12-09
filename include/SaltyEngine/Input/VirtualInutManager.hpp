//
// Created by wery_a on 09/12/16.
//

#ifndef RTYPE_VIRTUALINUTMANAGER_HPP
#define RTYPE_VIRTUALINUTMANAGER_HPP

#include <string>
#include <map>
#include "SaltyEngine/Input/ActionType.hpp"

namespace SaltyEngine {
    namespace Input {
        class VirtualInputManager {
        private:
            static std::map<std::string, float>        m_axis;
            static std::map<std::string, ActionType>   m_actions;
        public:
            ///
            /// \brief Get Axis by name
            /// \brief Reset the value to 0
            /// \warning use one time
            /// \param name
            /// \return float
            static float    GetAxis(std::string const &name);

            ///
            /// \brief Get Action by name
            /// \brief Reset the value to None
            /// \warning use one time
            /// \param name
            /// \return bool
            static bool     GetAction(std::string const &name, ActionType actionType);

            ///
            /// \brief set a value to an Axis by name
            /// \param name
            /// \param value
            static void     SetAxis(std::string const &name, float value);

            ///
            /// \brief set a ActionType to an Action by name
            /// \param name
            /// \param value
            static void     SetAction(std::string const &name, ActionType actionType);
        };
    }
}

#endif //RTYPE_VIRTUALINUTMANAGER_HPP
