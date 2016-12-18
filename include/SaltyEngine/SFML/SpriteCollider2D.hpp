//
// Created by nicolas-constanty on 17/12/16.
//

#ifndef RTYPE_SPRITECOLLIDER2D_HPP
#define RTYPE_SPRITECOLLIDER2D_HPP

#include <SFML/Graphics.hpp>
#include <atomic>
#include <stack>
#include "SaltyEngine/SFML/Sprite.hpp"
#include "SaltyEngine/Collider.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        class SpriteCollider2D : public ACollider2D<sf::Vector2i> {
            static std::atomic<uint32_t> m_id;
            static std::vector<uint32_t> m_colors;
        public:
            SpriteCollider2D(const string &name, GameObject * const gameObj);

            explicit SpriteCollider2D(GameObject * const gameObj);

            SpriteCollider2D(GameObject * const gameObj, const sf::Vector2u &size);

            SpriteCollider2D(const string &name, GameObject * const gameObj, const sf::Vector2u &size);

            virtual void Display(void) {};

        public:
            sf::Uint32  GetColor() const;
            sf::Vector2i GetPosition() const;
            sf::Vector2f GetScale() const;
            sf::Vector2u GetSize() const;
            const sf::IntRect &GetRect() const;
            void ResetCollisions();
            void UpdateCollisions(SpriteCollider2D *col);
            void RemoveCollisions();

        private:
            std::map<SpriteCollider2D *, bool> m_collisions;
            std::list<SpriteCollider2D *> m_updated;

        public:
            Sprite *GetSprite() const;

        private:
            sf::Uint32  m_color;
            sf::Image   m_img;
            Sprite      **m_sprite;

        protected:
            sf::IntRect m_rect;

        private:
            void InitImage();
            void InitImage(const sf::Vector2u &size);

        public:
            const sf::Image &GetImage() const;
        };
    }
}
#endif //RTYPE_SPRITECOLLIDER2D_HPP
