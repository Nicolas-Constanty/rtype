#pragma once

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_


#include "SaltyEngine/Object.hpp"

namespace SaltyEngine
{ 
	class Scene;
	class Transform;
	class GameObject : public Object
	{
	public:
		GameObject() : Object() {};
		GameObject(const std::string &name) : Object(name) {};
		virtual ~GameObject() {};

	private:
		bool activeSelf;
		size_t layer;
		Scene *scene;

	public:
		std::string tag;
		Transform *transform;

	public:

		AddComponent	Adds a component class named className to the game object.
			CompareTag	Is this game object tagged with tag ?
			GetComponent	Returns the component of Type type if the game object has one attached, null if it doesn't.
			GetComponentInChildren	Returns the component of Type type in the GameObject or any of its children using depth first search.
			GetComponentInParent	Returns the component of Type type in the GameObject or any of its parents.
			GetComponents	Returns all components of Type type in the GameObject.
			GetComponentsInChildren	Returns all components of Type type in the GameObject or any of its children.
			GetComponentsInParent	Returns all components of Type type in the GameObject or any of its parents.
			SendMessage	Calls the method named methodName on every MonoBehaviour in this game object.
			SendMessageUpwards	Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.
			SetActive
	};
}
#endif // !GAMEOBJECT_HPP_
