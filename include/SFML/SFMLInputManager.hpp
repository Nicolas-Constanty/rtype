//
// Created by wery_a on 24/11/16.
//

#ifndef SFMLINPUTMANAGER_HPP
#define SFMLINPUTMANAGER_HPP


#include <map>
#include <vector>
#include <SFML/Window/Event.hpp>
#include "SaltyEngine/Input/InputManager.hpp"

class SFMLInputManager {
private:
    static  std::map<sf::Event::EventType, sf::Event>   m_events;
    static  std::map<sf::Keyboard::Key , bool>          m_keys_down;
    static  std::map<sf::Keyboard::Key , bool>          m_keys_emited;

public:
    static void addEvent(sf::Event event);
    static void clearEvents();

    static bool isKey(SaltyEngine::Input::KeyCode::Key key);
    static bool isKeyDown(SaltyEngine::Input::KeyCode::Key key);
    static bool isKeyUp(SaltyEngine::Input::KeyCode::Key key);
    static std::vector<SaltyEngine::Input::KeyCode::Key>  GetCurrentKeys();

    static inline SaltyEngine::Input::KeyCode::Key GetKeyCode(sf::Keyboard::Key key) {
        return (SaltyEngine::Input::KeyCode::Key(key + 1));
    }
    static inline sf::Keyboard::Key     GetKeyCode(SaltyEngine::Input::KeyCode::Key key) {
        return (sf::Keyboard::Key(key - 1));
    }
};


#endif //SFMLINPUTMANAGER_HPP
