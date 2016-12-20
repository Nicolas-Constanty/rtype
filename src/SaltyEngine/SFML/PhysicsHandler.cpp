//
// Created by nicolas-constanty on 17/12/16.
//

#include <SaltyEngine/SFML/SpriteCollider2D.hpp>
#include "SaltyEngine/SFML/PhysicsHandler.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        const sf::Uint32 PhysicsHandler::m_IntColors[] = {
                0x000000FF,
                0x10101010,
                0x202020FF,
                0x303030FF,
                0x404040FF,
                0x505050FF,
                0x606060FF,
                0x707070FF,
                0x808080FF,
                0x909090FF
        };

//        std::map<const sf::Uint32 , const Layer> PhysicsHandler::m_collisionLayers = {
//                { m_IntColors[0], Layer::_00DMG},
//                { m_IntColors[1], Layer::_10DMG},
//                { m_IntColors[2], Layer::_20DMG},
//                { m_IntColors[3], Layer::_30DMG},
//                { m_IntColors[4], Layer::_40DMG},
//                { m_IntColors[5], Layer::_50DMG},
//                { m_IntColors[6], Layer::_60DMG},
//                { m_IntColors[7], Layer::_70DMG},
//                { m_IntColors[8], Layer::_80DMG},
//                { m_IntColors[9], Layer::_90DMG}
//        };

        const sf::Color PhysicsHandler::m_collisionLayersColor[] = {
                sf::Color(m_IntColors[0]),
                sf::Color(m_IntColors[1]),
                sf::Color(m_IntColors[2]),
                sf::Color(m_IntColors[3]),
                sf::Color(m_IntColors[4]),
                sf::Color(m_IntColors[5]),
                sf::Color(m_IntColors[6]),
                sf::Color(m_IntColors[7]),
                sf::Color(m_IntColors[8]),
                sf::Color(m_IntColors[9])
        };



        PhysicsHandler::PhysicsHandler(unsigned int x, unsigned int y, bool debug) : m_size_x(x), m_size_y(y), m_stop(false) {

            m_texture.create(x, y);
            m_img.create(m_size_x, m_size_y, sf::Color::Black);
            m_texture.update(m_img);
            m_sprite.setTexture(m_texture);
            m_renderer = nullptr;
            if (debug)
            {
                std::cout << "Mode Debug Enabled" << std::endl;
                m_renderer = new sf::RenderWindow(sf::VideoMode(m_size_x, m_size_y), "Debug Collisions");
//                m_renderer->setFramerateLimit(60);
            }
        }

        void PhysicsHandler::Clear() {
//            m_mutext.lock();
            while (!m_vecs.empty())
            {
//                m_imgs[m_vecs.top().first].setPixel((unsigned int) (m_vecs.top().second.x), (unsigned int) (m_vecs.top().second.y), m_collisionLayersColor[0]);
//                if (m_renderer)
                    m_img.setPixel((unsigned int) (m_vecs.top().x), (unsigned int) (m_vecs.top().y), sf::Color::Black);
                m_vecs.pop();
            }
//            m_mutext.unlock();
        }



        void PhysicsHandler::Update() {
            for (std::list<const SpriteRenderer *>::const_iterator spr = m_sprites.begin(); spr != m_sprites.end(); ++spr)
            {
                Sprite * s = dynamic_cast<Sprite *>((*spr)->m_sprite);
                if (s)
                {
//                    const sf::IntRect &r = s->getTextureRect();
                    const Transform &t = (*spr)->gameObject->transform;
//                    (*spr)->GetSprite()->setPosition(
//                            t.position.x * t.localScale.x - (r.width * t.localScale.x / 2),
//                            t.position.y * t.localScale.y - (r.height * t.localScale.y / 2)
//                    );
                    (*spr)->GetSprite()->setPosition(t.GetPosition().x * t.GetLocalScale().x, t.GetPosition().y * t.GetLocalScale().y);

                    (*spr)->GetSprite()->setRotation(t.GetRotation());
                }
            }
//            for (ColliderLayerMap::const_iterator col_layer = m_colliders.begin(); col_layer != m_colliders.end(); ++col_layer) {
            if (m_colliders.size())
            {
                bool update = false;
//                    m_mutext.lock();
                for (ColliderList::const_iterator col = m_colliders.begin(); col != m_colliders.end(); ++col) {
//                    (*col)->GetSprite()->setScale((*col)->gameObject->transform.localScale.x, (*col)->gameObject->transform.localScale.y);
                     Transform &t = (*col)->gameObject->transform;
                    const sf::IntRect &r = (*col)->GetRect();
//                    (*col)->GetSprite()->setPosition(
//                            t.position.x * t.localScale.x - (r.width * t.localScale.x / 2),
//                            t.position.y * t.localScale.y - (r.height * t.localScale.y / 2)
//                    );
                    (*col)->GetSprite()->setPosition(t.GetPosition().x * t.GetLocalScale().x, t.GetPosition().y * t.GetLocalScale().y);

                    (*col)->GetSprite()->setRotation(t.GetRotation());

//                    bool deleted = true;
                    float i_pos_x = (*col)->GetPosition().x;
                    float i_pos_y = (*col)->GetPosition().y;
                    float offset_x = i_pos_x - (r.width / 2);
                    float offset_y = i_pos_y - (r.height / 2);
                    unsigned int text_pos_x = (unsigned int) r.left;
                    unsigned int text_pos_y = (unsigned int) r.top;
                    unsigned int text_pos_h = (unsigned int) r.height;
                    unsigned int text_pos_w = (unsigned int) r.width;

                    float posX = t.GetPosition().x;
                    float posY = t.GetPosition().y;

                    if (i_pos_x >= 0 && i_pos_y >= 0 && i_pos_x < m_size_x && i_pos_y < m_size_y)
                    {
                        float radRot = (float) (t.GetRotation() * M_PI / 180.f);
                        float sinRot = sin(radRot);
                        float cosRot = cos(radRot);

                        for (unsigned int y = 0; y < text_pos_h; ++y) {
                            for (unsigned int x = 0; x < text_pos_w; ++x) {
                                float pos_xa = x + offset_x - posX;
                                float pos_ya = y + offset_y - posY;
                                float pos_x = (cosRot * pos_xa - sinRot * pos_ya) + posX;
                                float pos_y = (cosRot * pos_ya + sinRot * pos_xa) + posY;

                                if (pos_x >= 0 && pos_y >= 0 && pos_x < m_size_x && pos_y < m_size_y)
                                {
                                    const sf::Color &color = (*col)->GetImage().getPixel(x + text_pos_x, y + text_pos_y);
                                    if (color != sf::Color::Transparent)
                                    {
                                        m_vecs.push(sf::Vector2i((int) pos_x, (int) pos_y));
                                        sf::Color c = m_img.getPixel((unsigned int) pos_x, (unsigned int) pos_y);
                                        if (c == sf::Color::Black)
                                            m_img.setPixel((unsigned int) (pos_x), (unsigned int) (pos_y), sf::Color((*col)->GetColor()));
//                                            else if (m_renderer &&c != color)
//                                                m_img.setPixel((unsigned int) (pos_x), (unsigned int) (pos_y), sf::Color::Green);
                                        update = true;
//                                        deleted = false;
                                    }
                                }
                            }
                        }
                    }
//                        if (deleted)
//                            m_deleted.push(*col);
                }
                if (update)
                    m_texture.update(m_img);
//                    while (!m_deleted.empty()) {
//                        m_colliders.remove(m_deleted.top());
//                        if (!m_colliders.size())
//                        {
//                                m_texture.update(m_img);
//                        }
//                        m_deleted.pop();
//                    }
            }
        }
        void PhysicsHandler::AddCollider(SpriteCollider2D *const collider) {

            m_mutext.lock();
//            const sf::Vector2i &pos = collider->GetPosition();
//            const sf::Vector2f &scale = collider->GetScale();
//            std::cout << pos.x << " " << pos.y << std::endl;
//            if (pos.x >= 0 && pos.y >= 0 && pos.x / scale.x < m_size_x && pos.y / scale.y < m_size_y) {
//                std::cout << " COUCOU " << std::endl;
                m_colliders.push_back(collider);
                m_col_to_sprite[collider->GetColor()] = collider;
//            }
            m_mutext.unlock();
        }



        unsigned int PhysicsHandler::GetSizeX() const {
            return m_size_x;
        }

        unsigned int PhysicsHandler::GetSizeY() const {
            return m_size_y;
        }

