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
			class GameClientObject : public SaltyEngine::SaltyBehaviour
			{
			public:
				explicit GameClientObject(SaltyEngine::GameObject* const gamObj, const std::string &ip, const uint16_t port);
				GameClientObject(const std::string &name, SaltyEngine::GameObject* const gamObj, const std::string &ip, const uint16_t port);
				void Start();
				void Update();
				~GameClientObject();

				void SendInput(std::string const &name, float const value);

			private:
				uint16_t m_port;
				std::string m_ip;
				Client::RtypeClientGameClient *m_rtypeclient;
				Network::Core::NativeSocketIOOperationDispatcher m_dispatcher;
			};
		}
	}
}