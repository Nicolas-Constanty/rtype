#pragma once

#ifndef RIGIDBODY2D_HPP_
#define RIGIDBODY2D_HPP_

#include "SaltyEngine/Component.hpp"
#include "SaltyEngine/Vector2.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SaltyEngine.hpp"

namespace SaltyEngine
{
	enum RigidbodyConstraints2D
	{
		None = 0x00,
		FreezePositionX = 0x01,
		FreezePositionY = 0x02,
		FreezeRotation = 0x04,
		FreezePosition = 0x08,
		FreezeAll = 0x10
	};
	template <class T>
	class BaseRigidBody2D : public Component
	{
	public:
		BaseRigidBody2D(GameObject* const gameObj) : public Component("RigidBody2D", gameObj) {};
		~BaseRigidBody2D() {};

	private:
		T						m_angularDrag;		// Coefficient of angular drag.
		T						m_angularVelocity;	// Angular velocity in degrees per second.
		BaseVector2<T>			m_centerOfMass;		//	The center of mass of the rigidBody in local space.
		RigidbodyConstraints2D	m_constraints;		// Controls which degrees of freedom are allowed for the simulation of this Rigidbody2D.
		T						m_drag;				// Coefficient of drag.
		bool					m_freezeRotation;	// Controls whether physics will change the rotation of the object.
		T						m_gravityScale;		// The degree to which this object is affected by gravity.
		T						m_inertia;			// The rigidBody rotational inertia.
		bool					m_kinematic;		// Should this rigidbody be taken out of physics control ?
		T						m_mass;				// Mass of the rigidbody.
		BaseVector2<T>			m_position;			// The position of the rigidbody.
		T						m_rotation;			// The rotation of the rigidbody.
		BaseVector2<T>			m_velocity;			// Linear velocity of the rigidbody.

		// GETTER
	public:
		inline T						GetAngularDrag(void) const { return m_angularDrag; };
		inline T						GetAngularVelocity(void) const { return m_angularVelocity; };
		inline BaseVector2<T>			GetCenterOfMass(void) const { return m_centerOfMass; };
		inline RigidbodyConstraints2D	GetConstraints(void) const { return m_constraints; };
		inline T						GetDrag(void) const { return m_drag; };
		inline bool						GetFreezeRotation(void) const { return m_freezeRotation; };
		inline T						GetGravityScale(void) const { return m_gravityScale; };
		inline T						GetInertia(void) const { return m_inertia; };
		inline bool						IsKinematic(void) const { return m_kinematic; };
		inline T						GetMass(void) const { return  m_mass };
		inline BaseVector2<T>			GetPosition(void) const { m_position; };
		inline T						GetRotation(void) const { return m_rotation; };
		inline BaseVector2<T>			GetVelocity(void) const { return m_velocity; };

		//SETTER
	public:
		inline void SetAngularDrag(T angl_drag) { m_angularDrag = angl_drag; };
		inline void SetAngularVelocity(T angl_vel) { m_angularVelocity = angl_vel; };
		inline void SetCenterOfMass(const BaseVector2<T> &center_of_mass) { m_centerOfMass = center_of_mass; };
		inline void SetConstraints(RigidbodyConstraints2D contrain) { m_constraints |= contrain; };
		inline void SetDrag(T drag) { m_drag = drag; };
		inline void SetFreezeRotation(bool freeze) { m_freezeRotation = freeze; };
		inline void SetGravityScale(T gravity_scale) { m_gravityScale = gravity_scale; };
		inline void SetInertia(T inertia) { m_inertia = inertia; };
		inline void	SetKinematic(bool kinematic) { return m_kinematic; };
		inline void SetMass(T mass) { m_mass = mass; };
		inline void SetPosition(const BaseVector2<T> &pos) { m_position = pos; };
		inline void SetRotation(T rot) { m_rotation = rot; };
		inline void SetVelocity(const BaseVector2<T> &velocity) { m_velocity = velocity; };

	public:
		void AddForce(const BaseVector2<T> &pos); // Apply a force to the rigidbody.
		// void AddRelativeForce(const BaseVector2<T> &pos); //	Adds a force to the rigidbody2D relative to its coordinate system.
	};
	typedef BaseRigidBody2D<float> RigidBody2D;
}

#endif // !RIGIDBODY_HPP_

