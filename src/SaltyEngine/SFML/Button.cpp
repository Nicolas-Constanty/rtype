//
// Created by nicolas-constanty on 18/12/16.
//

#include <SaltyEngine/SFML.hpp>
#include "SaltyEngine/SFML/Button.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine
{
    namespace GUI
    {
        namespace SFML
        {
            Button::Button(GameObject* gameObj, ::SaltyEngine::SFML::Sprite * const sprite) :
                    GUI::Button("SMFLButton", gameObj), m_normal(sprite), m_over(sprite), m_status(false)
            {
                m_sprr = gameObject->GetComponent<::SaltyEngine::SFML::SpriteRenderer>();
                if (!m_sprr)
                    m_sprr = gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(m_normal, Layout::gui);
                else
                    m_sprr->SetSprite(m_normal);
                eve = dynamic_cast<SaltyEngine::SFML::EventManager *>(SaltyEngine::Engine::Instance().GetEventManager());
            }

            Button::Button(GameObject *gameObj, ::SaltyEngine::SFML::Sprite *const norm,
                           ::SaltyEngine::SFML::Sprite *const over) :
                    GUI::Button("SMFLButton", gameObj), m_normal(norm), m_over(over), m_status(false)
            {
                m_sprr = gameObject->GetComponent<::SaltyEngine::SFML::SpriteRenderer>();
                if (!m_sprr)
                    m_sprr = gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(m_normal, Layout::gui);
                else
                    m_sprr->SetSprite(m_normal);
                eve = dynamic_cast<SaltyEngine::SFML::EventManager *>(SaltyEngine::Engine::Instance().GetEventManager());
            }

            Button::Button(const std::string &name, GameObject *gameObj, ::SaltyEngine::SFML::Sprite *const sprite) :
                    GUI::Button(name, gameObj), m_normal(sprite), m_over(sprite), m_status(false)
            {
                m_sprr = gameObject->GetComponent<::SaltyEngine::SFML::SpriteRenderer>();
                if (!m_sprr)
                    m_sprr = gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(m_normal, Layout::gui);
                else
                    m_sprr->SetSprite(m_normal);
                eve = dynamic_cast<SaltyEngine::SFML::EventManager *>(SaltyEngine::Engine::Instance().GetEventManager());
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
                ::SaltyEngine::SFML::Sprite	*normal = ::SaltyEngine::SFML::AssetManager::Instance().GetSprite(m_normal->GetName());
                if (normal == nullptr) {
                    ::SaltyEngine::SFML::Rect	*rect = dynamic_cast<::SaltyEngine::SFML::Rect*>(m_normal->GetRect());
                    ::SaltyEngine::SFML::Texture	*texture = dynamic_cast<::SaltyEngine::SFML::Texture*>(m_normal->GetTexture());
                    if (rect == nullptr) {
                        normal = new ::SaltyEngine::SFML::Sprite(texture);
                    } else {
                        normal = new ::SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(rect->left, rect->top, rect->width, rect->height));
                    }
                }
                ::SaltyEngine::SFML::Sprite	*over = ::SaltyEngine::SFML::AssetManager::Instance().GetSprite(m_over->GetName());
                if (over == nullptr) {
                    ::SaltyEngine::SFML::Rect	*rect = dynamic_cast<::SaltyEngine::SFML::Rect*>(m_over->GetRect());
                    ::SaltyEngine::SFML::Texture	*texture = dynamic_cast<::SaltyEngine::SFML::Texture*>(m_over->GetTexture());
                    if (rect == nullptr) {
                        over = new ::SaltyEngine::SFML::Sprite(texture);
                    } else {
                        over = new ::SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(rect->left, rect->top, rect->width, rect->height));
                    }
                }
                std::cout << "CLONE" << std::endl;
                return new Button(obj, normal, over);
            }

            void Button::FixedUpdate() {
                if (!eve->IsWindowFocused())
                    return;
                Vector2i vec = InputKey::GetPositionRelative();
                if (m_sprr->GetSprite()->getGlobalBounds().contains(sf::Vector2<float>(vec.x, vec.y)))
                {
                    const std::list<SaltyBehaviour *> & list = gameObject->GetSaltyBehaviour();

                    if (!m_status) {
                        m_sprr->SetSprite(m_over);
                        for (std::list<SaltyBehaviour *>::const_iterator it = list.begin(); it != list.end(); ++it)
                            (*it)->OnMouseEnter();
                        m_status = true;
                    } else {
                        for (std::list<SaltyBehaviour *>::const_iterator it = list.begin(); it != list.end(); ++it)
                            (*it)->OnMouseOver();
                    }
                    if (InputKey::GetButtonPressed(::SaltyEngine::Input::Mouse::Button::Left))
                    {
                        OnPointerClick();
                    }
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

            void Button::OnPointerClick() {
                onClick.InvokeAll();
            }
        }
    }
}