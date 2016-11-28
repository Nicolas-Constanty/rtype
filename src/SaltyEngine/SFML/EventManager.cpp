//
// Created by wery_a on 24/11/16.
//

#include "SaltyEngine/Input/Mapping.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"

namespace SaltyEngine {
    namespace SFML {
        std::map<sf::Keyboard::Key, bool>           EventManager::m_keys_down;
        std::map<sf::Keyboard::Key, bool>           EventManager::m_keys_emited;
        sf::RenderWindow *                          EventManager::m_window = nullptr;

        EventManager::EventManager(sf::RenderWindow *const window) {
            m_window = window;
        }

        void EventManager::Update() {
            if (!m_window || !m_window->isOpen()) {
                return;
            }
            sf::Event event;
            while (m_window->pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::EventType::KeyPressed:
                        m_keys_down[event.key.code] = true;
                        SaltyEngine::Input::Mapping::CallAxis(GetKeyCode(event.key.code));
                        SaltyEngine::Input::Mapping::CallAction(GetKeyCode(event.key.code),
                                                                SaltyEngine::Input::ActionType::Pressed);
                        break;
                    case sf::Event::EventType::KeyReleased:
                        m_keys_down[event.key.code] = false;
                        m_keys_emited[event.key.code] = false;
                        SaltyEngine::Input::Mapping::CallAction(GetKeyCode(event.key.code),
                                                                SaltyEngine::Input::ActionType::Released);
                        break;
                    case sf::Event::EventType::JoystickButtonPressed:
                        break;
                    case sf::Event::EventType::JoystickButtonReleased:
                        break;
                    case sf::Event::EventType::JoystickMoved:
                        break;
                    default:
                        break;
                }

            }
        }

        bool EventManager::IsKey(SaltyEngine::Input::KeyCode::Key key) {
            sf::Keyboard::Key sfKey = GetKeyCode(key);
            if (!m_keys_emited[sfKey] && m_keys_down[sfKey]) {
                m_keys_emited[sfKey] = true;
                return true;
            }
            return false;
        }

        bool EventManager::IsKeyDown(SaltyEngine::Input::KeyCode::Key key) {
            return (m_keys_down[GetKeyCode(key)] == true);
        }

        bool EventManager::IsKeyUp(SaltyEngine::Input::KeyCode::Key key) {
            return (m_keys_down[GetKeyCode(key)] == false);
        }

        std::vector<SaltyEngine::Input::KeyCode::Key> EventManager::GetCurrentKeys() {
            std::vector<SaltyEngine::Input::KeyCode::Key> keys;
            for (std::map<sf::Keyboard::Key, bool>::const_iterator it = m_keys_down.begin();
                 it != m_keys_down.end(); ++it) {
                if (it->second) {
                    keys.push_back(GetKeyCode(it->first));
                }
            }
            return keys;
        }

        bool EventManager::GetButtonPressed(SaltyEngine::Input::Mouse::Button button) {
            return sf::Mouse::isButtonPressed(sf::Mouse::Button(button));
        }

        SaltyEngine::Vector EventManager::GetPosition() {
            sf::Vector2i position = sf::Mouse::getPosition();
            return SaltyEngine::Vector(position.x, position.y);
        }

        SaltyEngine::Vector EventManager::GetPositionRelative() {
            sf::Vector2i position = sf::Mouse::getPosition(*m_window);
            return SaltyEngine::Vector(position.x, position.y);
        }
    }
}