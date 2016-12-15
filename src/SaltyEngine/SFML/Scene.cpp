#include "SaltyEngine/SFML/Scene.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		void Scene::operator<<(GameObject * const gameobj)
		{
			if (gameobj == nullptr)
			{
				Debug::PrintWarning("Scene : NULL object");
				return;
			}
			::SaltyEngine::AScene::operator<<(gameobj);
			Renderer *r = dynamic_cast<Renderer *>(Engine::Instance().GetRenderer());

			SFML::BoxCollider2D *c = gameobj->GetComponent<SFML::BoxCollider2D>();
			ACollider2D<sf::Vector2i> *col = dynamic_cast<ACollider2D<sf::Vector2i> *>(c);
			if (col && r && c)
			{
				m_collisions[col] = {};
                if (c->IsDebug())
				    r->AddDebug(c);
			}
			SpriteRenderer *sprr = gameobj->GetComponent<SpriteRenderer>();
			if (sprr && r)
			{
				r->AddSpriteRenderer(sprr);
			}
			GUI::Selectable *select = gameobj->GetComponent<GUI::Selectable>();
			if (select && r)
			{
				r->AddSelectable(select);
			}
		}

        void Scene::InitScene(Component *const component)
        {
			Renderer *r = dynamic_cast<Renderer *>(Engine::Instance().GetRenderer());

			SFML::BoxCollider2D *c = dynamic_cast<SFML::BoxCollider2D *>(component);
			ACollider2D<sf::Vector2i> *col = dynamic_cast<ACollider2D<sf::Vector2i> *>(c);
			if (col && r && c)
			{
				m_collisions[col] = {};
                if (c->IsDebug())
				    r->AddDebug(c);
			}
			SpriteRenderer *sprr = dynamic_cast<SpriteRenderer *>(component);
			if (sprr && r)
			{
				r->AddSpriteRenderer(sprr);
			}
			GUI::Selectable *select = dynamic_cast<GUI::Selectable *>(component);
			if (select && r)
			{
				r->AddSelectable(select);
			}
        }

		void Scene::UpdatePhysics()
		{
            Up();
		}

		void Scene::Destroy() {

			for (std::list<GameObject *>::iterator i = m_deleted.begin(); i != m_deleted.end(); ++i) {
				GameObject *gm = (*i);
                for(CollisionTab::iterator it = m_collisions.begin(), ite = m_collisions.end(); it != ite;)
                {
                    if (gm == it->first->gameObject)
                        it = m_collisions.erase(it);
                    else
                        ++it;
                }
			}
			AScene::Destroy();
		}

        void Scene::Up() {
            CollisionTab collisions = m_collisions;
            for (CollisionTab::iterator me = m_collisions.begin(); me != m_collisions.end(); ++me)
            {
                for (CollisionTab::iterator other = m_collisions.begin(); other != m_collisions.end(); ++other)
                {
                    if ((*me).first != (*other).first)
                    {
                        bool collide = (*me).first->GetBound()->Intersect((*other).first->GetBound());
                        if ((*me).second.find((*other).first) != (*me).second.end())
                        {
                            // Trigger
                            if ((*me).first->IsTrigger())
                            {
                                if (collide)
                                {
                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
                                    {
                                        if (!(*me).second[(*other).first])
                                            m_onTriggerEnter.push(
                                                    std::bind(&SaltyBehaviour::OnTriggerEnter, (*it), (*other).first)
                                            );
                                        else
                                            m_onTriggerStay.push(
                                                    std::bind(&SaltyBehaviour::OnTriggerStay, (*it), (*other).first)
                                            );
                                    }
                                }
                                else
                                {
                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
                                    {
                                        if ((*me).second[(*other).first])
                                            m_onTriggerExit.push(
                                                    std::bind(&SaltyBehaviour::OnTriggerExit, (*it), (*other).first)
                                            );
                                    }
                                }
                            }
                                // Collider
                            else
                            {
                                if (collide)
                                {
                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
                                    {
                                        if (!(*me).second[(*other).first])
                                            m_onCollisionEnter.push(
                                                    std::bind(&SaltyBehaviour::OnCollisionEnter, (*it), (*other).first)
                                            );
                                        else
                                            m_onCollisionStay.push(
                                                    std::bind(&SaltyBehaviour::OnCollisionStay, (*it), (*other).first)
                                            );
                                    }
                                }
                                else
                                {
                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
                                    {
                                        if ((*me).second[(*other).first])
                                            m_onCollisionExit.push(
                                                    std::bind(&SaltyBehaviour::OnCollisionExit, (*it), (*other).first)
                                            );
                                    }
                                }
                            }
                            (*me).second[(*other).first] = collide;
                        }
                        else
                        {
                            (*me).second[(*other).first] = collide;
                            if ((*me).first->IsTrigger())
                            {
                                if (collide)
                                {
                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
                                    {
                                        m_onTriggerEnter.push(
                                                std::bind(&SaltyBehaviour::OnTriggerEnter, (*it), (*other).first)
                                        );
                                    }
                                }
                            }
                            else
                            {
                                if (collide)
                                {
                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
                                    {
                                        m_onCollisionEnter.push(
                                                std::bind(&SaltyBehaviour::OnCollisionEnter, (*it), (*other).first)
                                        );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

