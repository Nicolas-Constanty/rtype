//
// Created by wery_a on 24/11/16.
//

#include "SaltyEngine/Input/Mapping.hpp"
#include "SFML/SFMLInputManager.hpp"

std::map<sf::Event::EventType, sf::Event>   SFMLInputManager::m_events;
std::map<sf::Keyboard::Key, bool>           SFMLInputManager::m_keys_down;
std::map<sf::Keyboard::Key, bool>           SFMLInputManager::m_keys_emited;
sf::RenderWindow                            *SFMLInputManager::m_window;

void SFMLInputManager::addEvent(sf::Event event) {
    m_events[event.type] = event;
    if (event.type == sf::Event::EventType::KeyPressed) {
        m_keys_down[event.key.code] = true;
        SaltyEngine::Input::Mapping::CallAxis(GetKeyCode(event.key.code));
        SaltyEngine::Input::Mapping::CallAction(GetKeyCode(event.key.code), SaltyEngine::Input::ActionType::Pressed);
    } else if (event.type == sf::Event::EventType::KeyReleased) {
        m_keys_down[event.key.code] = false;
        m_keys_emited[event.key.code] = false;
        SaltyEngine::Input::Mapping::CallAction(GetKeyCode(event.key.code), SaltyEngine::Input::ActionType::Released);
    }
}

void SFMLInputManager::clearEvents() {
    m_events.clear();
}

bool SFMLInputManager::isKey(SaltyEngine::Input::KeyCode::Key key) {
    sf::Keyboard::Key sfKey = GetKeyCode(key);
    if (!m_keys_emited[sfKey] && m_keys_down[sfKey]) {
        m_keys_emited[sfKey] = true;
        return true;
    }
    return false;
}

bool SFMLInputManager::isKeyDown(SaltyEngine::Input::KeyCode::Key key) {
    return (m_keys_down[GetKeyCode(key)] == true);
}

bool SFMLInputManager::isKeyUp(SaltyEngine::Input::KeyCode::Key key) {
    return (m_keys_down[GetKeyCode(key)] == false);
}

std::vector<SaltyEngine::Input::KeyCode::Key> SFMLInputManager::GetCurrentKeys() {
    std::vector<SaltyEngine::Input::KeyCode::Key> keys;
    for (std::map<sf::Keyboard::Key , bool>::const_iterator it = m_keys_down.begin(); it != m_keys_down.end(); ++it) {
        if (it->second) {
            keys.push_back(GetKeyCode(it->first));
        }
    }
    return keys;
}

bool SFMLInputManager::GetButtonPressed(SaltyEngine::Input::Mouse::Button button) {
    sf::Mouse::isButtonPressed(sf::Mouse::Button(button));
}

SaltyEngine::Vector2i SFMLInputManager::GetPosition() {
    sf::Vector2i position = sf::Mouse::getPosition();
    return SaltyEngine::Vector2i(position.x, position.y);
}

SaltyEngine::Vector2i SFMLInputManager::GetPositionRelative() {
    sf::Vector2i position = sf::Mouse::getPosition(*m_window);
    return SaltyEngine::Vector2i(position.x, position.y);
}