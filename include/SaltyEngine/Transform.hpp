#pragma once

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <vector>
#include "SaltyEngine/Vector3.hpp"
#include "SaltyEngine/Vector2.hpp"
#include "SaltyEngine/Component.hpp"

namespace SaltyEngine
{
    class GameObject;
	template <class T>
	class BaseTransform : public Component
	{
	public:
		// delete copy and move constructors and assign operators
		BaseTransform(BaseTransform const&) = delete;             // Copy construct
		BaseTransform(BaseTransform&&) = delete;                  // Move construct
		BaseTransform& operator=(BaseTransform const&) = delete;  // Copy assign
		BaseTransform& operator=(BaseTransform &&) = delete;      // Move assign
		explicit BaseTransform(GameObject* const gameObj) : Component("Transform", gameObj)
        {
            m_parent = nullptr;
        }

		virtual ~BaseTransform()
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
			for (typename std::vector<BaseTransform<T> *>::const_iterator it = m_children.begin(); it != m_children.end(); ++it)
			{
				if (name == (*it)->GetName())
					return (*it);
			}
			return (nullptr);
		}
		BaseTransform<T> * GetChild(size_t index) const
		{
			return (m_children[index]);
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

        T up() const
        {
            float rot = (rotation + 90.f) * 180.f / M_PI;
            return T(cos(rot), sin(rot));
        }

        T right() const
        {
            float rot = rotation * 180.f / M_PI;
            return T(cos(rot), sin(rot));
        }

		void SetParent(BaseTransform<T> * parent)
		{
			m_parent = parent;
		}
		void Translate(const T & translation)
		{
			position += translation;
		}
		const std::vector<BaseTransform<T> *> &GetChildren()
		{
			return (m_children);
		}
		BaseTransform<T> *GetParent()
		{
			return (m_parent);
		}

	public:
		float rotation;
		float localRotation;
		T position;
		T localPosition;
	private:
		BaseTransform<T>					*m_parent;
		std::vector<BaseTransform<T> *>		m_children;

	public:
		virtual Component *CloneComponent(GameObject* const obj) {
			return new BaseTransform<T>(obj);
		}
	};
}

#ifndef GAME2D
typedef SaltyEngine::BaseTransform<SaltyEngine::Vector>	Transform;
#else
typedef SaltyEngine::BaseTransform<Vector>	Transform;
#endif // !GAME2D

#endif // !TRANSFORM_HPP_
