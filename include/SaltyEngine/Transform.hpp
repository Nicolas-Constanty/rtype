#pragma once

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <vector>
#include "Vector3.hpp"
#include "Vector2.hpp"

#ifndef GAME2D
namespace SaltyEngine
{
	typedef Vector2 Vector;
}
#else
namespace SaltyEngine
{
	typedef Vector3 Vector;
}
#endif

namespace SaltyEngine
{
	class SaltyBehavior;
	template <class T>
	class BaseTransform
	{
	public:
		BaseTransform() :
			rotation(T::zero()), localRotation(T::zero()),
			position(T::zero()), localPosition(T::zero())
		{
			m_parent = nullptr;
			m_attach = nullptr;
		}

		BaseTransform(SaltyBehavior *sb) :
			rotation(T::zero()), localRotation(T::zero()),
			position(T::zero()), localPosition(T::zero())
		{
			m_attach = sb;
			m_parent = nullptr;
		}

		~BaseTransform()
		{
			if (!m_children.empty())
				DetachChildren();
		}

	public:
		void DetachChildren()
		{
			m_children.clear();
		}
		BaseTransform<T> *Find(const std::string &name) const
		{
			for (std::vector<BaseTransform<T> *>::const_iterator it = m_children.begin(); it != m_children.end(); it++)
			{
				if (name == (*it)->GetName())
					return (*it);
			}
			return nullptr;
		}
		BaseTransform<T> * GetChild(size_t index) const
		{
			return m_children[index];
		}
		bool IsChildOf(BaseTransform<T> *parent) const
		{
			return (parent == m_parent);
		}
		void Rotate(const T & eulerAngles)
		{
			throw std::runtime_error("Rotate not implemented!");
		}
		void RotateAround(const T & point, const T & axis, float angle)
		{
			throw std::runtime_error("RotateAround not implemented!");
		}
		void SetParent(BaseTransform<T> * parent)
		{
			m_parent = parent;
		}
		void Translate(const T & translation)
		{
			position += translation;
		}
		const std::string & GetName() const
		{
			if (m_attach)
				return m_attach->GetName();
			throw std::runtime_error("No attachement!");
		}

	public:
		T rotation;
		T localRotation;
		T position;
		T localPosition;
		BaseTransform<T>				*m_parent;
		std::vector<BaseTransform<T> *>	m_children;
		SaltyBehavior				*m_attach;
	};

	typedef BaseTransform<Vector3>	Transform3D;
	typedef BaseTransform<Vector2>	Transform2D;

	typedef BaseTransform<Vector>	Transform;
}

#include "SaltyBehavior.hpp"

#endif // !TRANSFORM_HPP_
