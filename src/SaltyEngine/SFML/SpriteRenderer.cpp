//
// Created by nicolas-constanty on 18/12/16.
//

#include "SaltyEngine/SFML/SpriteRenderer.hpp"

namespace SaltyEngine
{
    namespace SFML
    {

        SpriteRenderer::SpriteRenderer(const std::string &name, GameObject *const gameObj, Sprite *const sprite,
                                       Layout layer, Window *const w)
                : ASpriteRenderer(name, gameObj, sprite, layer)
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

        SpriteRenderer::SpriteRenderer(GameObject *const gameObj, Sprite *const sprite, Layout layer, Window *const w)
                : ASpriteRenderer("SpriteRenderer", gameObj, sprite, layer)
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

        Sprite *SpriteRenderer::GetSprite(void) const {
            return (dynamic_cast<Sprite*>(m_sprite));
        }

        IWindow *SpriteRenderer::GetWindow(void) const {
            return (m_window);
        }

        Component *SpriteRenderer::CloneComponent(GameObject *const obj) {
            {
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
        }
    }
}