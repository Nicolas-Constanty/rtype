#pragma once

#ifndef SALTYBEHAVIOR_HPP_
#define SALTYBEHAVIOR_HPP_

#include <mutex>
#include <vector>
#include "SaltyEngine/Coroutine.hpp"
#include "SaltyEngine/Behaviour.hpp"
#include "ICollider.hpp"

namespace SaltyEngine
{
	class SaltyEngine;
#define WaitForSecond(x) coroutine::await(std::bind(&SaltyBehaviour::__Wait_For_Seconds, x))
#define WaitForMillisecond(x) coroutine::await(std::bind(&SaltyBehaviour::__Wait_For_Milliseconds, x))
#define WaitForMicrosecond(x) coroutine::await(std::bind(&SaltyBehaviour::__Wait_For_Microseconds, x))
#define StartCoroutine(x) m_coroutines.push_back(coroutine::create(std::bind(x, this)))

	class SaltyBehaviour : public Behaviour
	{
	public:
		// delete copy and move constructors and assign operators
		SaltyBehaviour(SaltyBehaviour const&) = delete;             // Copy construct
		SaltyBehaviour(SaltyBehaviour&&) = delete;                  // Move construct
		SaltyBehaviour& operator=(SaltyBehaviour const&) = delete;  // Copy assign
		SaltyBehaviour& operator=(SaltyBehaviour &&) = delete;      // Move assign
		explicit SaltyBehaviour(GameObject* gameObj);
		SaltyBehaviour(const std::string &name, GameObject* gameObj);
		virtual ~SaltyBehaviour();

	public:
		bool IsInit() const;
		void Init();

	protected:
		std::vector<coroutine::routine_t> m_coroutines;

	public:
		static void __Wait_For_Seconds(size_t time);
		static void __Wait_For_Milliseconds(size_t time);
		static void __Wait_For_Microseconds(size_t time);

		void CallCoroutines() const;

	public:
		virtual void Start() {};

		virtual void FixedUpdate() {};

		virtual void OnTriggerEnter(ICollider *) {};
		virtual void OnTriggerExit(ICollider *) {};
		virtual void OnTriggerStay(ICollider *) {};

		virtual void OnCollisionEnter(ICollider *) {};
		virtual void OnCollisionExit(ICollider *) {};
		virtual void OnCollisionStay(ICollider *) {};

		virtual void OnMouseEnter() {};
		virtual void OnMouseExit() {};
		virtual void OnMouseOver() {};

		virtual void Update() {};
		virtual void OnGui() {};
		virtual void OnDestroy() {};

	private:
		bool					m_status;
		std::mutex				m_mutex;
	};
}

#endif // SALTYBEHAVIOR_HPP_
