#include "SaltyEngine/SFML/Scene.hpp"
#include "SaltyEngine/Debug.hpp"

namespace SaltyEngine
{
	namespace SFML
	{
		void Scene::operator<<(GameObject * const gameobj)
		{
			::SaltyEngine::AScene::operator<<(gameobj);
			ACollider2D<sf::Vector2i> *col = dynamic_cast<ACollider2D<sf::Vector2i> *>(gameobj->GetComponent<ACollider2D<sf::Vector2i>>());
			if (col)
			{
				m_collisions[col] = {};
				Debug::PrintSuccess("Successfull add collider");
			}
		}

		void Scene::UpdatePhysics()
		{
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
