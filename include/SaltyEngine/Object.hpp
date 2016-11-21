#pragma once

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <atomic>
#include <iostream>
#include <string>

namespace SaltyEngine
{
	static std::string const Tag[] = { "NONE", "PLAYER", "ENEMY" };
	typedef size_t uid;

	class Object
	{
	private:
		static std::atomic<int> s_id;
	public:
		// delete copy and move constructors and assign operators
		Object(Object const&) = delete;             // Copy construct
		Object(Object&&) = delete;                  // Move construct
		Object& operator=(Object const&) = delete;  // Copy assign
		Object& operator=(Object &&) = delete;      // Move assign
		Object(const std::string &name) : m_uid(++s_id), m_name(name) {};
		virtual ~Object() {};

	public:
		uid GetInstanceID() const;
		const std::string &GetName() const;

	private:
		uid m_uid;
		std::string m_name;

	public:
		static void Destroy(Object* original);
	};
}

#endif // !OBJECT_HPP_
