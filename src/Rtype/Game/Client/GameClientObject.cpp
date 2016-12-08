#include "Rtype/Game/Client/GameClientObject.hpp"

Rtype::Game::Client::GameClientObject::GameClientObject(SaltyEngine::GameObject * const gamObj, const std::string &ip, const uint16_t port)
	: SaltyBehaviour("GameClientObject", gamObj), m_ip(ip), m_port(port)
{
}

Rtype::Game::Client::GameClientObject::GameClientObject(const std::string & name, SaltyEngine::GameObject * const gamObj, const std::string &ip, const uint16_t port)
	: SaltyBehaviour("GameClientObject", gamObj), m_ip(ip), m_port(port)
{
}

void Rtype::Game::Client::GameClientObject::Start()
{
	m_rtypeclient = new Rtype::Game::Client::RtypeClientGameClient(m_dispatcher);
	m_dispatcher.Watch(m_rtypeclient, Network::Core::NativeSocketIOOperationDispatcher::READ);
	m_dispatcher.setTimeout({0, 0});
}

void Rtype::Game::Client::GameClientObject::Update()
{
	m_dispatcher.Poll();
}

Rtype::Game::Client::GameClientObject::~GameClientObject()
{
}
