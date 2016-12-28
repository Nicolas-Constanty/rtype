//
// Created by nicolas-constanty on 17/12/16.
//

#include "SaltyEngine/SFML/SpriteCollider2D.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "Common/Utils.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine
{
    namespace SFML
    {
        std::atomic<uint32_t> SpriteCollider2D::m_id(0);

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
                m_rect = (*m_sprite)->getTextureRect();
            }
            else
            {
                sf::Image img;
                img.create(size.x, size.y, sf::Color::Magenta);
                Texture *text = new Texture();
                text->create(size.x, size.y);
                text->update(img);
                Sprite *spr = new Sprite(text);
                spr->setScale(gameObject->transform.GetLocalScale().x, gameObject->transform.GetLocalScale().y);
                sprr = gameObject->AddComponent<SpriteRenderer>(spr, Layout::normal);
                m_img = spr->getTexture()->copyToImage();
                m_sprite = (Sprite **)(&sprr->m_sprite);
                m_rect = (*m_sprite)->getTextureRect();
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
                m_rect = (*m_sprite)->getTextureRect();
            }
            else
            {
                m_img.create(40, 40, sf::Color::Magenta);
                Texture *text = new Texture();
                text->create(40, 40);
                text->update(m_img);
                Sprite *spr = new Sprite(text);
                spr->setScale(gameObject->transform.GetLocalScale().x, gameObject->transform.GetLocalScale().y);
                sprr =gameObject->AddComponent<SpriteRenderer>(spr, Layout::normal);
                m_sprite = (Sprite **)(&sprr->m_sprite);
                m_rect = (*m_sprite)->getTextureRect();
            }
        }

        sf::Uint32 SpriteCollider2D::GetColor() const {
            return m_color;
        }

        const sf::Image &SpriteCollider2D::GetImage() const {
            return m_img;
        }

        sf::Vector2i SpriteCollider2D::GetPosition() const {
            return sf::Vector2i((int) gameObject->transform.GetPosition().x, (int) gameObject->transform.GetPosition().y);
        }

        sf::Vector2f SpriteCollider2D::GetScale() const {
            return sf::Vector2f(gameObject->transform.GetLocalScale().x, gameObject->transform.GetLocalScale().y);
        }

        sf::Vector2u SpriteCollider2D::GetSize() const {
            return m_img.getSize();
        }

        const sf::IntRect &SpriteCollider2D::GetRect() const {
            if (m_sprite)
                return (*m_sprite)->getTextureRect();
            else
                return m_rect;
        }

        Sprite *SpriteCollider2D::GetSprite() const {
            return (*m_sprite);
        }

        void SpriteCollider2D::UpdateCollisions(SpriteCollider2D *col) {
//            if (!col)
//            {
//                Debug::PrintWarning("Cannot collide with null");
//                return;
//            }
            AScene *scene = SaltyEngine::Engine::Instance().GetCurrentScene();
            const std::list<SaltyBehaviour *> &sb = gameObject->GetSaltyBehaviour();
            if (m_collisions.find(col) == m_collisions.end())
            {
                m_collisions[col] = true;
                for (std::list<SaltyBehaviour *>::const_iterator it = sb.begin(); it != sb.end(); ++it)
                {
                    if (col->IsTrigger())
                        scene->PushOnTriggerEnter(std::bind(&SaltyBehaviour::OnTriggerEnter, (*it), col));
                    else
                        scene->PushOnCollisionEnter(std::bind(&SaltyBehaviour::OnCollisionEnter, (*it), col));
                }
            } else if (!m_collisions[col])
            {
                m_collisions[col] = true;
                for (std::list<SaltyBehaviour *>::const_iterator it = sb.begin(); it != sb.end(); ++it)
                {
                    if (col->IsTrigger())
                        scene->PushOnTriggerStay(std::bind(&SaltyBehaviour::OnTriggerStay, (*it), col));
                    else
                        scene->PushOnCollisionStay(std::bind(&SaltyBehaviour::OnCollisionStay, (*it), col));
                }
            }
        }

        void SpriteCollider2D::RemoveCollisions() {
//            std::stack<SpriteCollider2D *> deleted;

            AScene *scene = SaltyEngine::Engine::Instance().GetCurrentScene();
            erase_if(m_collisions, [this, scene](const std::pair<SpriteCollider2D *, bool> p){
                if (!p.second) {
                    const std::list<SaltyBehaviour *> &sb = gameObject->GetSaltyBehaviour();
                    for (std::list<SaltyBehaviour *>::const_iterator it = sb.begin(); it != sb.end(); ++it) {
                        if (p.first->IsTrigger())
                            scene->PushOnTriggerExit(std::bind(&SaltyBehaviour::OnTriggerExit, (*it), p.first));
                        else
                            scene->PushOnCollisionExit(
                                    std::bind(&SaltyBehaviour::OnCollisionExit, (*it), p.first));
                    }
                    return true;
                }
                return false;
            });
//            if (m_collisions.size()) {
//                for (std::map<SpriteCollider2D *, bool>::iterator p = m_collisions.begin();
//                     p != m_collisions.end(); ++p) {
//                    if (!p->second) {
//                        const std::list<SaltyBehaviour *> &sb = gameObject->GetSaltyBehaviour();
//                        for (std::list<SaltyBehaviour *>::const_iterator it = sb.begin(); it != sb.end(); ++it) {
//                            if (p->first->IsTrigger())
//                                scene->PushOnTriggerExit(std::bind(&SaltyBehaviour::OnTriggerExit, (*it), p->first));
//                            else
//                                scene->PushOnCollisionExit(
//                                        std::bind(&SaltyBehaviour::OnCollisionExit, (*it), p->first));
//                        }
//                        deleted.push(p->first);
//                    }
//                }
//                while (!deleted.empty())
//                {
//                    m_collisions.erase(deleted.top());
//                    deleted.pop();
//                }
//            }
        }

        void SpriteCollider2D::ResetCollisions() {
            for (std::map<SpriteCollider2D *, bool>::iterator it = m_collisions.begin(); it != m_collisions.end(); ++it)
            {
                (*it).second = false;
            }
        }

        Component *SpriteCollider2D::CloneComponent(GameObject *const obj) {
            return new SpriteCollider2D(obj);
        }

		std::vector<uint32_t> SpriteCollider2D::m_colors = {
//#include "SaltyEngine/SFML/colors.col"
		};
    }
}

