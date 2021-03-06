//
// Created by gaspar_q on 11/26/16.
//

#include <Network/Socket/BasicSockStreamsContainer.hpp>
#include <algorithm>

/**
 * @brief Basic constructor
 */
Network::Socket::BasicSockStreamsContainer::BasicSockStreamsContainer()
{

}

/**
 * @brief Basic destructor
 */
Network::Socket::BasicSockStreamsContainer::~BasicSockStreamsContainer()
{
	while (!streams.empty())
	{
		ISockStreamHandler *s = streams.back();
		streams.pop_back();
		delete s;
	}
}

/**
 * @brief Allow any one to add a new user into the internal users to handle
 * @param toadd The new user to handle
 */
void Network::Socket::BasicSockStreamsContainer::Add(Network::Socket::ISockStreamHandler *toadd)
{
    streams.push_back(toadd);
}

/**
 * @brief Allow the user to remove a user into the internal list
 * @param torm The user to remove
 */
void Network::Socket::BasicSockStreamsContainer::Remove(Network::Socket::ISockStreamHandler *torm)
{
    for (std::list<Socket::ISockStreamHandler *>::iterator it = streams.begin(), end = streams.end(); it != end; ++it)
    {
        if (torm == *it)
        {
            streams.erase(it);
            return;
        }
    }
}

/**
 * @brief Allow the user to change the instance of the client handle by another client
 * @param old The old client to change
 * @param newone The new client instance with which change the old one
 */
void Network::Socket::BasicSockStreamsContainer::Move(Network::Socket::ISockStreamHandler *old,
                                                      Network::Socket::ISockStreamHandler *newone)
{
    for (ISockStreamHandler *&curr : streams)
    {
		if (curr == old)
		{
            delete curr;
			curr = newone;
			break;
		}
    }
}

/**
 * @brief Allow user to broadcast a message to all clients handled inside the container from a specific sender
 * @param tosnd The data to send
 * @param sender The sender from who send the data
 */
void Network::Socket::BasicSockStreamsContainer::Broadcast(Network::Core::NetBuffer &tosnd, Socket::ISockStream &sender)
{
    for (Socket::ISockStreamHandler *curr : streams)
    {
        sender.SendTo(tosnd, curr->getSocket());
    }
}

/**
 * @brief Allow user to get a reference on streams list internally handled
 * @return A reference on stream list
 */
std::list<Network::Socket::ISockStreamHandler *> &Network::Socket::BasicSockStreamsContainer::Streams()
{
    return streams;
}
