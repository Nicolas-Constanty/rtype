#pragma once

#ifndef SALTYFACTORY_HPP_
#define SALTYFACTORY_HPP_

#include <memory>
#include <list>
#include <map>
#include <algorithm>
#include <stack>
#include <vector>
#include "SaltyEngine/Constants.hpp"
#include "Common/Singleton.hpp"
#include "Vector2.hpp"

namespace SaltyEngine
{
	/**
	 * \brief The factory allow the engine to clone objects
	 */
	class Object;
	class GameObject;
	class LIB_EXPORT Factory: public Singleton<Factory> {
	public:
		friend class Singleton<Factory>;

	private:
		Factory();
		virtual ~Factory();

	private:
		std::map<std::string, std::unique_ptr<Object>>	m_prefabs;
		std::list<std::unique_ptr<Object>>				m_objects;
		std::stack<std::unique_ptr<SaltyEngine::Asset::ASSET_LOADER> >  m_loaders;

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
         * @brief Find game objects with a certain tag
         * @param tag
         * @return
         */
		GameObject* FindByTag(Layer::Tag tag);
		std::vector<GameObject *> FindAllByTag(Layer::Tag tag);

		/**
         * @brief Loads an asset into the memory from a path
         */
		Asset::ASSET_LOADER *LoadAsset(std::string const& path);

        /**
         * @brief Clear the entire factory. Prefabs and instantiated gameobjects will be removed
         */
        void Clear();
	};
}

template<>
SaltyEngine::Factory &Singleton<SaltyEngine::Factory>::Instance();

#include "SaltyEngine/Object.hpp"

#endif
