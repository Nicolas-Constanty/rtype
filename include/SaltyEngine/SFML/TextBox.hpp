//
// Created by nicolas-constanty on 29/12/16.
//

#ifndef RTYPE_TEXTBOX_HPP
#define RTYPE_TEXTBOX_HPP

#include "SaltyEngine/SFML/Label.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"

namespace SaltyEngine
{
    namespace GUI
    {
        namespace SFML {

            class LIB_EXPORT TextBox : public GUI::UIBehaviour
            {
            public:
                TextBox(GameObject *gameObj,
                        const Label *label,
                        const sf::Vector2f& size,
                        unsigned int font_size,
                        const sf::Font *font,
                        const sf::Color &color = sf::Color::Black,
                        const sf::Color &fill_color = sf::Color::White,
                        const sf::Color &color_outline = sf::Color::Black,
                        unsigned int outline_thickness = 2);

            public:
                void Start() override;
                void Update() override;

                void FixedUpdate() override;

            private:
                const Label *m_title;
                sf::Font m_font;
                sf::RectangleShape m_entry;
                sf::Text m_cursor;
                sf::Text m_text;
                std::string m_aff;
                sf::Clock m_clock;
                sf::Time m_elapsed;
                std::string m_field;
                size_t m_max_size;
                bool m_clignot;
                SaltyEngine::SFML::Renderer *m_renderer;
            };
        }
    }
}

#endif //RTYPE_TEXTBOX_HPP
