#pragma once

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <vector>
#include <cmath>
#include "SaltyEngine/Vector3.hpp"
#include "SaltyEngine/Vector2.hpp"
#include "SaltyEngine/Component.hpp"

namespace SaltyEngine
{
    class GameObject;
	template <class T>
	class LIB_EXPORT BaseTransform : public Component
	{
	public:
		// delete copy and move constructors and assign operators
		BaseTransform(BaseTransform const&) = delete;             // Copy construct
		BaseTransform(BaseTransform&&) = delete;                  // Move construct
		BaseTransform& operator=(BaseTransform const&) = delete;  // Copy assign
		BaseTransform& operator=(BaseTransform &&) = delete;      // Move assign
		explicit BaseTransform(GameObject* const gameObj) : Component("Transform", gameObj), localScale(1, 1)
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
        void Rotate(float angle)
        {
            rotation += angle;

            for (BaseTransform *tr : m_children)
            {
                T diff = tr->position - position;
                tr->Rotate(angle);
                tr->position = position;
                tr->position += tr->right() * diff.magnitude();
            }
        }
		void RotateAround(const T & point, const T & axis, float angle)
		{
			throw std::runtime_error("RotateAround not implemented!");
		}

        T up() const
        {
            float rot = (rotation + 90.f) * M_PI / 180.f;
            return T(cos(rot), sin(rot));
        }

        T right() const
        {
            float rot = rotation * M_PI / 180.f;
            return T(cos(rot), sin(rot));
        }

        void LookAt(BaseTransform<T> const& target)
        {
            rotation = Vector::Angle(position, target.position);
        }

		void SetParent(BaseTransform<T> * parent)
		{
			if (parent != nullptr)
			{
				parent->m_children.push_back(this);
			}
			else if (m_parent != nullptr)
			{
				typename std::vector<BaseTransform<T>*>::iterator this_child = std::find_if(m_parent->m_children.begin(),m_parent->m_children.end(),
											   [&](BaseTransform<T> *other) { return other == this; });
				if (this_child != m_children.end())
				{
                    m_parent->m_children.erase(this_child);
				}
			}
			m_parent = parent;
		}

		/**
		 * @brief Translate the object according to a given vector
		 * @param translation to be done
		 * @note Will also move all the attached children
		 */
		void Translate(const T & translation)
		{
			position += translation;

            for (BaseTransform *tr : m_children)
            {
                tr->position += translation;
            }
		}

        void SetPosition(const T & pos)
        {
            T diff = position - pos;

            position = pos;

            for (BaseTransform *tr : m_children)
            {
                tr->position -= diff;
            }
        }

        void SetPosition(float x, float y)
        {
            SetPosition(T(x, y));
        }

		const std::vector<BaseTransform<T> *> &GetChildren()
		{
			return (m_children);
		}

		BaseTransform<T> *GetParent()
		{
			return (m_parent);
		}

        void SetLocalScale(const T scale)
        {
            localScale = scale;
        }

        void SetRotation(float rot)
        {
            rotation = rot;

            for (BaseTransform *tr : m_children)
            {
                T diff = tr->position - position;
                tr->SetRotation(rot);
                tr->position = position;
                tr->position += tr->right() * diff.magnitude();
            }
        }

        const T GetPosition() const
        {
            return position;
        }

        const T GetLocalScale() const
        {
            return localScale;
        }

        float GetRotation() const
        {
            return rotation;
        }

	protected:
		float rotation = 0;
		float localRotation = 0;
		T position;
		T localPosition;
		T localScale;
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
