#pragma once

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <vector>
#include "Vector3.hpp"
#include "SaltyBehavior.hpp"

#define Vector3 Vector3f

namespace SaltyEngine
{
	class Transform
	{
	public:
		Transform();
		Transform(SaltyBehavior *sb);
		~Transform();

	public:

		void DetachChildren();						// Unparents all children.
		Transform *Find(const std::string &name) const;	// Finds a child by name and returns it.
		Transform *GetChild(size_t index) const;				// Returns a transform child by index.
		bool IsChildOf(Transform *parent) const;			// Is this transform a child of parent ?
	 // LookAt										   Rotates the transform so the forward vector points at / target / 's current position.
		void Rotate(const Vector3 &eulerAngles);	// Applies a rotation of eulerAngles.z degrees around the z axis, eulerAngles.x degrees around the x axis, and eulerAngles.y degrees around the y axis(in that order).
		void RotateAround(const Vector3 &point,
			const Vector3 &axis, float angle);		// Rotates the transform about axis passing through point in world coordinates by angle degrees.
		void SetParent(Transform *parent);			// Set the parent of the transform.
		void Translate(const Vector3 &translation);	// Translate the transform
		const std::string &GetName() const;

	public:
		Vector3 rotation;
		Vector3 localRotation;
		Vector3 position;
		Vector3 localPosition;
		Transform					*m_parent;
		std::vector<Transform *>	m_children;
		SaltyBehavior				*m_attach;
	};
}

#endif // !TRANSFORM_HPP_
