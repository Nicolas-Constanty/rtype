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

	Engine::Engine(): m_current(nullptr)
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		m_renderer = nullptr;
		m_even_manager = nullptr;
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
        __LoadScene();
		if (m_scenes.size() == 0)
		{
			Debug::PrintError("Cannot run without scene!");
			return;
		}
        if (m_even_manager == nullptr)
        {
            Debug::PrintError("Set event manager before Run!");
            return;
        }
        if (m_renderer == nullptr)
        {
            Debug::PrintError("Set renderer before Run!");
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
			m_current->OnStart();
            m_current->OnEnable();

			while (lag >= m_frame_rate)
			{
				lag -= m_frame_rate;
				if (!m_scenes.empty())
				{
					if (m_status != EngineStatus::pause)
					{
                        m_current->FixedUpdate();
						if (m_physics_handler)
						{
							m_physics_handler->Clear();
							m_physics_handler->Update();
							m_physics_handler->Collide();
						}

                        m_current->OnTriggerEnter();
                        m_current->OnTriggerExit();
                        m_current->OnTriggerStay();

                        m_current->OnCollisionEnter();
                        m_current->OnCollisionExit();
                        m_current->OnCollisionStay();
					}
					else
					{
						std::cout << "Game state : Paused" << std::endl;
					}
				}
				else
					std::cerr << "You run an empty game!" << std::endl;
			}

            m_current->Update();
			if (m_physics_handler)
				m_physics_handler->Display();
            m_current->CallCoroutines();
            m_current->OnGui();
            m_current->OnDisable();
            m_current->OnDestroy();
			m_renderer->Display();
            m_current->Destroy();
            __LoadScene();
		}
	}

	AScene *Engine::GetSceneByName(const std::string &name)
	{
		for (std::vector<std::unique_ptr<AScene>>::const_iterator scene = m_scenes.begin(); scene != m_scenes.end(); ++scene) {
			if ((*scene)->GetName() == name)
				return scene->get();
		}
		return nullptr;
	}

    void Engine::SetCurrentScene(AScene *scene)
    {
        if (!scene)
        {
            Debug::PrintWarning("Cannot add null scene");
            return;
        }
        m_current = scene;
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
        if (m_current) {
            m_undeleted_object = m_current->CleanScene();
        }
        if (m_current_name.empty())
        {
            m_current_name = name;
        }
        return (m_current != nullptr);
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
			delete m_renderer;
        m_renderer = renderer;
	}

	void Engine::SetEventManager(Input::IEventManager * ev_manager)
	{
		if (m_even_manager && m_even_manager != ev_manager)
			delete m_even_manager;
        m_even_manager = ev_manager;
	}

	AScene * Engine::GetCurrentScene(void) const
	{
		if (m_scenes.empty()) {
			throw std::runtime_error("No Scene was added");
		}
		return m_current;
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
		{
			m_scenes.push_back(std::unique_ptr<AScene>(scene));
			if (!m_current)
				m_current = scene;
		}
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

    void Engine::__LoadScene() {
        if (!m_current_name.empty())
        {
            m_current = m_sceneLoader->LoadScene(m_current_name);
            for (GameObject *go : m_undeleted_object)
                m_current->m_objects.push_back(go);
            m_undeleted_object.clear();
            m_current_name = "";
        }
    }

    ISceneLoader *Engine::GetSceneLoader() const {
        return m_sceneLoader;
    }
}
