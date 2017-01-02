//
// Created by nicolas-constanty on 17/12/16.
//

#include <SaltyEngine/SFML/SpriteCollider2D.hpp>
#include <SaltyEngine/Maths.hpp>
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



        PhysicsHandler::PhysicsHandler(unsigned int x, unsigned int y, bool debug) : APhysicsHandler(x, y), m_stop(false) {

            m_texture.create(x, y);
            m_img.create(m_size.x, m_size.y, sf::Color::Black);
            m_texture.update(m_img);
            m_sprite.setTexture(m_texture);
            m_renderer = nullptr;
            if (debug)
            {
                std::cout << "Mode Debug Enabled" << std::endl;
                m_renderer = new sf::RenderWindow(sf::VideoMode(m_size.x, m_size.y), "Debug Collisions");
            }
        }

        void PhysicsHandler::Clear() {
            while (!m_vecs.empty())
            {
                    m_img.setPixel((unsigned int) (m_vecs.top().x), (unsigned int) (m_vecs.top().y), sf::Color::Black);
                m_vecs.pop();
            }
        }



        void PhysicsHandler::Update() {
            for (std::list<const SpriteRenderer *>::const_iterator spr = m_sprites.begin(); spr != m_sprites.end(); ++spr)
            {
                Sprite * s = dynamic_cast<Sprite *>((*spr)->m_sprite);
                if (s)
                {
                    const Transform &t = (*spr)->gameObject->transform;
                    (*spr)->GetSprite()->setPosition(t.GetPosition().x * t.GetLocalScale().x, t.GetPosition().y * t.GetLocalScale().y);

                    (*spr)->GetSprite()->setRotation(t.GetRotation());
                }
            }
            if (m_colliders.size())
            {
                bool update = false;
                for (ColliderList::iterator col = m_colliders.begin(); col != m_colliders.end(); ++col) {
                    if (!(*col).first->gameObject->GetActiveSelf())
                        continue;
                    SpriteCollider2D *spr = (*col).first;
                     Transform &t = spr->gameObject->transform;
                    const sf::IntRect &r = spr->GetRect();
                    spr->GetSprite()->setPosition(t.GetPosition().x * t.GetLocalScale().x, t.GetPosition().y * t.GetLocalScale().y);
                    spr->GetSprite()->setRotation(t.GetRotation());
                    bool deleted = true;
                    float i_pos_x = spr->GetPosition().x;
                    float i_pos_y = spr->GetPosition().y;
                    float offset_x = i_pos_x - (r.width / 2);
                    float offset_y = i_pos_y - (r.height / 2);
                    unsigned int text_pos_x = (unsigned int) r.left;
                    unsigned int text_pos_y = (unsigned int) r.top;
                    unsigned int text_pos_h = (unsigned int) r.height;
                    unsigned int text_pos_w = (unsigned int) r.width;

                    float posX = t.GetPosition().x;
                    float posY = t.GetPosition().y;
                    float sinRot = Mathf::Sin(t.GetRotation());
                    float cosRot = Mathf::Cos(t.GetRotation());


                    for (unsigned int y = 0; y < text_pos_h; ++y) {
                        for (unsigned int x = 0; x < text_pos_w; ++x) {
                            float pos_xa = x + offset_x - posX;
                            float pos_ya = y + offset_y - posY;
                            float pos_x = (cosRot * pos_xa - sinRot * pos_ya) + posX;
                            float pos_y = (cosRot * pos_ya + sinRot * pos_xa) + posY;

                            if (pos_x >= 0 && pos_y >= 0 && pos_x < m_size.x && pos_y < m_size.y)
                            {
                                const sf::Color &color = spr->GetImage().getPixel(x + text_pos_x, y + text_pos_y);
                                if (color != sf::Color::Transparent)
                                {
                                    m_vecs.push(sf::Vector2i((int) pos_x, (int) pos_y));
                                    sf::Color c = m_img.getPixel((unsigned int) pos_x, (unsigned int) pos_y);
                                    if (c == sf::Color::Black)
                                        m_img.setPixel((unsigned int) (pos_x), (unsigned int) (pos_y), sf::Color(spr->GetColor()));
                                    update = true;
                                    deleted = false;
                                    (*col).second = true;
                                }
                            }
                        }
                    }
                        if (deleted && (*col).second)
                            m_deleted.push(spr);
                }
                if (update)
                    m_texture.update(m_img);
                    while (!m_deleted.empty()) {
                        Object::Destroy(m_deleted.top()->gameObject);
                        m_colliders.erase(m_deleted.top());
                        if (!m_colliders.size())
                            m_texture.update(m_img);
                        m_deleted.pop();
                    }
            }
        }
        void PhysicsHandler::AddCollider(SpriteCollider2D *const collider) {

            m_mutext.lock();
            if (m_colliders.find(collider) == m_colliders.end())
                m_colliders[collider] = false;
            if (m_col_to_sprite.find(collider->GetColor()) == m_col_to_sprite.end())
                m_col_to_sprite[collider->GetColor()] = collider;
            m_mutext.unlock();
        }

        const sf::Texture &PhysicsHandler::GetTexture() const {
            return m_texture;
        }

        const sf::Sprite &PhysicsHandler::GetSprite() const {
            return m_sprite;
        }

        void PhysicsHandler::Run() {
            while (!m_renderer)
            {
                Clear();
                Update();
            }
        }

        void PhysicsHandler::Collide()
        {
            for (ColliderList::const_iterator col = m_colliders.begin(); col != m_colliders.end(); ++col) {
                if (!(*col).first->gameObject->GetActiveSelf())
                    continue;
                SpriteCollider2D *spr = (*col).first;
                spr->ResetCollisions();
                const sf::IntRect &r = spr->GetRect();
                float i_pos_x = spr->GetPosition().x;
                float i_pos_y = spr->GetPosition().y;
                float offset_x = i_pos_x - (r.width / 2);
                float offset_y = i_pos_y - (r.height / 2);
                unsigned int text_pos_x = (unsigned int) r.left;
                unsigned int text_pos_y = (unsigned int) r.top;
                unsigned int text_pos_h = (unsigned int) r.height;
                unsigned int text_pos_w = (unsigned int) r.width;
                if (i_pos_x >= 0 && i_pos_y >= 0 && i_pos_x < m_size.x && i_pos_y < m_size.y)
                {
                    for (unsigned int y = 0; y < text_pos_h; ++y) {
                        for (unsigned int x = 0; x < text_pos_w; ++x) {
                            float pos_x = x + offset_x;
                            float pos_y = y + offset_y;
                            if (pos_x >= 0 && pos_y >= 0 && pos_x < m_size.x && pos_y < m_size.y)
                            {
                                const sf::Color &color = spr->GetImage().getPixel(x + text_pos_x, y + text_pos_y);
                                if (color != sf::Color::Transparent)
                                {
                                    sf::Color c = m_img.getPixel((unsigned int) pos_x, (unsigned int) pos_y);
                                    if (c != sf::Color::Black && c != sf::Color::Green && c.toInteger() != spr->GetColor())
                                    {
                                        if (m_renderer)
                                            m_img.setPixel((unsigned int) (pos_x), (unsigned int) (pos_y), sf::Color::Green);
                                        if (m_col_to_sprite[c.toInteger()] != nullptr)
                                            m_col_to_sprite[c.toInteger()]->UpdateCollisions(spr);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            m_texture.update(m_img);
            for (ColliderList::const_iterator col = m_colliders.begin(); col != m_colliders.end(); ++col) {
                (*col).first->RemoveCollisions();
            }
        }

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
            if (std::find(m_sprites.begin(), m_sprites.end(), s) == m_sprites.end())
                m_sprites.push_back(s);
        }

        void PhysicsHandler::RemoveSpriteCollider(const SpriteCollider2D *s) {
            erase_if(m_colliders, [this, s](const std::pair<SpriteCollider2D *, bool> p){
                if (s == p.first) {
                    m_col_to_sprite.erase(s->GetColor());
                    return true;
                }
                return false;
            });
        }

        void PhysicsHandler::RemoveSpriteRenderer(const SpriteRenderer *s) {
            m_sprites.remove_if([s](const SpriteRenderer *sprr) { return (s == sprr); });
        }

        void PhysicsHandler::SetSize(unsigned int x, unsigned y) {
            m_size.x = x;
            m_size.y = y;
            m_img.create(m_size.x, m_size.y, sf::Color::Black);
            m_renderer->setSize(sf::Vector2u(m_size.x, m_size.y));
            m_renderer->setView(sf::View(sf::FloatRect(0.f, 0.f, m_size.x, m_size.y)));
        }
    }
}