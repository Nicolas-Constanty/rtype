#include "Transform.hpp"

namespace SaltyEngine
{
	Transform::Transform() : rotation(Vector3::zero()),
		localRotation(Vector3::zero()),
		position(Vector3::zero()),
		localPosition(Vector3::zero())
	{
		m_parent = nullptr;
		m_attach = nullptr;
	}

	Transform::Transform(SaltyBehavior *sb) : rotation(Vector3::zero()),
		localRotation(Vector3::zero()),
		position(Vector3::zero()),
		localPosition(Vector3::zero())
	{
		m_attach = sb;
		m_parent = nullptr;
	}

	Transform::~Transform()
	{
	}
	void Transform::DetachChildren()
	{
	}
	Transform *Transform::Find(const std::string &name) const
	{
		for (std::vector<Transform *>::const_iterator it = m_children.begin(); it != m_children.end(); it++)
		{
			if (name == (*it)->GetName())
				return (*it);
		}
		return nullptr;
	}
	Transform * Transform::GetChild(size_t index) const
	{
		return m_children[index];
	}
	bool Transform::IsChildOf(Transform *parent) const
	{
		return (parent == m_parent);
	}
	void Transform::Rotate(const Vector3 & eulerAngles)
	{
		throw std::runtime_error("Rotate not implemented!");
	}
	void Transform::RotateAround(const Vector3 & point, const Vector3 & axis, float angle)
	{
		throw std::runtime_error("RotateAround not implemented!");
	}
	void Transform::SetParent(Transform * parent)
	{
		m_parent = parent;
	}
	void Transform::Translate(const Vector3 & translation)
	{
		position += translation;
	}
	const std::string & Transform::GetName() const
	{
		if (m_attach)
			return m_attach->GetName();
		throw std::runtime_error("No attachement!");
	}
}