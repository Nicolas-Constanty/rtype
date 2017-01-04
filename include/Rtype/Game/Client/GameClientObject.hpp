#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Rtype/Game/Client/RtypeClientGameClient.hpp"
#include "Network/Core/NativeSocketIOOperationDispatcher.hpp"
#include "Protocol/Game/GamePackageFactory.hpp"

namespace Rtype
{
	namespace Game
	{
		namespace Client
		{
			class PREF_EXPORT GameClientObject : public SaltyEngine::SaltyBehaviour
			{
			public:
				explicit GameClientObject(SaltyEngine::GameObject* const gamObj, const std::string &ip, const uint16_t port, const uint16_t secret);
				GameClientObject(const std::string &name, SaltyEngine::GameObject* const gamObj, const std::string &ip, const uint16_t port, const uint16_t secret);
				void Start();
				void Update();
				~GameClientObject();

			public:
				template <typename Pack, typename Send, typename ... Args>
				void SendPackage(Send send1, Args ... args)
				{
					m_rtypeclient->SendPackage<Pack>(send1, args...);
				}

				template <typename Package, typename SendFunc, typename ... Args>
				void BroadCastPackage(SendFunc func, Args ... args)
				{
					m_rtypeclient->BroadCastPackage<Package>(func, args...);
				}

				Client::RtypeClientGameClient *GetClient() const {
					return m_rtypeclient;
				}

				SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject *const obj) override;

			private:
				uint16_t m_port;
				std::string m_ip;
                const uint32_t m_secret;
				Client::RtypeClientGameClient *m_rtypeclient = nullptr;
				Network::Core::NativeSocketIOOperationDispatcher m_dispatcher;
			};
		}
	}
}