#pragma once

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
//#include "Rtype/Game/Client/RtypeClientGameClient.hpp"
#include "Network/Core/NativeSocketIOOperationDispatcher.hpp"
#include "Rtype/Game/Common/GameObjectContainer.hpp"
#include "Rtype/Game/Client/GameClientObject.hpp"
#include <Rtype/Game/Server/GameServerObject.hpp>

#define SCREEN_X 1280

class GameManager : public SaltyEngine::SaltyBehaviour
{
public:
	explicit GameManager(SaltyEngine::GameObject* const gamObj);
	GameManager(const std::string &name, SaltyEngine::GameObject* const gamObj);
	~GameManager();

public:
	void Start();
	void FixedUpdate();
    void OnCollisionExit(SaltyEngine::ICollider *collider);
    void OnCollisionEnter(SaltyEngine::ICollider *collider);

public:
	template <typename Pack, typename Send, typename ... Args>
    void SendPackage(Send send1, Args ... args)
    {
		if (m_client)
        	m_client->SendPackage<Pack>(send1, args...);
    }

	template <typename Package, typename SendFunc, typename ... Args>
	void BroadCastPackage(SendFunc func, Args ... args)
	{
		if (m_server)
            m_server->BroadCastPackage<Package>(func, args...);
		else if (m_client)
			m_client->BroadCastPackage<Package>(func, args...);
	}

public:
    bool isServerSide() const;

public:
	void addPlayer(SaltyEngine::GameObject *player);
	std::list<SaltyEngine::GameObject *> const &getPlayers() const;

	void OnPlayerDeath();
	void StartTheGame();

public:
	void addPod(SaltyEngine::GameObject *pod);
	std::list<SaltyEngine::GameObject*> const &getPods() const;

private:
    void OnSendHighScore();

private:
	Rtype::Game::Server::GameServerObject *m_server;
	Rtype::Game::Client::GameClientObject *m_client;
    std::list<SaltyEngine::GameObject*> m_players;
	std::list<SaltyEngine::GameObject*> m_pods;

public:
	GameObjectContainer				gameObjectContainer;

private:
	std::unique_ptr<SaltyEngine::SceneDefault>   monsterMap;
	double currentPosition = SCREEN_X;
	int velocity = 8;
    bool endOfGame = false;
    GameOver *gameOver;
    int     canSend = 0;
};

