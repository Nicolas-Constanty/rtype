#pragma once

#ifndef SALTYFACTORY_HPP_
#define SALTYFACTORY_HPP_

#include <memory>
#include <list>
#include <map>
#include <algorithm>
#include "Common/Singleton.hpp"
#include "Vector2.hpp"

namespace SaltyEngine
{
	/**
	 * \brief The factory allow the engine to clone objects
	 */
	class Object;
	class GameObject;
	class Factory: public Singleton<Factory> {
	public:
		friend class Singleton<Factory>;

	private:
		Factory();
		virtual ~Factory();

	private:
		std::map<std::string, std::unique_ptr<Object>>	m_prefabs;
		std::list<std::unique_ptr<Object>>				m_objects;

	public:
		Object *Create();
		Object	*Create(std::string const& name, Vector const& pos, float rot);

		/**
         * \brief Retrieves all the object of a certain type in the factory
         */
		template <class T>
		std::list<Object*> GetObjectsOfType()
		{
			std::list<Object*> objs;
			for (std::list<std::unique_ptr<Object>>::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it)
			{
				if (dynamic_cast<T*>(it->get()))
				{
					objs.push_back(it->get());
				}
			}
			return objs;
		}

		/**
         * @brief Find game object from its name
         * @param name
         * @return
         */
		GameObject* Find(std::string const& name);

		/**
         * \brief Loads an asset into the memory from a path
         */
		bool LoadAsset(std::string const& path);
	};
}

#include "SaltyEngine/Object.hpp"

#endif
