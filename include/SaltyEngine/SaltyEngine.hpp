#pragma once

#ifndef SALTYENGINE_HPP_
#define SALTYENGINE_HPP_

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <memory>
#include "SaltyEngine/DefaultRenderer.hpp"
#include "SaltyEngine/Input/DefaultEventManager.hpp"
#include "Common/Singleton.hpp"
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/IPhysicHandler.hpp"


#define DEFAULT_FRAME_RATE 60

namespace SaltyEngine
{
	class AScene;
#define print_status(x) x

	class LIB_EXPORT Engine : public Singleton<Engine>
	{
		friend class Singleton<Engine>;
	public:
		Engine();
		virtual ~Engine();

		void Start();
		void Stop();
		virtual void Run(void);
		EngineStatus GetStatus(void) const;
		bool LoadScene(size_t index);
		bool LoadScene(const std::string &name);
		void SetFrameRate(size_t fr);
		void operator<<(AScene *scene);
		double GetDeltaTime(void) const;
		double GetFixedDeltaTime(void) const;
        Input::IEventManager *GetEventManager() const;
		void SetRenderer(IRenderer *renderer);
		void SetEventManager(Input::IEventManager *ev_manager);
		void SetPhysicsHandler(APhysicsHandler *renderer);
		AScene *GetCurrentScene(void) const;
		IRenderer *GetRenderer(void) const;
		APhysicsHandler *GetPhysicsHandler(void) const;
		const Vector2ui &GetSize(void) const;

	private:
		EngineStatus								m_status;
		std::vector<std::unique_ptr<AScene>>		m_scenes;
		size_t										m_current;
		std::chrono::nanoseconds					m_frame_rate;
		size_t										m_fps;
		std::chrono::duration<long long, std::nano> m_delta_time;
		IRenderer									*m_renderer;
		Input::IEventManager						*m_even_manager;
        APhysicsHandler                             *m_physics_handler;
	};
}

template class Singleton<SaltyEngine::Engine>;

#endif // !SALTYENGINE_HPP_


