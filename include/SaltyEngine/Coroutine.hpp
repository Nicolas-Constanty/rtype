/*
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements. See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership. The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License. You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied. See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#ifndef STDEX_COROUTINE_H_
#define STDEX_COROUTINE_H_

#ifndef STACK_LIMIT
#define STACK_LIMIT (1024*1024)
#endif

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cassert>

#include <string>
#include <vector>
#include <list>
#include <thread>
#include <future>

using std::string;
using std::wstring;

#ifdef _MSC_VER
#include <Windows.h>
#else
#if __APPLE__ && __MACH__
#include <sys/ucontext.h>
#else
#include <ucontext.h>
#endif
#endif

#include "Common/Singleton.hpp"

namespace coroutine {

	typedef size_t routine_t;

#ifdef _MSC_VER

	struct Routine
	{
		std::function<void()> func;
		bool finished;
		LPVOID fiber;

		Routine(std::function<void()> f)
		{
			func = f;
			finished = false;
			fiber = nullptr;
		}

		~Routine()
		{
			DeleteFiber(fiber);
		}
	};

	struct Ordinator
	{
		std::vector<Routine *> routines;
		std::list<routine_t> indexes;
		routine_t current;
		size_t stack_size;
		LPVOID fiber;

		Ordinator(size_t ss = STACK_LIMIT)
		{
			current = 0;
			stack_size = ss;
			fiber = ConvertThreadToFiber(nullptr);
		}

		~Ordinator()
		{
			for (auto &routine : routines)
				delete routine;
		}
	};

	//thread_local  static  Singleton<Ordinator> Singleton<Ordinator>::Instance();

	inline routine_t create(std::function<void()> f)
	{
		Routine *routine = new Routine(f);

		if (Singleton<Ordinator>::Instance().indexes.empty())
		{
			Singleton<Ordinator>::Instance().routines.push_back(routine);
			return Singleton<Ordinator>::Instance().routines.size();
		}
		else
		{
			routine_t id = Singleton<Ordinator>::Instance().indexes.front();
			Singleton<Ordinator>::Instance().indexes.pop_front();
			assert(Singleton<Ordinator>::Instance().routines[id - 1] == nullptr);
			Singleton<Ordinator>::Instance().routines[id - 1] = routine;
			return id;
		}
	}

	inline void destroy(routine_t id)
	{
		Routine *routine = Singleton<Ordinator>::Instance().routines[id - 1];
		assert(routine != nullptr);

		delete routine;
		Singleton<Ordinator>::Instance().routines[id - 1] = nullptr;
		Singleton<Ordinator>::Instance().indexes.push_back(id);
	}

	inline void __stdcall entry(LPVOID lpParameter)
	{
		routine_t id = Singleton<Ordinator>::Instance().current;
		Routine *routine = Singleton<Ordinator>::Instance().routines[id - 1];
		assert(routine != nullptr);

		routine->func();

		routine->finished = true;
		Singleton<Ordinator>::Instance().current = 0;

		SwitchToFiber(Singleton<Ordinator>::Instance().fiber);
	}

	inline int resume(routine_t id)
	{
		assert(Singleton<Ordinator>::Instance().current == 0);

		Routine *routine = Singleton<Ordinator>::Instance().routines[id - 1];
		if (routine == nullptr)
			return -1;

		if (routine->finished)
			return -2;

		if (routine->fiber == nullptr)
		{
			routine->fiber = CreateFiber(Singleton<Ordinator>::Instance().stack_size, entry, 0);
			Singleton<Ordinator>::Instance().current = id;
			SwitchToFiber(routine->fiber);
		}
		else
		{
			Singleton<Ordinator>::Instance().current = id;
			SwitchToFiber(routine->fiber);
		}

		return 0;
	}

	inline void yield()
	{
		routine_t id = Singleton<Ordinator>::Instance().current;
		Routine *routine = Singleton<Ordinator>::Instance().routines[id - 1];
		assert(routine != nullptr);

		Singleton<Ordinator>::Instance().current = 0;
		SwitchToFiber(Singleton<Ordinator>::Instance().fiber);
	}

#if 0
	template<typename Function>
	typename std::result_of<Function()>::type
		await(Function &&func)
	{
		auto future = std::async(std::launch::async, func);
		std::future_status status = future.wait_for(std::chrono::milliseconds(100));
		while (status == std::future_status::timeout)
		{
			if (Singleton<Ordinator>::Instance().current != 0)
				yield();
			status = future.wait_for(std::chrono::milliseconds(0));
		}
		return future.get();
	}
#endif

#if 1
	template<typename Function>
	std::result_of_t<std::decay_t<Function>()>
		await(Function &&func)
	{
		auto future = std::async(std::launch::async, func);
		std::future_status status = future.wait_for(std::chrono::milliseconds(100));

		while (status == std::future_status::timeout)
		{
			if (Singleton<Ordinator>::Instance().current != 0)
				yield();

			status = future.wait_for(std::chrono::milliseconds(0));
		}
		return future.get();
	}
#endif

#else

	struct Routine
	{
		std::function<void()> func;
		char *stack;
		bool finished;
		ucontext_t ctx;

		Routine(std::function<void()> f)
		{
			func = f;
			stack = nullptr;
			finished = false;
		}

		~Routine()
		{
			delete[] stack;
		}
	};

	struct Ordinator
	{
		std::vector<Routine *> routines;
		std::list<routine_t> indexes;
		routine_t current;
		size_t stack_size;
		ucontext_t ctx;

		inline Ordinator(size_t ss = STACK_LIMIT)
		{
			current = 0;
			stack_size = ss;
		}

		inline ~Ordinator()
		{
			for (auto &routine : routines)
				delete routine;
		}
	};

	thread_local static Ordinator Singleton<Ordinator>::Instance();

	inline routine_t create(std::function<void()> f)
	{
		Routine *routine = new Routine(f);

		if (Singleton<Ordinator>::Instance().indexes.empty())
		{
			Singleton<Ordinator>::Instance().routines.push_back(routine);
			return Singleton<Ordinator>::Instance().routines.size();
		}
		else
		{
			routine_t id = Singleton<Ordinator>::Instance().indexes.front();
			Singleton<Ordinator>::Instance().indexes.pop_front();
			assert(Singleton<Ordinator>::Instance().routines[id - 1] == nullptr);
			Singleton<Ordinator>::Instance().routines[id - 1] = routine;
			return id;
		}
	}

	inline void destroy(routine_t id)
	{
		Routine *routine = Singleton<Ordinator>::Instance().routines[id - 1];
		assert(routine != nullptr);

		delete routine;
		Singleton<Ordinator>::Instance().routines[id - 1] = nullptr;
	}

	inline void entry()
	{
		routine_t id = Singleton<Ordinator>::Instance().current;
		Routine *routine = Singleton<Ordinator>::Instance().routines[id - 1];
		routine->func();

		routine->finished = true;
		Singleton<Ordinator>::Instance().current = 0;
		Singleton<Ordinator>::Instance().indexes.push_back(id);
	}

	inline int resume(routine_t id)
	{
		assert(Singleton<Ordinator>::Instance().current == 0);

		Routine *routine = Singleton<Ordinator>::Instance().routines[id - 1];
		if (routine == nullptr)
			return -1;

		if (routine->finished)
			return -2;

		if (routine->stack == nullptr)
		{
			//initializes the structure to the currently active context.
			//When successful, getcontext() returns 0
			//On error, return -1 and set errno appropriately.
			getcontext(&routine->ctx);

			//Before invoking makecontext(), the caller must allocate a new stack
			//for this context and assign its address to ucp->uc_stack,
			//and define a successor context and assign its address to ucp->uc_link.
			routine->stack = new char[Singleton<Ordinator>::Instance().stack_size];
			routine->ctx.uc_stack.ss_sp = routine->stack;
			routine->ctx.uc_stack.ss_size = Singleton<Ordinator>::Instance().stack_size;
			routine->ctx.uc_link = &Singleton<Ordinator>::Instance().ctx;
			Singleton<Ordinator>::Instance().current = id;

			//When this context is later activated by swapcontext(), the function entry is called.
			//When this function returns, the  successor context is activated.
			//If the successor context pointer is NULL, the thread exits.
			makecontext(&routine->ctx, (void(*)(void))entry, 0);

			//The swapcontext() function saves the current context,
			//and then activates the context of another.
			swapcontext(&Singleton<Ordinator>::Instance().ctx, &routine->ctx);
		}
		else
		{
			Singleton<Ordinator>::Instance().current = id;
			swapcontext(&Singleton<Ordinator>::Instance().ctx, &routine->ctx);
		}

		return 0;
	}

	inline void yield()
	{
		routine_t id = Singleton<Ordinator>::Instance().current;
		Routine *routine = Singleton<Ordinator>::Instance().routines[id - 1];
		assert(routine != nullptr);

		char *stack_top = routine->stack + Singleton<Ordinator>::Instance().stack_size;
		char stack_bottom = 0;
		assert((size_t)(stack_top - &stack_bottom) <= Singleton<Ordinator>::Instance().stack_size);

		Singleton<Ordinator>::Instance().current = 0;
		swapcontext(&routine->ctx, &Singleton<Ordinator>::Instance().ctx);
	}

	routine_t current()
	{
		return Singleton<Ordinator>::Instance().current;
	}

	template<typename Function>
	typename std::result_of<Function()>::type
		await(Function &&func)
	{
		auto future = std::async(std::launch::async, func);
		std::future_status status = future.wait_for(std::chrono::milliseconds(100));

		while (status == std::future_status::timeout)
		{
			if (Singleton<Ordinator>::Instance().current != 0)
				yield();

			status = future.wait_for(std::chrono::milliseconds(0));
		}
		return future.get();
	}

#endif

	template<typename Type>
	class Channel
	{
	public:
		Channel()
		{
			_taker = 0;
		}

		Channel(routine_t id)
		{
			_taker = id;
		}

		void consumer(routine_t id)
		{
			_taker = id;
		}

		inline void push(const Type &obj)
		{
			_list.push_back(obj);
			if (_taker)
				resume(_taker);
		}

		inline void push(Type &&obj)
		{
			_list.push_back(std::move(obj));
			if (_taker)
				resume(_taker);
		}

		inline Type pop()
		{
			if (!_taker)
				_taker = current();

			while (_list.empty())
				yield();

			Type obj = std::move(_list.front());
			_list.pop_front();
			return std::move(obj);
		}

		void clear()
		{
			_list.clear();
		}

		inline size_t size()
		{
			return _list.size();
		}

		inline bool empty()
		{
			return _list.empty();
		}

	private:
		std::list<Type> _list;
		routine_t _taker;
	};

}
#endif //STDEX_COROUTINE_H_