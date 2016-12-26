#ifdef _WIN32
#include <direct.h>
#else
#include <X11/Xlib.h>
#include <dirent.h>
#include <SaltyEngine/Constants.hpp>
 #include <unistd.h>
#endif

#include "SaltyEngine/SaltyEngine.hpp"
#include <SaltyEngine/Constants.hpp>
#include <SFML/System/Thread.hpp>
#include <thread>
#include "SaltyEngine/AScene.hpp"
#include "Common/Debug.hpp"


namespace SaltyEngine
{
	/**
	 * @fn	SaltyEngine::SaltyEngine()
	 *
	 * @brief	Default constructor init m_fps at DEFAULT_FRAME_RATE.
	 */

	Engine::Engine(): m_current(0)
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		m_renderer = new DefaultRenderer();
		m_even_manager = new Input::DefaultEventManager();
        m_physics_handler = nullptr;
		m_status = EngineStatus::stop;
		m_fps = DEFAULT_FRAME_RATE;
		std::chrono::duration<double> d(1.0 / m_fps);
		m_frame_rate = std::chrono::duration_cast<std::chrono::nanoseconds>(d);
    }

	/**
	 * @fn	SaltyEngine::~SaltyEngine()
	 *
	 * @brief	Destructor.
	 */

	Engine::~Engine()
	{
		if (m_renderer)
			delete m_renderer;
		if (m_even_manager)
			delete m_even_manager;
		m_scenes.clear();
	}

	/**
	 * @fn	void SaltyEngine::Start()
	 *
	 * @brief	Starts this object.
	 */

	void Engine::Start()
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

	void Engine::Stop()
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

	void Engine::Run()
	{
		if (m_scenes.size() == 0)
		{
			Debug::PrintError("Cannot run without scene!");
			return;
		}
		Start();
		std::chrono::nanoseconds lag(0);
		std::chrono::time_point<std::chrono::high_resolution_clock> time_start = std::chrono::high_resolution_clock::now();
//		bool st = true;
		while (m_status != EngineStatus::stop)
		{
			m_delta_time = std::chrono::high_resolution_clock::now() - time_start;
			time_start = std::chrono::high_resolution_clock::now();
			lag += std::chrono::duration_cast<std::chrono::nanoseconds>(m_delta_time);
			m_even_manager->Update();
            m_scenes[m_current]->OnStart();
			m_scenes[m_current]->OnEnable();
			// Control Frame Rate
//			if (m_physics_handler)
//			{
//				XInitThreads();
//			}


			while (lag >= m_frame_rate)
			{
				lag -= m_frame_rate;
				if (!m_scenes.empty())
				{
					if (m_status != EngineStatus::pause)
					{
                        m_scenes[m_current]->FixedUpdate();
						//m_scenes[m_current]->UpdatePhysics();
						if (m_physics_handler)
						{
							m_physics_handler->Clear();
							m_physics_handler->Update();
							m_physics_handler->Collide();
						}

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
			if (m_physics_handler)
				m_physics_handler->Display();
			m_scenes[m_current]->CallCoroutines();
			m_scenes[m_current]->OnGui();
			m_scenes[m_current]->OnDestroy();
//			if (m_physics_handler && st)
//			{
//				std::cout << "pouet" << std::endl;
//				sf::Thread thread(&IPhysicsHandler::Run, m_physics_handler);
//				thread.launch();
//				st = false;
//			}
			m_renderer->Display();
			m_scenes[m_current]->Destroy();
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

	EngineStatus Engine::GetStatus(void) const
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

	bool Engine::LoadScene(size_t index)
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

	bool Engine::LoadScene(const std::string & name)
	{
		size_t index = 0;
		for (std::vector<std::unique_ptr<AScene>>::const_iterator it = m_scenes.begin(); it < m_scenes.end(); ++it)
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

	void Engine::SetFrameRate(size_t fr)
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

	double Engine::GetDeltaTime(void) const
	{
		double res = m_delta_time.count() / 1000000000.0;
		return res;
	}

	/**
	 * @fn	double SaltyEngine::GetFixedDeltaTime() const
	 *
	 * @brief	Gets fixed delta time.
	 *
	 * @return	The fixed delta time.
	 */

	double Engine::GetFixedDeltaTime(void) const
	{
		return (1.0 / m_fps);
	}

	void Engine::SetRenderer(IRenderer *renderer)
	{
		if (m_renderer && m_renderer != renderer)
		{
			delete m_renderer;
			m_renderer = renderer;
		}
	}

	void Engine::SetEventManager(Input::IEventManager * ev_manager)
	{
		if (m_even_manager && m_even_manager != ev_manager)
		{
			delete m_even_manager;
			m_even_manager = ev_manager;
		}
	}

	AScene * Engine::GetCurrentScene(void) const
	{
		if (m_scenes.empty()) {
			throw std::runtime_error("Not Scene was added");
		}
		return m_scenes[m_current].get();
	}

	IRenderer * Engine::GetRenderer(void) const
	{
		return m_renderer;
	}

//	/**
//	 * \brief Will load all the assets contained in the folder
//	 */
//	void SaltyEngine::LoadAssets() noexcept
//	{
//#if _WIN32
//		WIN32_FIND_DATA findFileData;
//		HANDLE hFind;
//		CHAR str[256];
//
//		_getcwd(str, sizeof(str));
//		hFind = FindFirstFile(std::string(std::string(str) + Asset::ASSET_PATH + "\\*").c_str(), &findFileData);
//
//		while (hFind != INVALID_HANDLE_VALUE)
//		{
//			std::string assetName = std::string(findFileData.cFileName);
//			if (assetName.length() >= Asset::LIB_EXTENSION.length()
//				&& assetName.compare(assetName.length() - Asset::LIB_EXTENSION.length(), Asset::LIB_EXTENSION.length(), Asset::LIB_EXTENSION) == 0)
//			{
//				std::cout << "Loading asset [" << assetName << "]" << std::endl;
//				std::string assetPath = std::string(str) + Asset::ASSET_PATH + "\\" + assetName;
//				Factory::LoadAsset(assetPath);
//			}
//			if (FindNextFile(hFind, &findFileData) == FALSE)
//				break;
//		}
//		FindClose(hFind);
//#else
//		DIR *dir;
//		struct dirent *ent;
//        char str[256];
//
//        getcwd(str, sizeof(str));
//
//		if ((dir = opendir(std::string(std::string(str) + Asset::ASSET_PATH).c_str())) != NULL)
//		{
//			/* get all the files and directories within directory */
//			while ((ent = readdir(dir)) != NULL)
//			{
//                std::string assetName = std::string(ent->d_name);
//                if (assetName.length() >= Asset::LIB_EXTENSION.length()
//                    && assetName.compare(assetName.length() - Asset::LIB_EXTENSION.length(), Asset::LIB_EXTENSION.length(), Asset::LIB_EXTENSION) == 0)
//                {
//                    std::cout << "Loading asset [" << assetName << "]" << std::endl;
//                    std::string assetPath = std::string(str) + Asset::ASSET_PATH + "/" + assetName;
//                    Factory::LoadAsset(assetPath);
//                }
//			}
//			closedir(dir);
//		}
//		else
//		{
//			/* could not open directory */
//			perror("");
//		}
//#endif
//	}

	/**
	 * @fn	void SaltyEngine::operator<<(Scene *scene)
	 *
	 * @brief	Bitwise left shift operator.
	 *
	 * @exception	std	Thrown when a Standard error condition occurs.
	 *
	 * @param [in,out]	scene	If non-null, the scene.
	 */

	void Engine::operator<<(AScene *scene)
	{
		if (scene != nullptr)
			m_scenes.push_back(std::unique_ptr<AScene>(scene));
		else
			throw new std::runtime_error("Can't push null scene");
	}

    void Engine::SetPhysicsHandler(IPhysicsHandler *ph) {
        m_physics_handler = ph;
    }

    IPhysicsHandler *Engine::GetPhysicsHandler(void) const {
        return m_physics_handler;
    }
}
