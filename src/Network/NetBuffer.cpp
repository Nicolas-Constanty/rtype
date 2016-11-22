//
// Created by gaspar_q on 11/21/16.
//

#include <Network/NetBuffer.hpp>

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
 * \brief Basic destructor
 */
Network::Core::NetBuffer::~NetBuffer()
{

}