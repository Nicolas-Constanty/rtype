//
// Created by gaspar_q on 11/10/16.
//

#include <csignal>

#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>
#include <algorithm>
#include <stack>
#include <iomanip>


#if _WIN32
#include <winsock2.h>
#else
#include <poll.h>
#include <unistd.h>
#endif


/**
 * \brief A Boolean variable used in <Run> method as conditional for the infinite server loop. Eq false on Crtl+C
 */
static bool running = true;

/**
 * @brief Constant IOOperation definition of read. Sets the good pointers on member and name
 */
const Network::Core::NativeSocketIOOperationDispatcher::IOOperation  Network::Core::NativeSocketIOOperationDispatcher::read = {
        &NativeSocketIOOperationDispatcher::m_readWatch,
        &Socket::ISockStreamHandler::OnAllowedToRead,
        &Socket::ISockStreamHandler::OnReadCheck
};

/**
 * @brief Constant IOOperation definition of write. Sets the good pointers on member and name
 */
const Network::Core::NativeSocketIOOperationDispatcher::IOOperation Network::Core::NativeSocketIOOperationDispatcher::write = {
        &NativeSocketIOOperationDispatcher::m_writeWatch,
        &Socket::ISockStreamHandler::OnAllowedToWrite,
        &Socket::ISockStreamHandler::OnWriteCheck
};

/**
 * \brief Function that catches the sigint signal in order to properly stop the server
 */
void breakCatch(int)
{
    if (running)
        running = false;
    else
        exit(1);
}

/**
 * \brief Basic constructor of NativeSocketIOOperationDispatcher
 * \param timeout Corresponds to the native <select> function timeout
 */
Network::Core::NativeSocketIOOperationDispatcher::NativeSocketIOOperationDispatcher(struct timeval const &timeout) :
    m_timeout(new struct timeval(timeout))
{

}

/**
 * \brief Secundary constructor
 * \param timeout through pointer in order to pass NULL for infinite timeout
 */
Network::Core::NativeSocketIOOperationDispatcher::NativeSocketIOOperationDispatcher(timeval *timeout) :
    m_timeout(timeout)
{

}

/**
 * \brief Desctructor that does nothing
 */
Network::Core::NativeSocketIOOperationDispatcher::~NativeSocketIOOperationDispatcher()
{

}

/**
 * \brief Function that will check if fd to watch can read data through usage of <select>
 */
void Network::Core::NativeSocketIOOperationDispatcher::HandleReadOperations()
{
    fd_set  readset;

    if (select(static_cast<int>(bindFdsToSet(readset, m_readWatch)) + 1, &readset, nullptr, nullptr, m_timeout.get()) == -1)
        throw std::runtime_error("Select fails");
    performOperations(readset, NativeSocketIOOperationDispatcher::read);
}

/**
 * \brief Function that will check if fd to watch can write data through usage of <select>
 */
void Network::Core::NativeSocketIOOperationDispatcher::HandleWriteOperations()
{
    fd_set  writeset;

    if (select(static_cast<int>(bindFdsToSet(writeset, m_writeWatch)) + 1, nullptr, &writeset, nullptr, m_timeout.get()) == -1)
        throw std::runtime_error("Select fails");
    performOperations(writeset, NativeSocketIOOperationDispatcher::write);
}

/**
 * \brief Do the HandleReadOperations + HandleWriteOperations at the same time
 */
void Network::Core::NativeSocketIOOperationDispatcher::HandleOperations()
{
    fd_set readset;
    fd_set writeset;
    std::unique_ptr<struct timeval>  timeout = NULL;

    if (m_timeout.get() != NULL) {
        timeout.reset(new struct timeval(*m_timeout.get()));
    }

	if (select(static_cast<int>(std::max(bindFdsToSet(readset, m_readWatch), bindFdsToSet(writeset, m_writeWatch))) + 1, &readset, &writeset, nullptr, timeout.get()) == -1) {
		throw std::runtime_error("Select fails");
    }
    performOperations(readset, NativeSocketIOOperationDispatcher::read);
    performOperations(writeset, NativeSocketIOOperationDispatcher::write);
}

/**
 * \brief Allows us to bind a native <fd_set> with our fd to watch for an upcoming <select> call
 * \param set The <fd_set> variable in witch we will set our fd that we have to watch
 * \return The maximum fd value that we have in our set of fd
 */
SOCKET Network::Core::NativeSocketIOOperationDispatcher::bindFdsToSet(fd_set &set, std::list<Socket::ISockStreamHandler *> &tobind) const
{
    SOCKET max = 0;

    FD_ZERO(&set);
    for (const Network::Socket::ISockStreamHandler *curr : tobind)
    {
        SOCKET currsock = curr->getSocket().Native();
        FD_SET(currsock, &set);
        if (currsock > max)
            max = currsock;
    }
    return max;
}

/**
 * @brief Performs an operation. Could be either read or write. Will check if fds in watch list are in the set and will then call callbacks
 * @param set The set of fds to check
 * @param operation The operation to perform
 */
