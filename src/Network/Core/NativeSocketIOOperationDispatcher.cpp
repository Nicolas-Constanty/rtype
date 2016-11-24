//
// Created by gaspar_q on 11/10/16.
//

#include <csignal>
#include <Network/Core/NativeSocketIOOperationDispatcher.hpp>

/**
 * \brief A Boolean variable used in <Run> method as conditional for the infinite server loop. Eq false on Crtl+C
 */
static bool running = true;

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

    if (select(bindFdsToSet(readset) + 1, &readset, NULL, NULL, m_timeout.get()) == -1)
        throw std::runtime_error("Select fails");
    performReadOperations(readset);
}

/**
 * \brief Function that will check if fd to watch can write data through usage of <select>
 */
void Network::Core::NativeSocketIOOperationDispatcher::HandleWriteOperations()
{
    fd_set  writeset;

    if (select(bindFdsToSet(writeset) + 1, NULL, &writeset, NULL, m_timeout.get()) == -1)
        throw std::runtime_error("Select fails");
    performWriteOperations(writeset);
}

/**
 * \brief Do the HandleReadOperations + HandleWriteOperations at the same time
 */
void Network::Core::NativeSocketIOOperationDispatcher::HandleOperations()
{
    fd_set readset;
    fd_set writeset;
    std::unique_ptr<struct timeval>  timeout = NULL;

    if (m_timeout.get() != NULL)
        timeout.reset(new struct timeval(*m_timeout.get()));
    if (select(std::max(bindFdsToSet(readset), bindFdsToSet(writeset)) + 1, &readset, &writeset, NULL, timeout.get()) == -1)
        throw std::runtime_error("Select fails");
    performReadOperations(readset);
    performWriteOperations(writeset);
}

/**
 * \brief Allows us to bind a native <fd_set> with our fd to watch for an upcoming <select> call
 * \param set The <fd_set> variable in witch we will set our fd that we have to watch
 * \return The maximum fd value that we have in our set of fd
 */
SOCKET Network::Core::NativeSocketIOOperationDispatcher::bindFdsToSet(fd_set &set) const
{
    SOCKET max = 0;

    FD_ZERO(&set);
    for (const std::unique_ptr<Network::Socket::INativeSocketStreamHandler> &curr : m_toWatch)
    {
        SOCKET currsock = curr->getSocket().Native();
        FD_SET(currsock, &set);
        if (currsock > max)
            max = currsock;
    }
    return max;
}

/**
 * \brief Will check, after <select> has been called, if we can read data of fd. If we can we will call OnAllowedToRead callback
 * \param set The <fd_set> that passed through the eye of <select> in parameter <read_fds>
 */
void Network::Core::NativeSocketIOOperationDispatcher::performReadOperations(fd_set &set)
{
    for (std::list<std::unique_ptr<Network::Socket::INativeSocketStreamHandler> >::iterator it = m_toWatch.begin(); it != m_toWatch.end(); ++it)
    {
        if (FD_ISSET((*it)->getSocket().Native(), &set) && !(*it)->OnAllowedToRead())
            it = m_toWatch.erase(it);
    }
}

/**
 * \brief Will check, after <select> has been called, if a we can write data on fd. If we can we will call OnAllowedToWrite callback
 * \param set The <fd_set> that passed through the eye of <select> in parameter <write_fds>
 */
void Network::Core::NativeSocketIOOperationDispatcher::performWriteOperations(fd_set &set)
{
    for (std::list<std::unique_ptr<Network::Socket::INativeSocketStreamHandler> >::iterator it = m_toWatch.begin(); it != m_toWatch.end(); ++it)
    {
        if (FD_ISSET((*it)->getSocket().Native(), &set) && !(*it)->OnAllowedToWrite())
            it = m_toWatch.erase(it);
    }
}

/**
 * \brief Will make a basic infinite server loop that will call select on fds to watch
 */
void Network::Core::NativeSocketIOOperationDispatcher::Run()
{
    signal(SIGINT, breakCatch);
    std::cout << "Handling sigint" << std::endl;
    while (running)
    {
        std::cout << "Handling operations" << std::endl;
        HandleOperations();
        usleep(500000);
    }
    std::cout << "Leaving" << std::endl;
    signal(SIGINT, SIG_DFL);
}

/**
 * \brief Allow the NativeSocketIOOperationDispatcher to watch a new INativeSocketStreamHandler
 * \param towatch The new INativeSocketStreamHandler to watch
 */
void Network::Core::NativeSocketIOOperationDispatcher::Watch(Network::Socket::INativeSocketStreamHandler &towatch)
{
    m_toWatch.emplace_back(&towatch);
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
 * @brief Swap the client instance in the internal watcher buffer
 * @param curr The current client to swap
 * @param newone The new client instance with which replace <curr>
 */
void Network::Core::NativeSocketIOOperationDispatcher::Swap(Network::Socket::INativeSocketStreamHandler &curr,
                                                            Network::Socket::INativeSocketStreamHandler &newone)
{
    for (std::unique_ptr<Network::Socket::INativeSocketStreamHandler> &toswp : m_toWatch)
    {
        if (toswp.get() == &curr)
        {
            std::cout << "Swapping client" << std::endl;
            return toswp.reset(&newone);
        }
    }
}