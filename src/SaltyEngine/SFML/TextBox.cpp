//
// Created by nicolas-constanty on 29/12/16.
//

#include "SaltyEngine/SFML.hpp"


SaltyEngine::GUI::SFML::TextBox::TextBox(SaltyEngine::GameObject *gameObj, const Label *label,
                                         const sf::Vector2f &size, unsigned int font_size, const sf::Font *font,
                                         const sf::Color &font_color, const sf::Color &fill_color,
                                         const sf::Color &color_outline, unsigned int outline_thickness,
                                         size_t max_char) :
        UIBehaviour("TextBoxGUI", gameObj),
        m_font(*font),
        m_entry(size)
{
    m_entry.setOutlineThickness(outline_thickness);
    m_entry.setOutlineColor(color_outline);
    m_entry.setFillColor(fill_color);
    m_cursor.setFont(m_font);
    m_cursor.setString("|");
    m_cursor.setCharacterSize(font_size);
    m_cursor.setFillColor(font_color);
    m_cursor.setPosition(2, 0);
    m_text.setFont(m_font);
    m_text.setFillColor(font_color);
    m_text.setPosition(2, 0);
    m_text.setCharacterSize(font_size);
    m_max_size = 0;
    m_title = label;
    m_max_char = max_char;
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();
    m_renderer = dynamic_cast<::SaltyEngine::SFML::Renderer *>(engine.GetRenderer());
    m_entry.setOrigin(size.x / 2, size.y /2);
    eve = dynamic_cast<SaltyEngine::SFML::EventManager *>(SaltyEngine::Engine::Instance().GetEventManager());
}

void SaltyEngine::GUI::SFML::TextBox::FixedUpdate() {
}

void SaltyEngine::GUI::SFML::TextBox::Update() {

    const Vector2 &vec = gameObject->transform.GetPosition();
    const Vector2 &sc = gameObject->transform.GetLocalScale();

    if (!eve->GetEvent().empty() && eve->IsWindowFocused() && this->gameObject->GetActiveSelf())
    {
        const sf::Event &ev = eve->GetEvent().front();
        if (ev.text.unicode < 128)
        {
            if (ev.key.code == 8 && m_field.size())
            {
                m_field = m_field.substr(0, m_field.size() - 1);
                m_aff = m_aff.substr(0, m_aff.size() - 1);
                m_text.setString(m_field);
                while (m_text.getLocalBounds().width > m_entry.getGlobalBounds().width - 10)
                {
                    if (m_field.size() > m_max_size)
                        m_aff = m_field.substr(m_field.size() - m_max_size);
                    m_text.setString(m_aff);
                    m_max_size = m_aff.size();
                }
            }
            else if (ev.key.code != 8)
            {
                if (m_max_char == 0 || (m_field.size() < m_max_char))
                {
                    m_field += static_cast<char>(ev.key.code);
                    m_aff += static_cast<char>(ev.key.code);
                    m_text.setString(m_aff);
                    while (m_text.getLocalBounds().width > m_entry.getGlobalBounds().width - 10)
                    {
                        m_aff = m_aff.substr(1, m_aff.size());
                        m_max_size = m_aff.size();
                        m_text.setString(m_aff);
                    }
                }
            }
            m_text.setString(m_aff);
            m_cursor.setPosition(vec.x * sc.x - m_entry.getSize().x + 8 + m_text.getGlobalBounds().width, vec.y * sc.y + m_entry.getSize().y / 2);
            m_text.setPosition(vec.x * sc.x - m_entry.getSize().x + 8, vec.y * sc.y + m_entry.getSize().y / 2);
        }
    }
    if (m_renderer) {
        if (m_clock.getElapsedTime().asSeconds() > 0.5f) {
            m_clock.restart();
            m_clignot = !m_clignot;
        }
        m_entry.setPosition(vec.x * sc.x, vec.y * sc.y + m_entry.getSize().y + m_title->getCharacterSize());
        m_entry.setScale(sc.x, sc.y);
        m_renderer->AddDrawable(&m_entry);
        if (m_clignot) {
            m_renderer->AddDrawable(&m_cursor);
        }
        m_renderer->AddDrawable(&m_text);
    }
}

void SaltyEngine::GUI::SFML::TextBox::Start() {
    m_text.setCharacterSize(m_text.getCharacterSize() * gameObject->transform.GetLocalScale().y);
    const Vector2 &vec = gameObject->transform.GetPosition();
    const Vector2 &sc = gameObject->transform.GetLocalScale();
    m_cursor.setPosition(vec.x * sc.x - m_entry.getSize().x + 8 + m_text.getGlobalBounds().width, vec.y * sc.y + m_entry.getSize().y / 2);
    m_cursor.setCharacterSize(m_text.getCharacterSize());
}

std::string const &SaltyEngine::GUI::SFML::TextBox::GetText(void) const
{
    return m_field;
}
