#include "Rtype/Game/Client/GameClientObject.hpp"
#include "Rtype/Game/Client/GameManager.hpp"

Rtype::Game::Client::GameClientObject::GameClientObject(SaltyEngine::GameObject * const gamObj, const std::string &ip, const uint16_t port, const uint16_t secret) :
		SaltyBehaviour("GameClientObject", gamObj),
		m_port(port),
		m_ip(ip),
		m_secret(secret)
{
}

Rtype::Game::Client::GameClientObject::~GameClientObject()
{
    if (m_rtypeclient != nullptr)
	    delete(m_rtypeclient);
}

Rtype::Game::Client::GameClientObject::GameClientObject(const std::string & name, SaltyEngine::GameObject * const gamObj, const std::string &ip, const uint16_t port, const uint16_t secret)
	: SaltyBehaviour(name, gamObj), m_port(port), m_ip(ip), m_secret(secret)
{
}

void Rtype::Game::Client::GameClientObject::Start() {
	std::cout << "start gameClientObject: " << this << std::endl;
	
	m_rtypeclient = new Rtype::Game::Client::RtypeClientGameClient(m_dispatcher, m_secret);

	try
	{
		m_rtypeclient->Connect(m_ip, m_port);
        m_dispatcher.Watch(m_rtypeclient, Network::Core::NativeSocketIOOperationDispatcher::READ);
        m_dispatcher.setTimeout({0, 2});
	}
	catch (Network::Socket::SocketException const &err)
	{
		Debug::PrintError("Connect: " + std::string(err.what()));
	}
}

void Rtype::Game::Client::GameClientObject::Update()
{
	try
	{
		m_dispatcher.Poll();
	}
	catch (std::runtime_error const &)
	{
		SaltyEngine::Engine::Instance().Stop();
	}
}

SaltyEngine::Component *Rtype::Game::Client::GameClientObject::CloneComponent(SaltyEngine::GameObject *const obj)
{
	return new GameClientObject(obj, m_ip, m_port, m_secret);
}
