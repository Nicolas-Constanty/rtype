#pragma once

#ifndef SPRITERENDERER_HPP_
#define SPRITERENDERER_HPP_

#include "SaltyEngine/Config.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"
#include "SaltyEngine/SFML/Window.hpp"
#include "SaltyEngine/SFML/Renderer.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        class SpriteRenderer : public ASpriteRenderer<sf::Vector2i>
        {
        public:
            // delete copy and move constructors and assign operators
            SpriteRenderer(SpriteRenderer const&) = delete;             // Copy construct
            SpriteRenderer(SpriteRenderer&&) = delete;                  // Move construct
            SpriteRenderer& operator=(SpriteRenderer const&) = delete;  // Copy assign
            SpriteRenderer& operator=(SpriteRenderer &&) = delete;      // Move assign
            explicit SpriteRenderer(const std::string &name, GameObject * const gameObj, Sprite * const sprite, Layout layer, Window * const w = nullptr) : ASpriteRenderer(name, gameObj, sprite, layer)
            {
                if (sprite == nullptr) {
                    m_sprite = new Sprite(nullptr);
                }

                m_window = w;
                Rect *rect = dynamic_cast<Rect *>(GetSprite()->GetRect());
                if (rect)
                {
                    GetSprite()->setPosition(gameObject->transform.position.x - (rect->width / 2),
                                             gameObject->transform.position.y - (rect->height / 2));
                }
                else
                {
                    GetSprite()->SetRect(new Rect(0, 0, GetSprite()->GetTexture()->GetSize().x, GetSprite()->GetTexture()->GetSize().y));
                    rect = dynamic_cast<Rect *>(GetSprite()->GetRect());
                    GetSprite()->setPosition(gameObject->transform.position.x - (rect->width / 2),
                                             gameObject->transform.position.y - (rect->height / 2));
                }
            }
            explicit SpriteRenderer(GameObject* const gameObj, Sprite * const sprite, Layout layer, Window * const w = nullptr) : ASpriteRenderer("SpriteRenderer", gameObj, sprite, layer)
            {
                if (sprite == nullptr) {
                    m_sprite = new Sprite(nullptr);
                }

                m_window = w;
                Rect *rect = dynamic_cast<Rect *>(GetSprite()->GetRect());
                if (rect)
                {
                    GetSprite()->setPosition(gameObject->transform.position.x - (rect->width / 2),
                                             gameObject->transform.position.y - (rect->height / 2));
                }
                else
                {
                    GetSprite()->SetRect(new Rect(0, 0, GetSprite()->GetTexture()->GetSize().x, GetSprite()->GetTexture()->GetSize().y));
                    rect = dynamic_cast<Rect *>(GetSprite()->GetRect());
                    GetSprite()->setPosition(gameObject->transform.position.x - (rect->width / 2),
                                             gameObject->transform.position.y - (rect->height / 2));
                }

            }
            virtual ~SpriteRenderer() {

            };
            Sprite* GetSprite(void) const override
            {
                return (dynamic_cast<Sprite*>(m_sprite));
            };

            IWindow *GetWindow(void) const override
            {
                return (m_window);
            }

        public:
            virtual Component *CloneComponent(GameObject* const obj) {
                Sprite	*sprite = AssetManager::Instance().GetSprite(m_sprite->GetName());
                if (sprite == nullptr) {
                    Rect	*rect = dynamic_cast<Rect*>(m_sprite->GetRect());
                    Texture	*texture = dynamic_cast<Texture*>(m_sprite->GetTexture());
                    if (rect == nullptr) {
                        sprite = new Sprite(texture);
                    } else {
                        sprite = new Sprite(texture, new Rect(rect->left, rect->top, rect->width, rect->height));
                    }
                }
                return new SpriteRenderer(obj, sprite, m_layer, (Window*)m_window);
            }
        };
    }
}

#endif // !SPRITERENDERER_HPP_
