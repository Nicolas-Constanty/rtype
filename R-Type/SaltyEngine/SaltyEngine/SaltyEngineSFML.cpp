#include "SaltyEngineSFML.hpp"

namespace SaltyEngine
{
	SaltyEngineSFML::SaltyEngineSFML()
	{
	}


	SaltyEngineSFML::~SaltyEngineSFML()
	{
	}

	void SaltyEngineSFML::Run()
	{
		Start();
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		while (m_status != EngineStatus::stop)
		{
			if (m_status != EngineStatus::pause)
			{
				m_scenes[m_current]
			}
			else
			{

				while (mWindow.isOpen())
				{
					sf::Time elapsedTime = clock.restart();
					timeSinceLastUpdate += elapsedTime;
					while (timeSinceLastUpdate > TimePerFrame)
					{
						timeSinceLastUpdate -= TimePerFrame;

						processEvents();
						update(TimePerFrame);
					}

					updateStatistics(elapsedTime);
					render();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(PAUSE_FRAME_RATE));
			}
		}
	}
}


