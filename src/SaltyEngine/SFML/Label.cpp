//
// Created by nicolas-constanty on 20/12/16.
//

#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/Label.hpp"

namespace SaltyEngine
{
    namespace GUI
    {
        namespace SFML
        {
            Label::Label(GameObject *gameObj, const std::string &text, unsigned int size, const sf::Font *fnt, const sf::Color &col)
                    : UIBehaviour("LabelGUI", gameObj), sf::Text(), m_data(text) {
                setFont(*fnt);
                setCharacterSize(size);
                setColor(col);
                setString(m_data);
                setOrigin(getLocalBounds().width / 2, (getGlobalBounds().height + size / 2) / 2 );
            }

            void Label::SetText(const std::string &txt) {
                m_data = txt;
                setString(m_data);
            }

            const std::string &Label::GetText() const {
                return m_data;
            }

            const Label &Label::operator+=(const std::string &t) {
                m_data += t;
                setString(m_data);
                return (*this);
            }

            void Label::Clear() {
                m_data.clear();
                setString(m_data);
            }

            void Label::Update() {
                const Transform &t = gameObject->transform;
                setPosition(t.GetPosition().x * t.GetLocalScale().x, t.GetPosition().y * t.GetLocalScale().y);
            }
        }
    }
}