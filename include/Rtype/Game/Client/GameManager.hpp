#pragma once

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
//#include "Rtype/Game/Client/RtypeClientGameClient.hpp"
#include "Network/Core/NativeSocketIOOperationDispatcher.hpp"
#include "Rtype/Game/Common/GameObjectContainer.hpp"
#include "Rtype/Game/Client/GameClientObject.hpp"
#include <Rtype/Game/Server/GameServerObject.hpp>

#define SCREEN_X 1280

class PREF_EXPORT GameManager : public SaltyEngine::SaltyBehaviour
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
	void		PlaySound(std::string const &sound, bool loop = true);

public:
	template <typename Pack, typename Send, typename ... Args>
    void SendPackage(Send send1, Args ... args)
    {
//		messages.push(std::bind([send1, this](Args ... arguments){
//				if (m_client)
//					m_client->SendPackage<Pack>(send1, arguments...);
//			}, args...));
		if (m_client)
			m_client->SendPackage<Pack>(send1, args...);
    }

	template <typename Package, typename SendFunc, typename ... Args>
	void BroadCastPackage(SendFunc func, Args ... args)
	{
//		messages.push(std::bind([func, this](Args ... arguments){
//				if (m_server)
//					m_server->BroadCastPackage<Package>(func, arguments...);
//				else if (m_client)
//					m_client->BroadCastPackage<Package>(func, arguments...);
//			}, args...));
		if (m_server)
			m_server->BroadCastPackage<Package>(func, args...);
		else if (m_client)
			m_client->BroadCastPackage<Package>(func, args...);
	}

public:
    bool isServerSide() const;

public:
	void addPlayer(SaltyEngine::GameObject *player, unsigned char playerID);
	std::map<unsigned char, SaltyEngine::GameObject *> const &getPlayers() const;
	SaltyEngine::GameObject	*GetPlayer(unsigned char playerID) const;
	unsigned char	GetPlayerID(SaltyEngine::GameObject *player) const;

	bool IsAllPlayerDeath() const;
	void StartTheGame();

public:
	void addPod(SaltyEngine::GameObject *pod);
	std::list<SaltyEngine::GameObject*> const &getPods() const;

private:
    void OnSendHighScore();

private:
    bool IsSceneEmpty() const;

private:
	Rtype::Game::Server::GameServerObject *m_server;
	Rtype::Game::Client::GameClientObject *m_client;
    std::map<unsigned char, SaltyEngine::GameObject*> m_players;
	std::list<SaltyEngine::GameObject*> m_pods;

public:
	GameObjectContainer				gameObjectContainer;

private:
	SaltyEngine::SceneDefault	*monsterMap;
	double currentPosition = SCREEN_X;
	int velocity = 8;
    bool endOfGame = false;
    std::unique_ptr<GameOver> gameOver;
    int     canSend = 0;

private:
	std::queue<std::function<void()> >	messages;
	float	elapseTime;
	SaltyEngine::Sound::ISound *m_backgroudnSound = NULL;

};

