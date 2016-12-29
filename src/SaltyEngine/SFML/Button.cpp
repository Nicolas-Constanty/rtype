//
// Created by nicolas-constanty on 18/12/16.
//

#include <SaltyEngine/SFML.hpp>
#include "SaltyEngine/SFML/Button.hpp"

namespace SaltyEngine
{
    namespace GUI
    {
        namespace SFML
        {
            Button::Button(GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite) :
                    GUI::Button("SMFLButton", gameObj), m_normal(sprite), m_over(sprite), m_status(false)
            {
                m_sprr = gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(m_normal, Layout::gui);
            }

            Button::Button(GameObject *gameObj, ::SaltyEngine::SFML::Sprite *const norm,
                           ::SaltyEngine::SFML::Sprite *const over) :
                    GUI::Button("SMFLButton", gameObj), m_normal(norm), m_over(over), m_status(false)
            {
                m_sprr = gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(m_normal, Layout::gui);
            }

            Button::Button(const std::string &name, GameObject *gameObj, ::SaltyEngine::SFML::Sprite *const sprite) :
                    GUI::Button(name, gameObj), m_normal(sprite), m_over(sprite), m_status(false)
            {
                m_sprr = gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(m_normal, Layout::gui);
            }

            void Button::SetOver(::SaltyEngine::SFML::Sprite *const sprite) {
                m_over = sprite;
            }

            void Button::SetNormal(::SaltyEngine::SFML::Sprite *const sprite) {
                m_normal = sprite;
            }

            ::SaltyEngine::SFML::Sprite *Button::GetOver(void) const {
                return (m_over);
            }

            ::SaltyEngine::SFML::Sprite *Button::GetNormal(void) const {
                return (m_normal);
            }

            Component *Button::CloneComponent(GameObject *const obj) {
                return new Button(obj, m_over);
            }

            void Button::Update() {
                Vector2i vec = InputKey::GetPosition();
                if (m_sprr->GetSprite()->getLocalBounds().contains(sf::Vector2<float>(vec.x, vec.y)))
                {
                    const std::list<SaltyBehaviour *> & list = gameObject->GetSaltyBehaviour();

                    if (!m_status) {
                        m_sprr->SetSprite(m_over);
                        for (std::list<SaltyBehaviour *>::const_iterator it = list.begin(); it != list.end(); ++it)
                            (*it)->OnMouseEnter();
                    }
                    for (std::list<SaltyBehaviour *>::const_iterator it = list.begin(); it != list.end(); ++it)
                        (*it)->OnMouseOver();
                    m_status = true;
                }
                else if (m_status)
                {
                    m_sprr->SetSprite(m_normal);
                    const std::list<SaltyBehaviour *> & list = gameObject->GetSaltyBehaviour();
                    for (std::list<SaltyBehaviour *>::const_iterator it = list.begin(); it != list.end(); ++it)
                        (*it)->OnMouseExit();
                    m_status = false;
                }
            }
        }
    }
}