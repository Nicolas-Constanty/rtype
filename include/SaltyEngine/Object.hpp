#pragma once

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <atomic>
#include <iostream>
#include <string>

namespace SaltyEngine
{
	typedef size_t uid;

	class Object
	{
	public:
		Object() : m_uid(++s_id), m_name("SObj") {};
		Object(const std::string &name) : m_uid(++s_id), m_name(name) {};
		virtual ~Object() {};
		uid GetInstanceID() const;
		const std::string &GetName() const;

	private:
		uid m_uid;
		const std::string &m_name;

	public:
		static void Destroy(Object* original);
		/*static Object *Instantiate(Object* original);
		static Object *Instantiate(Object* original, Transform *parent);
		static Object *Instantiate(Object* original, Vector position, Vector rotation);
		static Object *Instantiate(Object* original, Vector position, Vector rotation, Transform *parent);*/

	private:
		static std::atomic<int> s_id;
	};
}

#endif // !OBJECT_HPP_
