#ifdef _WIN32
#include <direct.h>
#else
#include <X11/Xlib.h>
#include <dirent.h>
#include <SaltyEngine/Constants.hpp>
 #include <unistd.h>
#endif

#include <thread>
#include <list>
#include "SaltyEngine/SaltyEngine.hpp"
#include <SaltyEngine/Constants.hpp>
#include <SFML/System/Thread.hpp>
#include <SaltyEngine/ISceneLoader.hpp>
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
		while (m_status != EngineStatus::stop)
		{
			m_delta_time = std::chrono::high_resolution_clock::now() - time_start;
			time_start = std::chrono::high_resolution_clock::now();
			lag += std::chrono::duration_cast<std::chrono::nanoseconds>(m_delta_time);
			m_even_manager->Update();
			AScene *scene = m_scenes[m_current].get();
			scene->OnStart();
			scene->OnEnable();

			while (lag >= m_frame_rate)
			{
				lag -= m_frame_rate;
				if (!m_scenes.empty())
				{
					if (m_status != EngineStatus::pause)
					{
						scene->FixedUpdate();
						if (m_physics_handler)
						{
							m_physics_handler->Clear();
							m_physics_handler->Update();
							m_physics_handler->Collide();
						}

						scene->OnTriggerEnter();
						scene->OnTriggerExit();
						scene->OnTriggerStay();

						scene->OnCollisionEnter();
						scene->OnCollisionExit();
						scene->OnCollisionStay();
					}
					else
					{
						std::cout << "Game state : Paused" << std::endl;
					}
				}
				else
					std::cerr << "You run an empty game!" << std::endl;
			}
			
			scene->Update();
			if (m_physics_handler)
				m_physics_handler->Display();
			scene->CallCoroutines();
			scene->OnGui();
			scene->OnDisable();
			scene->OnDestroy();
			m_renderer->Display();
			scene->Destroy();
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
		{
			std::list<GameObject *> undeleted_obj = m_scenes[m_current]->CleanScene();
			m_current = index;
            for (GameObject *go : undeleted_obj)
                m_scenes[m_current]->m_objects.push_back(go);
            m_sceneLoader->LoadScene(m_scenes[m_current]->GetName());
            m_scenes[m_current]->SetScale(m_sceneLoader->GetSceneScale());
            for (std::pair<std::string, SaltyEngine::Vector2> it : m_sceneLoader->GetSceneObjects())
            {
                if (it.first == "GameManager") {
                    SaltyEngine::Vector2f pos = it.second;
                    SaltyEngine::Instantiate(it.first, pos, 0);
                }
            }
		}
		else
		{
			std::cerr << "Invalid scene index[" << index << "]!" << std::endl;
		}
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
        {
            return LoadScene(index);
        }
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
			throw std::runtime_error("No Scene was added");
		}
		return m_scenes[m_current].get();
	}

	IRenderer * Engine::GetRenderer(void) const
	{
		return m_renderer;
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

	void Engine::operator<<(AScene *scene)
	{
		if (scene != nullptr)
			m_scenes.push_back(std::unique_ptr<AScene>(scene));
		else
			throw new std::runtime_error("Can't push null scene");
	}

    void Engine::SetPhysicsHandler(APhysicsHandler *ph) {
        m_physics_handler = ph;
    }

    APhysicsHandler *Engine::GetPhysicsHandler(void) const {
        return m_physics_handler;
    }

	const Vector2ui &Engine::GetSize(void) const {
		if (m_physics_handler)
			return m_physics_handler->GetSize();
		return m_renderer->GetSize();
	}

	Input::IEventManager *Engine::GetEventManager() const {
        return m_even_manager;
    }

    void Engine::SetSceneLoader(ISceneLoader *sceneLoader)
    {
        m_sceneLoader = sceneLoader;
    }

    int Engine::GetArgc(void) const
    {
        return m_ac;
    }

    char const** Engine::GetArgv(void) const
    {
        return m_av;
    }

    void Engine::SetArguments(int ac, char const **av)
    {
        m_ac = ac;
        m_av = av;
    }
}
