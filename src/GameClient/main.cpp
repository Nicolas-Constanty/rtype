#include <SaltyEngine/SaltyEngine.hpp>
#include <Rtype/Game/Client/RtypeClientGameClient.hpp>

int main()
{
	Network::Core::NativeSocketIOOperationDispatcher    dispatcher;
	Rtype::Game::Client::RtypeClientGameClient          client(dispatcher);

#if _WIN32
	Network::Socket::WinSocket::Start();
#endif
	client.Connect("10.10.252.172", 4242);
	dispatcher.Watch(client, Network::Core::NativeSocketIOOperationDispatcher::READ);
	dispatcher.Run();
#if _WIN32
	Network::Socket::WinSocket::Stop();
#endif
	return 0;
}