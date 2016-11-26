#pragma once

#ifndef SALTYBEHAVIOR_HPP_
#define SALTYBEHAVIOR_HPP_

#include <mutex>
#include <vector>
#include <functional>
#include "SaltyEngine/Coroutine.hpp"
#include "SaltyEngine/Behaviour.hpp"

namespace SaltyEngine
{
	class SaltyEngine;
#define WaitForSecond(x) coroutine::await(std::bind(&SaltyBehaviour::__Wait_For_Seconds, this, x))
#define StartCoroutine(x) m_coroutines.push_back(coroutine::create(std::bind(x, this)))
	class SaltyBehaviour : public Behaviour
	{
	public:
		// delete copy and move constructors and assign operators
		SaltyBehaviour(SaltyBehaviour const&) = delete;             // Copy construct
		SaltyBehaviour(SaltyBehaviour&&) = delete;                  // Move construct
		SaltyBehaviour& operator=(SaltyBehaviour const&) = delete;  // Copy assign
		SaltyBehaviour& operator=(SaltyBehaviour &&) = delete;      // Move assign
		SaltyBehaviour(GameObject* gameObj);
		SaltyBehaviour(const std::string &name, GameObject* gameObj);
		virtual ~SaltyBehaviour();

	public:
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
		bool					m_status;
		std::mutex				m_mutex;
	};
}

#endif // SALTYBEHAVIOR_HPP_
