#pragma once

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <atomic>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Vector2.hpp"
#include "Common/ICloneable.hpp"
#include "Factory.hpp"

namespace SaltyEngine
{
	static std::string const Tag[] = { "NONE", "PLAYER", "ENEMY" };
	typedef size_t uid;

	class Object: protected ICloneable<Object>
	{
	private:
		static std::atomic<int> s_id;
	public:
		// delete copy and move constructors and assign operators
		Object(Object const&) = delete;             // Copy construct
		Object(Object&&) = delete;                  // Move construct
		Object& operator=(Object const&) = delete;  // Copy assign
		Object& operator=(Object &&) = delete;      // Move assign
		explicit Object(const std::string &name) : m_uid(++s_id), m_name(name) {};
		virtual ~Object() {};

	public:
		uid GetInstanceID(void) const;
		const std::string &GetName(void) const;

	private:
		uid m_uid;
		const std::string m_name;

	public:
		static void Destroy(Object* original);
		static Object *Instantiate(std::string const& obj, Vector pos = Vector::zero(), float rot = 0)
		{
			return Factory::Create(obj, pos, rot);
		}

		static Object *Instantiate()
		{
			return Factory::Create();
		}

	public:
		std::unique_ptr<Object> Clone() override
		{
			return (std::unique_ptr<Object>(new Object(m_name + "(Clone)")));
        }

		std::unique_ptr<Object> CloneMemberwise() override
		{
			return (std::unique_ptr<Object>(new Object(m_name + "(Clone)")));
        }

	public:
		/**
		 * _\brief : retrieves all the object of a certain type currently instantiated.
		 * This is slow, so consider using it wisely
		 */
		template <class Type>
		static std::list<Object*> FindObjectsOfType()
		{
			return Factory::GetObjectsOfType<Type>();
		}
	};

#ifdef _WIN32
//#define Instantiate(...) Object::Instantiate(## __VA_ARGS__)
	#define Instantiate(...) Object::Instantiate(__VA_ARGS__)
#else
#define Instantiate(...) Object::Instantiate(__VA_ARGS__)
#endif
}

#endif // !OBJECT_HPP_
