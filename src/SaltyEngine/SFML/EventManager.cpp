//
// Created by wery_a on 24/11/16.
//

#include <SaltyEngine/SaltyEngine.hpp>
#include "SaltyEngine/Input/Mapping.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"

namespace SaltyEngine {
    namespace SFML {
        std::map<sf::Keyboard::Key, ::SaltyEngine::Input::ActionType> EventManager::m_keys;
        std::map<sf::Keyboard::Key, bool>           EventManager::m_keys_down;
        std::map<sf::Keyboard::Key, bool>           EventManager::m_keys_up;

        sf::RenderWindow *                          EventManager::m_window = nullptr;

        EventManager::EventManager(sf::RenderWindow *const window) {
            m_window = window;
        }

        void EventManager::Update() {
            if (!m_window || !m_window->isOpen()) {
                return;
            }
            sf::Event event;
            while (!m_events.empty())
                m_events.pop();
            while (m_window->pollEvent(event)) {

                switch (event.type) {
                    case sf::Event::EventType::Closed:
                        m_window->close();
                        Singleton<Engine>::Instance().Stop();
                        break;
                    case sf::Event::EventType::KeyPressed:
                        m_keys[event.key.code] = ::SaltyEngine::Input::ActionType::Pressed;
                        m_keys_up[event.key.code] = false;
                        break;
                    case sf::Event::EventType::KeyReleased:
                        m_keys[event.key.code] = ::SaltyEngine::Input::ActionType::Released;
                        m_keys_down[event.key.code] = false;
                        break;
                    case sf::Event::EventType::JoystickButtonPressed:
                        break;
                    case sf::Event::EventType::JoystickButtonReleased:
                        break;
                    case sf::Event::EventType::JoystickMoved:
                        break;
                    case sf::Event::EventType::TextEntered:
                    case sf::Event::EventType::MouseButtonPressed:
                    case sf::Event::EventType::MouseButtonReleased:
                        m_events.push(event);
                    case sf::Event::EventType::GainedFocus:
                        m_isFocused = true;
                        break;
                    case sf::Event::EventType::LostFocus:
                        m_isFocused = false;
                        break;
                    default:
                        break;
                }
            }
        }

        bool EventManager::GetKey(::SaltyEngine::Input::KeyCode::Key key) {
            return (m_keys[GetKeyCode(key)] == ::SaltyEngine::Input::ActionType::Pressed);
        }

        bool EventManager::GetKeyDown(::SaltyEngine::Input::KeyCode::Key key) {
            sf::Keyboard::Key sfKey = GetKeyCode(key);
            if (m_keys[sfKey] == ::SaltyEngine::Input::ActionType::Pressed && !m_keys_down[sfKey]) {
                m_keys_down[sfKey] = true;
                return true;
            }
            return false;
        }

        bool EventManager::GetKeyUp(::SaltyEngine::Input::KeyCode::Key key) {
            sf::Keyboard::Key sfKey = GetKeyCode(key);
            if (m_keys[sfKey] == ::SaltyEngine::Input::ActionType::Released && !m_keys_up[sfKey]) {
                m_keys_up[sfKey] = true;
                return true;
            }
            return false;
        }

        std::vector<::SaltyEngine::Input::KeyCode::Key> EventManager::GetCurrentKeys() {
            std::vector<::SaltyEngine::Input::KeyCode::Key> keys;
            for (std::map<sf::Keyboard::Key, bool>::const_iterator it = m_keys_down.begin();
                 it != m_keys_down.end(); ++it) {
                if (it->second) {
                    keys.push_back(GetKeyCode(it->first));
                }
            }
            return keys;
        }

        bool EventManager::GetButtonPressed(::SaltyEngine::Input::Mouse::Button button) {
            return sf::Mouse::isButtonPressed(sf::Mouse::Button(button));
        }

        ::SaltyEngine::Vector2i EventManager::GetPosition(void) {
            sf::Vector2i position = sf::Mouse::getPosition();
            return ::SaltyEngine::Vector2i(position.x, position.y);
        }

        ::SaltyEngine::Vector2i EventManager::GetPositionRelative(void) {
            sf::Vector2i position = sf::Mouse::getPosition(*m_window);
            return ::SaltyEngine::Vector2i(position.x, position.y);
        }

        bool EventManager::IsJoystickConnected(unsigned int id) {
            return sf::Joystick::isConnected(id);
        }

        unsigned int EventManager::GetButtons(unsigned int id) {
            return sf::Joystick::getButtonCount(id);
        }

        bool EventManager::HasAxis(unsigned int id, ::SaltyEngine::Input::MotionController::Axis axis) {
            return sf::Joystick::hasAxis(id, sf::Joystick::Axis(axis));
        }

        bool EventManager::IsButtonPressed(unsigned int id, unsigned int button) {
            return sf::Joystick::isButtonPressed(id, button);
        }

        float EventManager::GetAxisPosition(unsigned int id, ::SaltyEngine::Input::MotionController::Axis axis) {
            return sf::Joystick::getAxisPosition(id, sf::Joystick::Axis(axis));
        }

        const std::queue<sf::Event> &EventManager::GetEvent() {
            return m_events;
        }

        bool EventManager::IsWindowFocused(void) const
        {
            return m_isFocused;
        }
    }
}