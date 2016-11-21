#pragma once

#ifndef SALTYFACTORY_HPP_
#define SALTYFACTORY_HPP_

#include <memory>
#include <list>
#include "Object.hpp"
#include "GameObject.hpp"
#include <map>

namespace SaltyEngine
{
	/**
	 * \brief The factory allow the engine to clone objects
	 */
	class Factory
	{
	private:
		static std::map<std::string, GameObject*> m_prefabs;
	private:
		virtual ~Factory();

	public:
		template <class ... Args>
		static std::shared_ptr<Object> Create(std::string const& name, Args ... args);

	private:
		static std::list<std::shared_ptr<Object> > m_objects;
	};
}

#endif
