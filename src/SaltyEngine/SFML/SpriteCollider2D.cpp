//
// Created by nicolas-constanty on 17/12/16.
//

#include "SaltyEngine/SFML/SpriteCollider2D.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        std::atomic<uint32_t> SpriteCollider2D::m_id(0);
        std::vector<uint32_t> SpriteCollider2D::m_colors = {
#include "SaltyEngine/SFML/colors.col"
        };

        SpriteCollider2D::SpriteCollider2D(const string &name, GameObject *const gameObj)
                : ACollider2D(name, gameObj)
        {
            m_color = m_colors[m_id];
            InitImage();
            ++m_id;
        }

        SpriteCollider2D::SpriteCollider2D(GameObject *const gameObj)
                : ACollider2D("SpriteCollider2D", gameObj)
        {
            m_color = m_colors[m_id];
            InitImage();
            ++m_id;
        }


        SpriteCollider2D::SpriteCollider2D(const string &name, GameObject *const gameObj, const sf::Vector2u &size)
                : ACollider2D(name, gameObj)
        {
            m_color = m_colors[m_id];
            InitImage(size);
            ++m_id;
        }

        SpriteCollider2D::SpriteCollider2D(GameObject *const gameObj, const sf::Vector2u &size) : ACollider2D("SpriteCollider2D", gameObj) {
            m_color = m_colors[m_id];
            InitImage(size);
            ++m_id;
        }

        void SpriteCollider2D::InitImage(const sf::Vector2u &size)
        {
            m_sprite = nullptr;
            SpriteRenderer *sprr = gameObject->GetComponent<SpriteRenderer>();
            if (sprr)
            {
                Sprite *spr = sprr->GetSprite();
                m_img = spr->getTexture()->copyToImage();
                m_sprite = (Sprite **)(&sprr->m_sprite);
            }
            else
            {
                m_img.create(size.x, size.y, sf::Color::Magenta);
            }
        }

        void SpriteCollider2D::InitImage()
        {
            m_sprite = nullptr;
            SpriteRenderer *sprr = gameObject->GetComponent<SpriteRenderer>();
            if (sprr)
            {
                Sprite *spr = sprr->GetSprite();
                m_img = spr->getTexture()->copyToImage();
                m_sprite = (Sprite **)(&sprr->m_sprite);
            }
            else
            {
                m_img.create(40, 40, sf::Color::Magenta);
            }
        }

        sf::Uint32 SpriteCollider2D::GetColor() const {
            return m_color;
        }

        const sf::Image &SpriteCollider2D::GetImage() const {
            return m_img;
        }

        sf::Vector2i SpriteCollider2D::GetPosition() const {
            return sf::Vector2i(gameObject->transform.position.x, gameObject->transform.position.y);
        }

        sf::Vector2f SpriteCollider2D::GetScale() const {
            return sf::Vector2f(gameObject->transform.localScale.x, gameObject->transform.localScale.y);
        }

        const sf::Vector2u &SpriteCollider2D::GetSize() const {
            return m_img.getSize();
        }

        const sf::IntRect &SpriteCollider2D::GetRect() const {
            if (m_sprite)
                return (*m_sprite)->getTextureRect();
            else
                return sf::IntRect(0, 0, m_img.getSize().x, m_img.getSize().y);
        }

    }
}

