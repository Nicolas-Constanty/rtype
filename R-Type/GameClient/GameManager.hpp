#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Rtype/Game/Client/RtypeClientGameClient.hpp"
#include "Network/Core/NativeSocketIOOperationDispatcher.hpp"
#include "Rtype/Game/Client/GameClientObject.hpp"
#include "Rtype/Game/Client/GameClientObject.hpp"

class GameManager : public SaltyEngine::SaltyBehaviour
{
public:
	explicit GameManager(SaltyEngine::GameObject* const gamObj);
	GameManager(const std::string &name, SaltyEngine::GameObject* const gamObj);
	~GameManager();
	void Start();
	void Send();
private:
	Rtype::Game::Client::GameClientObject *m_network;
};

