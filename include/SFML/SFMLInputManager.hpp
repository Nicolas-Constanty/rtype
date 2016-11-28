//
// Created by wery_a on 24/11/16.
//

#ifndef SFMLINPUTMANAGER_HPP
#define SFMLINPUTMANAGER_HPP


#include <map>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SaltyEngine/Vector2.hpp>
#include "SaltyEngine/Input/InputManager.hpp"

class SFMLInputManager {
private:
    static  std::map<sf::Event::EventType, sf::Event>   m_events;
    static  std::map<sf::Keyboard::Key , bool>          m_keys_down;
    static  std::map<sf::Keyboard::Key , bool>          m_keys_emited;
    static  sf::RenderWindow                            *m_window;

public:
    static void addEvent(sf::Event event);
    static void clearEvents();

    static bool isKey(SaltyEngine::Input::KeyCode::Key key);
    static bool isKeyDown(SaltyEngine::Input::KeyCode::Key key);
    static bool isKeyUp(SaltyEngine::Input::KeyCode::Key key);
    static std::vector<SaltyEngine::Input::KeyCode::Key>  GetCurrentKeys();

    static bool     GetButtonPressed(SaltyEngine::Input::Mouse::Button button);
    static SaltyEngine::Vector2i GetPosition();
    static SaltyEngine::Vector2i GetPositionRelative();

    static inline SaltyEngine::Input::KeyCode::Key GetKeyCode(sf::Keyboard::Key key) {
        return (SaltyEngine::Input::KeyCode::Key(key + 1));
    }
    static inline sf::Keyboard::Key     GetKeyCode(SaltyEngine::Input::KeyCode::Key key) {
        return (sf::Keyboard::Key(key - 1));
    }
};

/// Example Usage
/// sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
/// SFMLInputManager::setWindow(&window);
/// sf::Event event;
/// while (window.isOpen()) {
///     while (window.pollEvent(event)) {
///         SFMLInputManager::addEvent(event);
///         if (event.type == sf::Event::Closed)
///             window.close();
///     }
///     SFMLInputManager::clearEvents();
///     window.display();
/// }


#endif //SFMLINPUTMANAGER_HPP
