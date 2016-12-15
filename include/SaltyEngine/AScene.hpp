#pragma once

#ifndef SCENE_HPP_
#define SCENE_HPP_

//#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <memory>
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/Component.hpp"
#include <functional>

namespace SaltyEngine
{
	class GameObject;
    class SaltyBehaviour;
	class AScene : public Object
	{
        friend class Engine;
	public:
		AScene();
		explicit AScene(const std::string &name);
		virtual ~AScene();

	public:
		size_t GetSize(void) const;
		float GetGravity(void) const;
		void SetGravity(float gravity);
		std::ostream & print(std::ostream &os) const;
		GameObject const &operator[](size_t index) const;
		void Clear();
		GameObject	*FindByName(std::string const &name) const;
		GameObject	*FindById(size_t id) const;
		virtual void operator<<(GameObject * const gameobj);


	public:
		void OnStart(void);

		void FixedUpdate(void);

		void OnTriggerEnter(void);
		void OnTriggerExit(void);
		void OnTriggerStay(void);

		void OnCollisionEnter(void);
		void OnCollisionExit(void);
		void OnCollisionStay(void);

		void OnMouseEnter(void);
		void OnMouseExit(void);
		void OnMouseOver(void);

		void Update(void);
		void OnGui(void);
		void OnDestroy();

		void CallCoroutines();
		virtual void UpdatePhysics(void) {};

		virtual void Destroy(GameObject *gm);
        virtual void InitScene(Component *const component) { (void)component; };

	protected:
		virtual void Destroy();

	protected:
		std::vector<GameObject *>	m_objects;
		std::queue<size_t>			m_init;
		float						m_gravity;
		std::list<GameObject *>		m_deleted;

	protected:
		std::queue<std::function<void()>>	m_onCollisionEnter;
		std::queue<std::function<void()>>	m_onCollisionStay;
		std::queue<std::function<void()>>	m_onCollisionExit;

		std::queue<std::function<void()>>	m_onTriggerEnter;
		std::queue<std::function<void()>>	m_onTriggerStay;
		std::queue<std::function<void()>>	m_onTriggerExit;

	public:
		friend std::ostream &operator<<(std::ostream &os, AScene &obj) {
			return os << "Scene " << obj.GetName() << " :" << std::endl;
		};
	};
};

#endif // !SCENE_HPP_
