//
// Created by nicolas-constanty on 01/01/17.
//
#include "SaltyEngine/SFML.hpp"

namespace SaltyEngine
{
    namespace GUI
    {
        namespace SFML
        {

            LabelList::LabelList(GameObject *const obj) : UIBehaviour("LabelList", obj), m_index(0) {

            }

            LabelList::~LabelList() {

            }

            void LabelList::AddLabel(Label *const label) {
                m_labels.push_back(label);
                int offset = 10;
                const Vector2 &vec = gameObject->transform.GetPosition();
//                std::cout << gameObject->transform.GetPosition().y  + m_labels.size() * label->getCharacterSize() + offset << std::endl;
//                label->setPosition(gameObject->transform.GetPosition().x, gameObject->transform.GetPosition().y  + m_labels.size() * label->getCharacterSize() + offset);
            }

            void LabelList::RemoveLabel(size_t index) {
                size_t i = 0;
                for (std::vector<Label *>::iterator it = m_labels.begin(); it != m_labels.end(); ++it) {
                    if (i == index)
                        m_labels.erase(it);
                    ++i;
                }
            }

            void LabelList::Update() {
                if (InputKey::GetKeyDown(Input::KeyCode::Down))
                {
                    ++m_index;
                    if (m_index >= m_labels.size())
                        m_index = 0;
                }
                else if (InputKey::GetKeyDown(Input::KeyCode::Up))
                {
                    --m_index;
                    if (m_index < 0)
                        m_index = m_labels.size() -1;
                }
                if (m_labels.size() && m_labels[m_index]->getColor() != sf::Color::Cyan)
                    m_labels[m_index]->setColor(sf::Color::Cyan);
            }
        }
    }
}