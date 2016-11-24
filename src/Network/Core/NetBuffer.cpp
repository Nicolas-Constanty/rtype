//
// Created by gaspar_q on 11/21/16.
//

#include <Network/Core/NetBuffer.hpp>
#include <iostream>

/**
 * \brief The internal size of the buffer. Limited in order to resolve MTU bug
 */
const size_t Network::Core::NetBuffer::size = MAX_MTU;

/**
 * \brief Basic constructor
 */
Network::Core::NetBuffer::NetBuffer() :
    data(),
    index(0),
    currlen(0)
{

}

/**
 * @brief Copy constructor
 * @param ref The reference to copy
 */
Network::Core::NetBuffer::NetBuffer(const Network::Core::NetBuffer &ref)
{
    *this = ref;
}

/**
 * \brief Basic destructor
 */
Network::Core::NetBuffer::~NetBuffer()
{

}

/**
 * @brief String constructor
 * @param txt The text to set
 */
Network::Core::NetBuffer::NetBuffer(std::string const &txt) :
    Network::Core::NetBuffer()
{
    setTextMessage(txt);
}

/**
 * @brief Copy operator
 * @param ref
 * @return
 */
Network::Core::NetBuffer &Network::Core::NetBuffer::operator=(const Network::Core::NetBuffer &ref)
{
    memcpy(data, ref.data, Network::Core::NetBuffer::size);
    index = ref.index;
    currlen = ref.currlen;
    return *this;
}
