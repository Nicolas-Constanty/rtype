#include "SaltyEngine/SFML/Scene.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/PhysicsHandler.hpp"
#include "SaltyEngine/SFML/Label.hpp"
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
			gameobj->SetScene(this);
			Renderer *r = dynamic_cast<Renderer *>(Engine::Instance().GetRenderer());
			SFML::SpriteCollider2D *c = gameobj->GetComponent<SFML::SpriteCollider2D>();
			PhysicsHandler *ph = dynamic_cast<PhysicsHandler *>(Engine::Instance().GetPhysicsHandler());
			SpriteRenderer *sprr = gameobj->GetComponent<SpriteRenderer>();
			if (sprr)
			{
				if (r)
				{
					r->AddSpriteRenderer(sprr);
					SFML::BoxCollider2D *bc = gameobj->GetComponent<SFML::BoxCollider2D>();
					if (bc && bc->IsDebug())
						r->AddDebug(bc);
					GUI::Selectable *select = gameobj->GetComponent<GUI::Selectable>();
					if (select)
						r->AddSelectable(select);
				}
				if (ph)
				{
					if (c)
						ph->AddCollider(c);
					else
						ph->AddSprite(sprr);
				}
			}
			GUI::SFML::Label *lb = gameobj->GetComponent<GUI::SFML::Label>();
			if (lb && r)
			{
				r->AddLabel(lb);
			}
		}

        void Scene::InitScene(Component *const component)
        {
			if (component->gameObject->GetScene())
			{
                GameObject *tmp = component->gameObject;
				Renderer *r = dynamic_cast<Renderer *>(Engine::Instance().GetRenderer());
				SFML::SpriteCollider2D *c = tmp->GetComponent<SFML::SpriteCollider2D>();
				PhysicsHandler *ph = dynamic_cast<PhysicsHandler *>(Engine::Instance().GetPhysicsHandler());
				SpriteRenderer *sprr = tmp->GetComponent<SpriteRenderer>();
				if (sprr)
				{
                    tmp->transform.SetLocalScale(m_scale);
					if (r)
					{
						r->AddSpriteRenderer(sprr);
						SFML::BoxCollider2D *bc = tmp->GetComponent<SFML::BoxCollider2D>();
						if (bc && bc->IsDebug())
							r->AddDebug(bc);
						GUI::Selectable *select = tmp->GetComponent<GUI::Selectable>();
						if (select)
							r->AddSelectable(select);
					}
					if (ph)
					{
						if (c)
							ph->AddCollider(c);
						else
							ph->AddSprite(sprr);
					}
				}
                std::list<GUI::SFML::Label *> lb = tmp->GetComponents<GUI::SFML::Label>();
				for (std::list<GUI::SFML::Label *>::const_iterator j = lb.begin(); j != lb.end(); ++j) {
					if (r)
						r->AddLabel(*j);
				}
			}

        }
//
//		void Scene::UpdatePhysics()
//		{
//            Up();
//		}

		void Scene::Destroy() {

            PhysicsHandler *ph = dynamic_cast<PhysicsHandler *>(Engine::Instance().GetPhysicsHandler());
			for (std::list<GameObject *>::iterator i = m_deleted.begin(); i != m_deleted.end(); ++i) {
				if (ph)
				{
					GameObject *gm = (*i);
					SFML::SpriteCollider2D *c = gm->GetComponent<SFML::SpriteCollider2D>();
					SpriteRenderer *sprr = gm->GetComponent<SpriteRenderer>();
					if (c)
						ph->RemoveSpriteCollider(c);
					if (sprr)
						ph->RemoveSpriteRenderer(sprr);
				}
			}
			AScene::Destroy();
		}

//        void Scene::Up() {
//            CollisionTab collisions = m_collisions;
//            for (CollisionTab::iterator me = m_collisions.begin(); me != m_collisions.end(); ++me)
//            {
//                for (CollisionTab::iterator other = m_collisions.begin(); other != m_collisions.end(); ++other)
//                {
//                    if ((*me).first != (*other).first)
//                    {
//                        bool collide = (*me).first->GetBound()->Intersect((*other).first->GetBound());
//                        if ((*me).second.find((*other).first) != (*me).second.end())
//                        {
//                            // Trigger
//                            if ((*me).first->IsTrigger())
//                            {
//                                if (collide)
//                                {
//                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
//                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
//                                    {
//                                        if (!(*me).second[(*other).first])
//                                            m_onTriggerEnter.push(
//                                                    std::bind(&SaltyBehaviour::OnTriggerEnter, (*it), (*other).first)
//                                            );
//                                        else
//                                            m_onTriggerStay.push(
//                                                    std::bind(&SaltyBehaviour::OnTriggerStay, (*it), (*other).first)
//                                            );
//                                    }
//                                }
//                                else
//                                {
//                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
//                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
//                                    {
//                                        if ((*me).second[(*other).first])
//                                            m_onTriggerExit.push(
//                                                    std::bind(&SaltyBehaviour::OnTriggerExit, (*it), (*other).first)
//                                            );
//                                    }
//                                }
//                            }
//                                // Collider
//                            else
//                            {
//                                if (collide)
//                                {
//                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
//                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
//                                    {
//                                        if (!(*me).second[(*other).first])
//                                            m_onCollisionEnter.push(
//                                                    std::bind(&SaltyBehaviour::OnCollisionEnter, (*it), (*other).first)
//                                            );
//                                        else
//                                            m_onCollisionStay.push(
//                                                    std::bind(&SaltyBehaviour::OnCollisionStay, (*it), (*other).first)
//                                            );
//                                    }
//                                }
//                                else
//                                {
//                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
//                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
//                                    {
//                                        if ((*me).second[(*other).first])
//                                            m_onCollisionExit.push(
//                                                    std::bind(&SaltyBehaviour::OnCollisionExit, (*it), (*other).first)
//                                            );
//                                    }
//                                }
//                            }
//                            (*me).second[(*other).first] = collide;
//                        }
//                        else
//                        {
//                            (*me).second[(*other).first] = collide;
//                            if ((*me).first->IsTrigger())
//                            {
//                                if (collide)
//                                {
//                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
//                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
//                                    {
//                                        m_onTriggerEnter.push(
//                                                std::bind(&SaltyBehaviour::OnTriggerEnter, (*it), (*other).first)
//                                        );
//                                    }
//                                }
//                            }
//                            else
//                            {
//                                if (collide)
//                                {
//                                    const std::list<SaltyBehaviour *> &Sb = (*me).first->gameObject->GetSaltyBehaviour();
//                                    for (std::list<SaltyBehaviour *>::const_iterator it = Sb.begin(); it != Sb.end(); ++it)
//                                    {
//                                        m_onCollisionEnter.push(
//                                                std::bind(&SaltyBehaviour::OnCollisionEnter, (*it), (*other).first)
//                                        );
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
    }
}

