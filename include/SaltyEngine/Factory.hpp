#pragma once

#ifndef SALTYFACTORY_HPP_
#define SALTYFACTORY_HPP_

#include <memory>
#include <list>
#include <map>
#include "Vector2.hpp"

namespace SaltyEngine
{
	/**
	 * \brief The factory allow the engine to clone objects
	 */
	class Object;
	class Factory
	{
	private:
		static std::map<std::string, Object*> m_prefabs;
	private:
		virtual ~Factory();

	public:
		static Object *Create();
		static Object	*Create(std::string const& name, Vector const& pos, float rot);

		/**
		 * \brief Retrieves all the object of a certain type in the factory
		 */
		template <class T>
		static std::list<Object*> GetObjectsOfType()
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
		 * \brief Loads an asset into the memory from a path
		 */
		static bool LoadAsset(std::string const& path);

	private:
		static std::list<std::unique_ptr<Object>> m_objects;
	};
}

#include "SaltyEngine/Object.hpp"

#endif
