#include "SaltyGame.hpp"

namespace SaltyEngine
{
	// 16 ms for 60fps
	SaltyGame::SaltyGame()
	{
		m_status = EngineStatus::stop;
		m_fps = DEFAULT_FRAME_RATE;
		std::chrono::duration<double> d(1.0 / m_fps);
		m_frame_rate = std::chrono::duration_cast<std::chrono::nanoseconds>(d);
	}


	SaltyGame::~SaltyGame()
	{
	}

	void SaltyGame::Start()
	{
		m_status = EngineStatus::start;
	}

	void SaltyGame::Stop()
	{
		m_status = EngineStatus::stop;
	}

	void SaltyGame::Run()
	{
		Start();
		std::chrono::nanoseconds lag(0);
		std::chrono::time_point<std::chrono::steady_clock> time_start = std::chrono::high_resolution_clock::now();

		while (m_status != EngineStatus::stop)
		{
			m_delta_time = std::chrono::high_resolution_clock::now() - time_start;
			time_start = std::chrono::high_resolution_clock::now();
			lag += std::chrono::duration_cast<std::chrono::nanoseconds>(m_delta_time);
			// Control Frame Rate
			while (lag >= m_frame_rate)
			{
				//std::cout << "FixedUpdate" << std::endl;
				lag -= m_frame_rate;
				if (!m_scenes.empty())
				{
					
					if (m_status != EngineStatus::pause)
					{
						m_scenes[m_current]->OnStart();

						m_scenes[m_current]->FixedUpdate();

						m_scenes[m_current]->OnTriggerEnter();
						m_scenes[m_current]->OnTriggerExit();
						m_scenes[m_current]->OnTriggerStay();

						m_scenes[m_current]->OnCollisionEnter();
						m_scenes[m_current]->OnCollisionExit();
						m_scenes[m_current]->OnCollisionStay();

						m_scenes[m_current]->OnMouseEnter();
						m_scenes[m_current]->OnMouseExit();
						m_scenes[m_current]->OnMouseOver();
					}
					else
					{
						std::cout << "Game state : Paused" << std::endl;
					}
				}
				else
					std::cerr << "You run an empty game!" << std::endl;
			}
			
			m_scenes[m_current]->Update();
			m_scenes[m_current]->CallCoroutines();
			m_scenes[m_current]->OnGui();
		}
	}

	EngineStatus SaltyGame::GetStatus() const
	{
		return m_status;
	}
	bool SaltyGame::LoadScene(size_t index)
	{
		if (index < m_scenes.size())
			m_current = index;
		else
			std::cerr << "Invalid scene index[" << index << "]!" << std::endl;
		return (index < m_scenes.size());
	}
	bool SaltyGame::LoadScene(const std::string & name)
	{
		size_t index = 0;
		for (std::vector<std::unique_ptr<Scene>>::const_iterator it = m_scenes.begin(); it < m_scenes.end(); it++)
		{
			if ((*it)->GetName() == name)
				break;
			++index;
		}
		if (index < m_scenes.size())
			return (true);
		else
			std::cerr << "Invalid scene index[" << index << "]!" << std::endl;
		return (index < m_scenes.size());
	}
	void SaltyGame::SetFrameRate(size_t fr)
	{
		m_fps = fr;
		std::chrono::duration<double> d(1.0 / m_fps);
		m_frame_rate = std::chrono::duration_cast<std::chrono::nanoseconds>(d);
	}
	void SaltyGame::operator<<(Scene *scene)
	{
		m_scenes.push_back(std::unique_ptr<Scene>(scene));
	}
	long long SaltyGame::DeltaTime() const
	{
		return m_delta_time.count();
	}
	double SaltyGame::FixedDeltaTime() const
	{
		return (1.0 / m_fps);
	}
}