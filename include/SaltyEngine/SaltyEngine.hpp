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


#define DEFAULT_FRAME_RATE 60

namespace SaltyEngine
{
	enum EngineStatus
	{
		start,
		stop,
		pause
	};
	class AScene;
#define print_status(x) x

	class SaltyEngine : public Singleton<SaltyEngine>
	{
		friend class Singleton<SaltyEngine>;
	public:
		SaltyEngine();
		virtual ~SaltyEngine();

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
		void SetRenderer(IRenderer *renderer);
		void SetEventManager(Input::IEventManager *ev_manager);
		AScene *GetCurrentScene(void) const;
		IRenderer *GetRenderer(void) const;

	/*public:
		static std::string const Tag[];*/

	private:
		void LoadAssets() noexcept;

	private:
		EngineStatus								m_status;
		std::vector<std::unique_ptr<AScene>>		m_scenes;
		size_t										m_current;
		std::chrono::nanoseconds					m_frame_rate;
		size_t										m_fps;
		std::chrono::duration<long long, std::nano> m_delta_time;
		IRenderer									*m_renderer;
		Input::IEventManager						*m_even_manager;
	};
}

template class Singleton<SaltyEngine::SaltyEngine>;

#include "SaltyEngine/AScene.hpp"

#endif // !SALTYENGINE_HPP_


