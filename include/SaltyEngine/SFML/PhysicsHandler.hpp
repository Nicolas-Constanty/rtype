//
// Created by nicolas-constanty on 17/12/16.
//

#ifndef RTYPE_PHYSICSHANDLER_HPP
#define RTYPE_PHYSICSHANDLER_HPP

#include <stack>
#include <list>
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/IPhysicHandler.hpp"

// TODO Optimisation en sauvegadant une seul image par sf::Texture
namespace SaltyEngine
{
    namespace SFML
    {
        class LIB_EXPORT PhysicsHandler : public IPhysicsHandler {
            static const sf::Uint32 m_IntColors[];
            static const sf::Color m_collisionLayersColor[];
//            static std::map<const sf::Uint32, const Layer> m_collisionLayers;
        public:
            typedef std::map<SpriteCollider2D *, bool> ColliderList;
            //typedef std::map<Layer, ColliderList> ColliderLayerMap;
            typedef std::map<sf::Uint32 , SpriteCollider2D *> ColorToSprite;
            typedef std::stack<sf::Vector2i> PixelStack;
            typedef std::stack<SpriteCollider2D *> SpriteStack;
            typedef std::list<const SpriteRenderer *> SpriteList;
        public:
            PhysicsHandler(unsigned int x, unsigned int y, bool debug = true);
            void AddCollider(SpriteCollider2D *const sprr);
            void AddSprite(const SpriteRenderer *s);
            virtual void Clear();
            virtual void Update();
            virtual void Run();
            virtual void Display();

            virtual void Collide();

        public:
            unsigned int GetSizeX() const;

            unsigned int GetSizeY() const;
            void RemoveSpriteCollider(const SpriteCollider2D *);
            void RemoveSpriteRenderer(const SpriteRenderer *);

//            const std::map<Layer, sf::Image> &GetImages() const;

            const sf::Texture &GetTexture() const;

            const sf::Sprite &GetSprite() const;

//            const PixelStack &GetDrawPixels() const;

//            const ColliderLayerMap &GetColliders() const;

        private:
            //std::map<Layer, sf::Image>       m_imgs;
            unsigned int        m_size_x;
            unsigned int        m_size_y;
            sf::Image           m_img;
            sf::Texture         m_texture;
            sf::Sprite          m_sprite;
            PixelStack          m_vecs;
            ColliderList         m_colliders;
            //ColliderLayerMap    m_colliders;
            bool                m_stop;
            SpriteStack         m_deleted;
            ColorToSprite       m_col_to_sprite;
            std::mutex          m_mutext;
            sf::RenderWindow    *m_renderer;
            SpriteList          m_sprites;
        };
    }
}

#endif //RTYPE_PHYSICSHANDLER_HPP
