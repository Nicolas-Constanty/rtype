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
#include "SaltyEngine/APhysicsHandler.hpp"
#include "ISceneLoader.hpp"


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

		virtual void Start();
		virtual void Stop();
		virtual void Run(void);
		virtual EngineStatus GetStatus(void) const;
//		virtual bool LoadScene(size_t index);
		virtual bool LoadScene(const std::string &name);
		virtual void SetFrameRate(size_t fr);
		virtual void operator<<(AScene *scene);
		virtual double GetDeltaTime(void) const;
		virtual double GetFixedDeltaTime(void) const;
        virtual Input::IEventManager *GetEventManager() const;
		virtual void SetRenderer(IRenderer *renderer);
		virtual void SetEventManager(Input::IEventManager *ev_manager);
		virtual void SetPhysicsHandler(APhysicsHandler *renderer);
		virtual AScene *GetCurrentScene(void) const;
		virtual IRenderer *GetRenderer(void) const;
		virtual APhysicsHandler *GetPhysicsHandler(void) const;
		virtual const Vector2ui &GetSize(void) const;
        virtual void SetSceneLoader(ISceneLoader *sceneLoader);

        int GetArgc(void) const;
        char const** GetArgv(void) const;
        void SetArguments(int ac, char const**av);
		AScene *GetSceneByName(const std::string &name);
		void SetCurrentScene(AScene *scene);

	protected:
		EngineStatus								m_status;
		std::vector<std::unique_ptr<AScene>>		m_scenes;
		AScene										*m_current;
		std::chrono::nanoseconds					m_frame_rate;
		size_t										m_fps;
		std::chrono::duration<long long, std::nano> m_delta_time;
		IRenderer									*m_renderer;
		Input::IEventManager						*m_even_manager;
        APhysicsHandler                             *m_physics_handler;
        std::list<GameObject *>                     m_undeleted_object;
        std::string                                 m_current_name;


    private:
        ISceneLoader        *m_sceneLoader = nullptr;
		char 				const**m_av = nullptr;
		int 				m_ac = 0;
        void                __LoadScene();
    };
}

template<>
SaltyEngine::Engine &Singleton<SaltyEngine::Engine>::Instance();

#endif // !SALTYENGINE_HPP_


