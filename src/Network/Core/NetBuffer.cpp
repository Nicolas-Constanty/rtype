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
 * @brief Copy operator
 * @param ref
 * @return
 */
Network::Core::NetBuffer &Network::Core::NetBuffer::operator=(const Network::Core::NetBuffer &ref)
{
    memcpy(data, ref.data, ref.currlen);
    index = ref.index;
    currlen = ref.currlen;
    return *this;
}

/**
 * \brief Reset the buffer internally to position 0
 */
void Network::Core::NetBuffer::reset()
{
    index = 0;
    currlen = 0;
}

/**
 * Converts the buffer into a std::string
 * @return The string that corresponds to the buffer
 */
std::string Network::Core::NetBuffer::toString() const
{
    return std::string(buff<char>(), currlen);
}

/**
 * @brief Setter for currlen
 * @param len The length to set
 */
void Network::Core::NetBuffer::setCurrlen(size_t len)
{
    currlen = len;
}

/**
 * @brief Returns the current length of the buffer
 * @return The current length of the buffer
 */
size_t Network::Core::NetBuffer::getCurrlen() const
{
    return currlen;
}

/**
 * @brief Check if the buffer is full
 * @return True if it is, false either
 */
bool Network::Core::NetBuffer::isFull()
{
    return currlen == size;
}

/**
 * @brief Serialize template specialization for strings in order to copy string instead of pointer address
 * @param obj The string to serialize
 * @return If serialization was done
 */
template <>
bool Network::Core::NetBuffer::serialize<std::string>(std::string const &obj)
{
    if (currlen + obj.size() > NetBuffer::size)
        return false;
    strncpy(buff<char>(), obj.c_str(), obj.size());
    currlen += obj.size();
    return true;
}

/**
 * @brief Serialize template specialization for const char * (msg between quotes)
 * @param obj The message to serialize
 * @return If serialization was done
 */
template <>
bool Network::Core::NetBuffer::serialize<const char *>(const char * const &obj)
{
    return serialize(std::string(obj));
}

/**
 * @brief Serialize template specialization for Netbuffer. Will serialize the internal buffer
 * @param ref The buffer to serialize
 * @return If serialization was done
 */
template <>
bool Network::Core::NetBuffer::serialize<Network::Core::NetBuffer>(Network::Core::NetBuffer const &ref)
{
    return serialize(ref.toString());
}

/**
 * @brief Allow user to dump a net buffer on an ostream (will dump unprintable character into hexadecimal)
 * @param output The stream in which dump the buffer
 * @param ref The buffer to dump
 * @return A reference on the stream in order to allow user to chain '<<'
 */
std::ostream    &Network::Core::operator<<(std::ostream &output, Network::Core::NetBuffer const &ref)
{
    unsigned char *bf = ref.buff();

    output << "\"" << std::hex;
    for (size_t i = 0, max = ref.getCurrlen(); i < max; ++i)
    {
        if (bf[i] >= ' ' && bf[i] <= '~')
            output << bf[i];
        else
            output << "\x1B[7m\\x" << static_cast<unsigned int>(bf[i]) << "\x1B[0m";
    }
    output << "\"(" << std::dec << ref.getCurrlen() << ")";
    return output;
}