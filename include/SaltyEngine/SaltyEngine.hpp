#pragma once

#ifndef SALTYENGINE_HPP_
#define SALTYENGINE_HPP_

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <memory>
#include "SaltyEngine/DefaultRenderer.hpp"


#define DEFAULT_FRAME_RATE 60

namespace SaltyEngine
{
	enum EngineStatus
	{
		start,
		stop,
		pause
	};
	class Scene;
#define print_status(x) x

	class SaltyEngine
	{
	public:
		SaltyEngine();
		virtual ~SaltyEngine();

		void Start();
		void Stop();
		virtual void Run();
		EngineStatus GetStatus() const;
		bool LoadScene(size_t index);
		bool LoadScene(const std::string &name);
		void SetFrameRate(size_t fr);
		void operator<<(Scene *scene);
		long long GetDeltaTime() const;
		double GetFixedDeltaTime() const;
		void SetRenderer(IRenderer *renderer);

	/*public:
		static std::string const Tag[];*/

	private:
		void LoadAssets() noexcept;

	private:
		EngineStatus						m_status;
		std::vector<std::unique_ptr<Scene>>	m_scenes;
		size_t								m_current;
		std::chrono::nanoseconds			m_frame_rate;
		size_t								m_fps;
		std::chrono::duration<long long, std::nano> m_delta_time;
		IRenderer							*m_renderer;
	};
}

#include "SaltyEngine/Scene.hpp"

#endif // !SALTYENGINE_HPP_


