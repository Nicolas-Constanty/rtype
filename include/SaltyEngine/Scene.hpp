#pragma once

#ifndef SCENE_HPP_
#define SCENE_HPP_

//#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <iostream>
#include <memory>
#include "SaltyEngine/SaltyReflection.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	public:
		const std::string &GetName() const;
		size_t GetSize() const;
		std::ostream & print(std::ostream &os) const;
		const std::unique_ptr<GameObject> &operator[](size_t index) const;
		void Clear();
		void operator<<(GameObject *gameobj);

	public:
		void OnStart();

		void Update();
		void FixedUpdate();

		void OnTriggerEnter();
		void OnTriggerExit();
		void OnTriggerStay();

		void OnCollisionEnter();
		void OnCollisionExit();
		void OnCollisionStay();

		void OnMouseEnter();
		void OnMouseExit();
		void OnMouseOver();

		void OnGui();

		void CallCoroutines();

	private:
		std::vector<std::unique_ptr<GameObject>>	m_objects;
		size_t							m_counter; // Use to set the m_uid of SaltyBehaviour Objects
		const std::string				m_name;
		std::queue<size_t>				m_init;
	};
};

std::ostream& operator<<(std::ostream& os, SaltyEngine::Scene& obj);

#endif // !SCENE_HPP_

