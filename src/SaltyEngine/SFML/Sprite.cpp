//
// Created by nicolas-constanty on 18/12/16.
//

#include "SaltyEngine/SFML/Sprite.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        Sprite::Sprite(Texture *texture) :
                ::SaltyEngine::Sprite<sf::Vector2i>(texture ? dynamic_cast<::SaltyEngine::Texture<sf::Vector2i> *>(texture) : []() { ::SaltyEngine::Texture<sf::Vector2i> *t = new Texture(); t->Create(200, 200); return t; }(), "SFMLSprite"),
                sf::Sprite(*dynamic_cast<Texture *>(GetTexture())) {
            m_bounds = new Rect(static_cast<int>(getTextureRect().left), static_cast<int>(getTextureRect().top), static_cast<int>(getTextureRect().width), static_cast<int>(getTextureRect().height));
            setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
        }

        Sprite::Sprite(Texture *texture, Rect *const rect) :
                ::SaltyEngine::Sprite<sf::Vector2i>(texture ? dynamic_cast<::SaltyEngine::Texture<sf::Vector2i> *>(texture) : []() { ::SaltyEngine::Texture<sf::Vector2i> *t = new Texture(); t->Create(200, 200); return t; }(), rect, "SFMLSprite"),
                sf::Sprite(*dynamic_cast<Texture *>(GetTexture()))
        {
			if (rect->top + rect->height > texture->GetSize().y)
				rect->height = texture->GetSize().y - rect->top;
			if (rect->left + rect->width > texture->GetSize().x)
				rect->width = texture->GetSize().x - rect->left;

            setTextureRect(*rect);
            m_bounds = new Rect(static_cast<int>(getTextureRect().left), static_cast<int>(getTextureRect().top), static_cast<int>(getTextureRect().width), static_cast<int>(getTextureRect().height));
            setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
        }

        Rect *Sprite::GetBounds() const {
            m_bounds->left = static_cast<int>(getGlobalBounds().left);
            m_bounds->top = static_cast<int>(getGlobalBounds().top);
            m_bounds->width = static_cast<int>(getGlobalBounds().width);
            m_bounds->height = static_cast<int>(getGlobalBounds().height);
            return m_bounds;
        }

        Sprite::~Sprite() {
            delete m_bounds;
        }
    }
}