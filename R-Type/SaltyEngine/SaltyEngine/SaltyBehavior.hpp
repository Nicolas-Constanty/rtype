#pragma once

#ifndef SALTYBEHAVIOR_HPP_
#define SALTYBEHAVIOR_HPP_

#include <mutex>
#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include "Coroutine.hpp"


namespace SaltyEngine
{
	class Transform;
	class SaltyGame;
#define WaitForSecond(x) coroutine::await(std::bind(&SaltyBehavior::__Wait_For_Seconds, this, x))
#define StartCoroutine(x) m_coroutines.push_back(coroutine::create(std::bind(x, this)))
	class SaltyBehavior
	{
	public:
		explicit SaltyBehavior(const std::string &name);
		virtual ~SaltyBehavior();

	public:
		const std::string &GetName() const;
		size_t GetUID() const;
		bool IsInit() const;
		void Init();

	protected:
		std::vector<coroutine::routine_t> m_coroutines;

	public:
		void __Wait_For_Seconds(size_t time) const;
		void __Wait_For_Milliseconds(size_t time) const;
		void __Wait_For_Microseconds(size_t time) const;

		void CallCoroutines() const;

	private:
		std::string		m_name;
		size_t			m_uid;
		bool			m_status;
		std::mutex		m_mutex;

	public:
		Transform		*transform;
	};
};

#include "Transform.hpp"

std::ostream &operator<<(std::ostream &os, SaltyEngine::SaltyBehavior &object);

#endif // SALTYBEHAVIOR_HPP_