//        const std::map<Layer, sf::Image> &PhysicsHandler::GetImages() const {
//            return m_imgs;
//        }

        const sf::Texture &PhysicsHandler::GetTexture() const {
            return m_texture;
        }

        const sf::Sprite &PhysicsHandler::GetSprite() const {
            return m_sprite;
        }

//        const PhysicsHandler::PixelStack &PhysicsHandler::GetDrawPixels() const {
//            return m_vecs;
//        }
//
//        const PhysicsHandler::ColliderLayerMap &PhysicsHandler::GetColliders() const {
//            return m_colliders;
//        }

        void PhysicsHandler::Run() {
//            Renderer *rend = dynamic_cast<Renderer *>(SaltyEngine::Engine::Instance().GetRenderer());
//            if (rend)
//            {
                while (!m_renderer)
                {
//                    std::cout << "coucouc" << std::endl;
                    Clear();
                    Update();
//                    Display();
                }
//            }
        }

        void PhysicsHandler::Collide()
        {
            for (ColliderList::const_iterator col = m_colliders.begin(); col != m_colliders.end(); ++col) {
                (*col)->ResetCollisions();
                const sf::IntRect &r = (*col)->GetRect();
                float i_pos_x = (*col)->GetPosition().x;
                float i_pos_y = (*col)->GetPosition().y;
                float offset_x = i_pos_x - (r.width / 2);
                float offset_y = i_pos_y - (r.height / 2);
                unsigned int text_pos_x = (unsigned int) r.left;
                unsigned int text_pos_y = (unsigned int) r.top;
                unsigned int text_pos_h = (unsigned int) r.height;
                unsigned int text_pos_w = (unsigned int) r.width;
                if (i_pos_x >= 0 && i_pos_y >= 0 && i_pos_x < m_size_x && i_pos_y < m_size_y)
                {
                    for (unsigned int y = 0; y < text_pos_h; ++y) {
                        for (unsigned int x = 0; x < text_pos_w; ++x) {
                            float pos_x = x + offset_x;
                            float pos_y = y + offset_y;
                            if (pos_x >= 0 && pos_y >= 0 && pos_x < m_size_x && pos_y < m_size_y)
                            {
                                const sf::Color &color = (*col)->GetImage().getPixel(x + text_pos_x, y + text_pos_y);
                                if (color != sf::Color::Transparent)
                                {
                                    sf::Color c = m_img.getPixel((unsigned int) pos_x, (unsigned int) pos_y);
                                    if (c != sf::Color::Black && c != sf::Color::Green && c.toInteger() != (*col)->GetColor())
                                    {
                                        if (m_renderer)
                                            m_img.setPixel((unsigned int) (pos_x), (unsigned int) (pos_y), sf::Color::Green);
                                        (*col)->UpdateCollisions(m_col_to_sprite[c.toInteger()]);
                                        m_col_to_sprite[c.toInteger()]->UpdateCollisions(*col);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            m_texture.update(m_img);
            for (ColliderList::const_iterator col = m_colliders.begin(); col != m_colliders.end(); ++col) {
                (*col)->RemoveCollisions();
            }
        }



//        bool PhysicsHandler::Collide()
//        {
//            if (m_colliders.size() > 1)
//            {
//                for (ColliderLayerMap::const_iterator me = m_colliders.begin(); me != m_colliders.end(); ++me) {
//                    for (ColliderLayerMap::const_iterator other = m_colliders.begin(); other != m_colliders.end(); ++other) {
//                        if (me != other && me->first != other->first)
//                        {
//                            m_mutext.lock();
//                            for (ColliderList::const_iterator col = other->second.begin(); col != other->second.end();) {
//
//                                float i_pos_x = col->first->getPosition().x / col->first->getScale().x;
//                                float i_pos_y = col->first->getPosition().y / col->first->getScale().y;
//                                unsigned int text_pos_x = (unsigned int) col->first->getTextureRect().left;
//                                unsigned int text_pos_y = (unsigned int) col->first->getTextureRect().top;
//                                unsigned int text_pos_w = (unsigned int) col->first->getTextureRect().width;
//                                unsigned int text_pos_h = (unsigned int) col->first->getTextureRect().height;
//                                if (i_pos_x >= 0 && i_pos_y >= 0 && i_pos_x < m_size_x && i_pos_y < m_size_y)
//                                {
//                                    for (unsigned int x = text_pos_w; x > 0; --x) {
//                                        for (unsigned int y = 0; y < text_pos_h; ++y) {
//                                            float pos_x = x + i_pos_x;
//                                            float pos_y = y + i_pos_y;
//                                            if (pos_x >= 0 && pos_y >= 0 && pos_x < m_size_x && pos_y < m_size_y)
//                                            {
//                                                const sf::Color &color = col->second.getPixel(x + text_pos_x, y + text_pos_y);
//                                                const sf::Color &collide_map_color = m_imgs[me->first].getPixel(pos_x, pos_y);
//                                                if (color != sf::Color::Transparent && collide_map_color != m_collisionLayersColor[0])
//                                                {
//                                                    if (m_renderer)
//                                                        m_img.setPixel((unsigned int) (pos_x), (unsigned int) (pos_y), sf::Color::Cyan);
//                                                    goto CollisionUp;
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                                CollisionUp:
//                                ++col;
//                            }
//                            m_mutext.unlock();
//                        }
//                    }
//                }
////        m_mutext.lock();
//                if (m_renderer)
//                    m_texture.update(m_img);
////        m_mutext.unlock();
//            }
//            return false;
//        }

        void PhysicsHandler::Display() {

            if (m_renderer)
            {
                if (m_renderer->isOpen())
                {
                    sf::Event event;
                    while (m_renderer->pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            m_renderer->close();
                    }
                    m_renderer->draw(m_sprite);
                    m_renderer->display();
                }
            }
        }

        void PhysicsHandler::AddSprite(const SpriteRenderer *s) {
            m_sprites.push_back(s);
        }

        void PhysicsHandler::RemoveSpriteCollider(const SpriteCollider2D *s) {
            m_colliders.remove_if([this, s](SpriteCollider2D *sc) {
                if (s == sc)
                {
                    m_col_to_sprite.erase(sc->GetColor());
                    return true;
                }
                return false;
            });
        }

        void PhysicsHandler::RemoveSpriteRenderer(const SpriteRenderer *s) {
            m_sprites.remove_if([s](const SpriteRenderer *sprr) { return (s == sprr); });
        }
    }
}