//
// Created by wery_a on 24/11/16.
//

#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP


#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <queue>
#include "SaltyEngine/Vector2.hpp"
#include "SaltyEngine/Input/IEventManager.hpp"
#include "SaltyEngine/Input/InputManager.hpp"

namespace SaltyEngine {
    namespace SFML {
        class EventManager : public ::SaltyEngine::Input::IEventManager {
        public:
            EventManager(sf::RenderWindow *const window);

        private:
            static std::map<sf::Keyboard::Key, bool> m_keys_down;
            static std::map<sf::Keyboard::Key, bool> m_keys_up;
            static std::map<sf::Keyboard::Key, bool> m_keys_emited;

        protected:
            static sf::RenderWindow *m_window;

        public:
            void Update();

            static bool IsKey(::SaltyEngine::Input::KeyCode::Key key);

            static bool IsKeyReleased(::SaltyEngine::Input::KeyCode::Key key);

            static bool IsKeyDown(::SaltyEngine::Input::KeyCode::Key key);

            static bool IsKeyUp(::SaltyEngine::Input::KeyCode::Key key);

            static std::vector<::SaltyEngine::Input::KeyCode::Key> GetCurrentKeys(void);

            static bool GetButtonPressed(::SaltyEngine::Input::Mouse::Button button);

            static Vector GetPosition(void);

            static Vector GetPositionRelative(void);

            static bool         IsJoystickConnected(unsigned int id);
            static unsigned int GetButtons(unsigned int id);
            static bool         HasAxis(unsigned int id, ::SaltyEngine::Input::MotionController::Axis axis);
            static bool         IsButtonPressed(unsigned int id, unsigned int button);
            static float        GetAxisPosition(unsigned int id, ::SaltyEngine::Input::MotionController::Axis axis);

            static inline ::SaltyEngine::Input::KeyCode::Key GetKeyCode(sf::Keyboard::Key key) {
                return (::SaltyEngine::Input::KeyCode::Key(key + 1));
            }

            static inline sf::Keyboard::Key GetKeyCode(::SaltyEngine::Input::KeyCode::Key key) {
                return (sf::Keyboard::Key(key - 1));
            }
        };
    }
}

#endif //EVENTMANAGER_HPP
