#ifdef _WIN32
#include <direct.h>
#else
#include <dirent.h>
#include <SaltyEngine/Constants.hpp>
#include <zconf.h>

#endif

#include "SaltyEngine/SaltyEngine.hpp"
#include <SaltyEngine/Constants.hpp>

namespace SaltyEngine
{
	/**
	 * @fn	SaltyEngine::SaltyEngine()
	 *
	 * @brief	Default constructor init m_fps at DEFAULT_FRAME_RATE.
	 */

	SaltyEngine::SaltyEngine(): m_current(0)
	{
		m_renderer = new DefaultRenderer();
		m_status = EngineStatus::stop;
		m_fps = DEFAULT_FRAME_RATE;
		std::chrono::duration<double> d(1.0 / m_fps);
		m_frame_rate = std::chrono::duration_cast<std::chrono::nanoseconds>(d);
		LoadAssets();
	}

	/**
	 * @fn	SaltyEngine::~SaltyEngine()
	 *
	 * @brief	Destructor.
	 */

	SaltyEngine::~SaltyEngine()
	{
	}

	/**
	 * @fn	void SaltyEngine::Start()
	 *
	 * @brief	Starts this object.
	 */

	void SaltyEngine::Start()
	{
		m_status = EngineStatus::start;
	}

	/**
	 * @fn	void SaltyEngine::Stop()
	 *
	 * @brief	Stops this object.
	 *
	 * @author	Nicol
	 * @date	20/11/2016
	 */

	void SaltyEngine::Stop()
	{
		m_status = EngineStatus::stop;
	}

	/**
	 * @fn	void SaltyEngine::Run()
	 *
	 * @brief	Runs this object.
	 *
	 * @author	Nicol
	 * @date	20/11/2016
	 */

	void SaltyEngine::Run()
	{
		Start();
		std::chrono::nanoseconds lag(0);
		std::chrono::time_point<std::chrono::high_resolution_clock> time_start = std::chrono::high_resolution_clock::now();

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
			m_scenes[m_current]->OnDestroy();
			m_renderer->Display();
		}
	}

	/**
	 * @fn	EngineStatus SaltyEngine::GetStatus() const
	 *
	 * @brief	Gets the status.
	 *
	 * @author	Nicol
	 * @date	20/11/2016
	 *
	 * @return	The status.
	 */

	EngineStatus SaltyEngine::GetStatus() const
	{
		return m_status;
	}

	/**
	 * @fn	bool SaltyEngine::LoadScene(size_t index)
	 *
	 * @brief	Loads a scene.
	 *
	 * @author	Nicol
	 * @date	20/11/2016
	 *
	 * @param	index	Zero-based index of the.
	 *
	 * @return	True if it succeeds, false if it fails.
	 */

	bool SaltyEngine::LoadScene(size_t index)
	{
		if (index < m_scenes.size())
			m_current = index;
		else
			std::cerr << "Invalid scene index[" << index << "]!" << std::endl;
		return (index < m_scenes.size());
	}

	/**
	 * @fn	bool SaltyEngine::LoadScene(const std::string & name)
	 *
	 * @brief	Loads a scene.
	 *
	 * @author	Nicol
	 * @date	20/11/2016
	 *
	 * @param	name	The name.
	 *
	 * @return	True if it succeeds, false if it fails.
	 */

	bool SaltyEngine::LoadScene(const std::string & name)
	{
		size_t index = 0;
		for (std::vector<std::unique_ptr<Scene>>::const_iterator it = m_scenes.begin(); it < m_scenes.end(); ++it)
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

	/**
	 * @fn	void SaltyEngine::SetFrameRate(size_t fr)
	 *
	 * @brief	Sets frame rate.
	 *
	 * @param	fr	The fr.
	 */

	void SaltyEngine::SetFrameRate(size_t fr)
	{
		m_fps = fr;
		std::chrono::duration<double> d(1.0 / m_fps);
		m_frame_rate = std::chrono::duration_cast<std::chrono::nanoseconds>(d);
	}

	/**
	 * @fn	long long SaltyEngine::GetDeltaTime() const
	 *
	 * @brief	Gets delta time.
	 *
	 * @return	The delta time.
	 */

	long long SaltyEngine::GetDeltaTime() const
	{
		return m_delta_time.count();
	}

	/**
	 * @fn	double SaltyEngine::GetFixedDeltaTime() const
	 *
	 * @brief	Gets fixed delta time.
	 *
	 * @return	The fixed delta time.
	 */

	double SaltyEngine::GetFixedDeltaTime() const
	{
		return (1.0 / m_fps);
	}

	void SaltyEngine::SetRenderer(IRenderer *renderer)
	{
		if (m_renderer)
			delete m_renderer;
		m_renderer = renderer;
	}

	/**
	 * \brief Will load all the assets contained in the folder
	 */
	void SaltyEngine::LoadAssets() noexcept
	{
#if _WIN32
		WIN32_FIND_DATA findFileData;
		HANDLE hFind;
		CHAR str[256];

		_getcwd(str, sizeof(str));

		hFind = FindFirstFile(std::string(std::string(str) + "\\*").c_str(), &findFileData);

		while (hFind != INVALID_HANDLE_VALUE)
		{
			std::string assetName = std::string(findFileData.cFileName);
			if (assetName.length() >= Asset::LIB_EXTENSION.length()
				&& assetName.compare(assetName.length() - Asset::LIB_EXTENSION.length(), Asset::LIB_EXTENSION.length(), Asset::LIB_EXTENSION) == 0)
			{
				std::cout << "Loading asset [" << assetName << "]" << std::endl;
				std::string assetPath = std::string(str) + "/" + assetName;
				Factory::LoadAsset(assetPath);
			}
			if (FindNextFile(hFind, &findFileData) == FALSE)
				break;
		}
		FindClose(hFind);
#else
		DIR *dir;
		struct dirent *ent;
        char str[256];

        getcwd(str, sizeof(str));

		if ((dir = opendir(Asset::ASSET_PATH.c_str())) != NULL)
		{
			/* get all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL)
			{
                std::string assetName = std::string(ent->d_name);
                if (assetName.length() >= Asset::LIB_EXTENSION.length()
                    && assetName.compare(assetName.length() - Asset::LIB_EXTENSION.length(), Asset::LIB_EXTENSION.length(), Asset::LIB_EXTENSION) == 0)
                {
                    std::cout << "Loading asset [" << assetName << "]" << std::endl;
                    std::string assetPath = std::string(str) + "/" + assetName;
                    Factory::LoadAsset(assetPath);
                }
			}
			closedir(dir);
		}
		else
		{
			/* could not open directory */
			perror("");
		}
#endif
	}

	/**
	 * @fn	void SaltyEngine::operator<<(Scene *scene)
	 *
	 * @brief	Bitwise left shift operator.
	 *
	 * @exception	std	Thrown when a Standard error condition occurs.
	 *
	 * @param [in,out]	scene	If non-null, the scene.
	 */

	void SaltyEngine::operator<<(Scene *scene)
	{
		if (scene != nullptr)
			m_scenes.push_back(std::unique_ptr<Scene>(scene));
		else
			throw new std::runtime_error("Can't push null scene");
	}
}
