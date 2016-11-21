#pragma once

#ifndef SALTYFACTORY_HPP_
#define SALTYFACTORY_HPP_

#include <memory>
#include <list>
#include <map>

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
		static std::shared_ptr<Object> Create(std::string const& name);

		/**
		 * \brief Retrieves all the object of a certain type in the factory
		 */
		template <class T>
		static std::list<std::shared_ptr<Object>> GetObjectsOfType()
		{
			std::list<std::shared_ptr<Object>> objs;
			for (std::shared_ptr<Object> obj : m_objects)
			{
				if (dynamic_cast<T*>(obj.get()))
				{
					objs.push_back(obj);
				}
			}
			return objs;
		}

	private:
		static std::list<std::shared_ptr<Object> > m_objects;
	};
}

#include "SaltyEngine/Object.hpp"

#endif
