#pragma once

#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_

#include "SaltyEngine/Component.hpp"
#include "SaltyEngine/RigidBody.hpp"
#include "SaltyEngine/BasicRect.hpp"
#include "SaltyEngine/ASpriteRenderer.hpp"
#include "SaltyEngine/ICollider.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine
{
	template <class T>
	class ACollider2D : public Component, public ICollider
	{
	public:
		explicit ACollider2D(GameObject * const gameObj) : Component("Collider2D", gameObj), m_enabled(true), m_trigger(false) {
			m_attachedRigidbody = gameObject->AddComponent<RigidBody2D>();
			ASpriteRenderer<T> *sprr = gameObject->GetComponent<ASpriteRenderer<T>>();
			if (sprr)
			{
				m_bounds = sprr->GetSprite()->GetBounds();
			}
			else
            {
                m_bounds = new BasicRect<T>((int) (gameObject->transform.GetPosition().x - 20),
                                       (int) (gameObject->transform.GetPosition().y - 20),
                                       40, 40);
            }
		};
		ACollider2D(const std::string &name, GameObject * const gameObj) : Component(name, gameObj), m_enabled(true), m_trigger(false) {
			m_attachedRigidbody = gameObject->AddComponent<RigidBody2D>();
			ASpriteRenderer<T> *sprr = gameObject->GetComponent<ASpriteRenderer<T>>();
			if (sprr)
				m_bounds = sprr->GetSprite()->GetBounds();
			else
            {
                m_bounds = new BasicRect<T>((int)(gameObject->transform.GetPosition().x - 50),
                                       (int)(gameObject->transform.GetPosition().y - 50),
                                       100, 100);
            }
		};
        ACollider2D(const std::string &name, GameObject * const gameObj, BasicRect<T> *rect) : Component(name, gameObj), m_enabled(true), m_trigger(false) {
            m_attachedRigidbody = gameObject->AddComponent<RigidBody2D>();
            m_bounds = rect;
        };
		virtual ~ACollider2D() {};

	protected:
		RigidBody2D	*m_attachedRigidbody;	// The rigidbody the collider is attached to.
		BasicRect<T>	*m_bounds;				// The world space bounding volume of the collider.
		bool		m_enabled;				// Enabled Colliders will collide with other colliders, disabled Colliders won't.
		bool		m_trigger;				// Is the collider a trigger ?

	public:
		bool IsTrigger(void) const { return m_trigger; };
		bool IsEnable(void) const { return m_enabled; };
		BasicRect<T> *GetBound(void) const { return m_bounds; };
		RigidBody2D *GetRigidBody(void) const { return m_attachedRigidbody; };

	public:
		void SetTrigger(bool trigger) { m_trigger = trigger; };
		void SetEnable(bool enable) { m_enabled = enable; };
		void SetBound(BasicRect<T> * const rect) {
			if (m_bounds)
				delete m_bounds;
			m_bounds = rect; 
		};
		void SetRigidBody(RigidBody2D * const rigid) { 
			if (m_attachedRigidbody)
				delete m_attachedRigidbody;
			m_attachedRigidbody = rigid; 
		};

	public:
		virtual void Display(void) = 0;
	};
}

#endif // !COLLIDER_HPP_
