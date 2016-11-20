#pragma once

#ifndef SALTYREFLECTION_HPP_
#define SALTYREFLECTION_HPP_

#include <mutex>
#include <iostream>
#include "SaltyObj.hpp"

static std::mutex m_mutex;

namespace SaltyEngine
{
	template<typename T>
	class SaltyReflection
	{
#define FUNC Start

#define PASTER(x,y) x ## y
#define EVALUATOR(x,y)  PASTER(x,y)
#define CONCAT(fun) EVALUATOR(fun, FUNC)

#define M_NAME "Start"
#define M_EXIST CONCAT(Exist)
#define M_EVAL CONCAT(Eval)
#define M_TYPE CONCAT(Type)
#define M_CALL CONCAT(Call)
	public:
		// Signature match
		template<typename A>
		static std::true_type M_EXIST(void (A::*)()) {
			return std::true_type();
		}

		// Check if the function Exist
		template <typename A>
		static decltype(M_EXIST(&A::FUNC)) M_EXIST(decltype(&A::FUNC), void *) {
			typedef decltype(M_EXIST(&A::FUNC)) return_type;
			return return_type();
		}

		// Signature doesn't match
		template<typename A>
		static std::false_type M_EXIST(...) {
			return std::false_type();
		}

		typedef decltype(M_EXIST<T>(0, 0)) M_TYPE;

		// If the function exist call her
		static void M_EVAL(T *t, std::true_type) {
			m_mutex.lock();
			if (!t->IsInit())
			{
				t->FUNC();
				t->Init();
			}
			m_mutex.unlock();
		}

		// If the function doesn't exist
		static void M_EVAL(...) {
			std::cout << typeid(T).name() << "::" << M_NAME << "() not called" << std::endl;
		}

		static void M_EVAL(T *t) {
			M_EVAL(t, M_TYPE());
		}

		// Call function with dynamic cast
		template<typename T, typename ...Rest>
		static void M_CALL(typelist<T, Rest...>, SaltyBehaviour *obj)
		{
			if (dynamic_cast<T *>(obj))
				SaltyReflection<T>::M_EVAL(static_cast<T *>(obj));
			else
				return M_CALL(typelist<Rest...>(), obj);
		}
		
		// Call function with dynamic cast
		template<typename T>
		static void M_CALL(typelist<T>, SaltyBehaviour *obj)
		{
			if (dynamic_cast<T *>(obj))
				SaltyReflection<T>::M_EVAL(static_cast<T *>(obj));
		}

#undef FUNC
#undef M_TYPE
#undef M_NAME
#undef M_EXIST
#undef M_EVAL

#include "Saltyreflection.inl"
	};
};

#endif // !SALTYREFLECTION_HPP_