void Network::Core::NativeSocketIOOperationDispatcher::performOperations(fd_set &set, IOOperation const &operation)
{
    std::list<Socket::ISockStreamHandler *>  tmp = this->*operation.watched;

    for (Socket::ISockStreamHandler *curr : tmp)
    {
        if (std::find((this->*operation.watched).begin(), (this->*operation.watched).end(), curr) == (this->*operation.watched).end())
            continue;
        (curr->*operation.check)();
        if (FD_ISSET(curr->getSocket().Native(), &set))
        {
            (this->*operation.watched).remove(curr);
            (curr->*operation.callback)();
        }
    }
}


/**
 * \brief Will make a basic infinite server loop that will call select on fds to watch
 */
void Network::Core::NativeSocketIOOperationDispatcher::Run()
{
    signal(SIGINT, breakCatch);
    while (running && (m_readWatch.size() > 0 || m_writeWatch.size() > 0))
    {
        try
        {
            HandleOperations();
        }
        catch (std::runtime_error const &err)
        {
			(void)err;
        }
    }
    signal(SIGINT, SIG_DFL);
}

/**
 * @brief Will call <select> on handled streams
 */
void Network::Core::NativeSocketIOOperationDispatcher::Poll()
{
    HandleOperations();
}

/**
 * @brief Will perform check on <handler> parameter
 * @param handler The handler to check
 */
void Network::Core::NativeSocketIOOperationDispatcher::Poll(Network::Socket::ISockStreamHandler &handler)
{
    struct pollfd   fd = {handler.getSocket().Native(), POLLIN | POLLOUT, 0};

#if _WIN32
	if (WSAPoll(&fd, 1, 0) == -1)
		return;
#else
	if (poll(&fd, 1, 0) == -1)
		return;
#endif
    if (fd.revents & POLLIN)
        handler.OnAllowedToRead();
    if (fd.revents & POLLOUT)
        handler.OnAllowedToWrite();
}

/**
 * \brief Allow the NativeSocketIOOperationDispatcher to watch a new INativeSocketStreamHandler
 * \param towatch The new INativeSocketStreamHandler to watch
 */
void Network::Core::NativeSocketIOOperationDispatcher::Watch(Network::Socket::ISockStreamHandler &towatch, WatchMode mode)
{
#if _WIN32
	if (towatch.getSocket().Native() == INVALID_SOCKET)
		return;
#endif
	if (towatch.getSocket().Native() <= 2)
		return;
    if (mode & WatchMode::READ)
        m_readWatch.emplace_back(&towatch);
    if (mode & WatchMode::WRITE)
        m_writeWatch.emplace_back(&towatch);
}

/**
 * @brief Call Watch(INativeSocketStreamHandler &)
 * @param towatch The socket to watch
 */
void Network::Core::NativeSocketIOOperationDispatcher::Watch(Socket::ISockStreamHandler *towatch, WatchMode mode)
{
    Watch(*towatch, mode);
}

/**
 * @brief Set the internal timeout
 * @param timeout The value of the timer to set
 */
void    Network::Core::NativeSocketIOOperationDispatcher::setTimeout(struct timeval const &timeout)
{
    m_timeout.reset(new struct timeval(timeout));
}

/**
 * @brief Set the internal timeout
 * @param timeout The value of the timer to set
 */
void    Network::Core::NativeSocketIOOperationDispatcher::setTimeout(struct timeval *timeout)
{
    m_timeout.reset(timeout);
}

/**
 * @brief Checks if a user is already bind into watch socket system
 * @param tocheck The user to check existance
 * @param mode The mode in which user want to be checked (READ/WRITE/BOTH)
 * @return True if the user is in specified lists, false either
 */
bool Network::Core::NativeSocketIOOperationDispatcher::IsBinded(Network::Socket::ISockStreamHandler *tocheck, WatchMode mode)
{
    return (
            mode & WatchMode::READ &&   //Check if the user want to check the read list
            std::any_of(                //Check in the read list
                    m_readWatch.begin(),
                    m_readWatch.end(),
                    [tocheck](Socket::ISockStreamHandler *curr){
                            return tocheck == curr;
                        })
    ) || (
            mode & WatchMode::WRITE && //Check if the user want to check in the write list
            std::any_of(               //Check in the write list
                    m_writeWatch.begin(),
                    m_writeWatch.end(),
                    [tocheck](Socket::ISockStreamHandler *curr){
                            return tocheck == curr;
                        })
    );

}

/**
 * @brief Removes any king of reference to <torm> parameter in the good watch list defined by <mode>
 * @param torm The pointer on the object to remove
 * @param mode Defines in which watch list we will remove the <torm> parameter
 */
void Network::Core::NativeSocketIOOperationDispatcher::Remove(Network::Socket::ISockStreamHandler *torm,
                                                              Network::Core::NativeSocketIOOperationDispatcher::WatchMode mode)
{
    if (mode & WatchMode::READ)
    {
        m_readWatch.remove(torm);
    }
    if (mode & WatchMode::WRITE)
    {
        m_writeWatch.remove(torm);
    }
}
