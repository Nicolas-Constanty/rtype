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
            }

            void LabelList::RemoveLabel(size_t index) {
                size_t i = 0;
                for (std::vector<Label *>::iterator it = m_labels.begin(); it != m_labels.end(); ++it) {
                    if (i == index) {
                        m_labels.erase(it);
                        return ;
                    }
                    ++i;
                }
            }

            void LabelList::OnGui() {
                int offset = 10;
                for (unsigned int j = 0; j < m_labels.size(); ++j) {
                    m_labels[j]->setPosition(gameObject->transform.GetPosition().x, gameObject->transform.GetPosition().y  + j * m_labels[j]->getCharacterSize() + offset);
                }
                if (InputKey::GetKeyDown(Input::KeyCode::Down))
                {
                    m_labels[m_index]->setColor(sf::Color::White);
                    ++m_index;
                    if (m_index >= static_cast<long>(m_labels.size()))
                        m_index = 0;
                }
                else if (InputKey::GetKeyDown(Input::KeyCode::Up))
                {
                    m_labels[m_index]->setColor(sf::Color::White);
                    --m_index;
                    if (m_index < 0)
                    {
                        if (m_labels.size())
                            m_index = m_labels.size() -1;
                        else
                            m_index = 0;
                    }
                }
                if (m_labels.size() && m_labels[m_index]->getColor() != sf::Color::Cyan)
                    m_labels[m_index]->setColor(sf::Color::Cyan);
            }

            const std::string &LabelList::GetSelected() {
                return m_labels[m_index]->GetText();
            }

            void LabelList::RemoveAllLabel() {
                std::vector<Label *>::iterator it = m_labels.begin();
                while (it != m_labels.end()) {
                    it = m_labels.erase(it);
                }
            }

            Component *LabelList::CloneComponent(GameObject *const obj) {
                return new LabelList(obj);
            }

            size_t LabelList::GetIndex() const {
                return (size_t) m_index;
            }
        }
    }
}