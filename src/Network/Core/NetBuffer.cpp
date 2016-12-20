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
    length(0)
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
    memcpy(data, ref.data, ref.length);
    index = ref.index;
    length = ref.length;
    return *this;
}

/**
 * @brief Will concatenate the <ref> buffer into <this> buffer. Will set the index and the length of the buffer
 * @param ref The buffer to concatenate
 * @return A reference on freshly changes <this>
 */
Network::Core::NetBuffer &Network::Core::NetBuffer::operator+=(const Network::Core::NetBuffer &ref)
{
    ConcatTo(ref);
    return *this;
}

/**
 * @brief Will concatenate the <ref> buffer with <this> buffer into a copy
 * @param ref The reference to concatenate
 * @return A copy of the concatenates buffers
 */
Network::Core::NetBuffer Network::Core::NetBuffer::operator+(const Network::Core::NetBuffer &ref)
{
    NetBuffer   toret(*this);
    return toret += ref;
}

/**
 * @brief Concatenate to buffers
 * @param ref To reference to concatenate
 * @return True if the concatenation is possible
 */
bool Network::Core::NetBuffer::ConcatTo(const Network::Core::NetBuffer &ref)
{
    if (length + ref.length > NetBuffer::size)
        return false;
    consume();
    memcpy(&data[length], ref.buff(), ref.length);
    length += ref.length;
    return true;
}

/**
 * \brief Reset the buffer internally to position 0
 */
void Network::Core::NetBuffer::reset()
{
    index = 0;
    length = 0;
}

/**
 * Converts the buffer into a std::string
 * @return The string that corresponds to the buffer
 */
std::string Network::Core::NetBuffer::toString() const
{
    return std::string(buff<char>(), length);
}

/**
 * @brief Setter for currlen
 * @param len The length to set
 */
void Network::Core::NetBuffer::setLength(size_t len)
{
    length = len;
}

/**
 * @brief Returns the current length of the buffer
 * @return The current length of the buffer
 */
size_t Network::Core::NetBuffer::getLength() const
{
    return length;
}


/**
 * @brief Allow user to add length
 * @param len The length to add
 */
void Network::Core::NetBuffer::addLength(size_t len)
{
    length += len;
}

/**
 * @brief Check if the buffer is full
 * @return True if it is, false either
 */
bool Network::Core::NetBuffer::isFull()
{
    return length == size;
}

/**
 * @brief Allow user to know how much space is available into the buffer
 * @return The available space in the buffer
 */
size_t Network::Core::NetBuffer::getAvailableSpace() const
{
    return NetBuffer::size - length;
}

void Network::Core::NetBuffer::consume()
{
    memmove(data, buff(), length);
    index = 0;
}

/**
 * @brief Serialize template specialization for strings in order to copy string instead of pointer address
 * @param obj The string to serialize
 * @return If serialization was done
 */
template <>
bool Network::Core::NetBuffer::serialize<std::string>(std::string const &obj)
{
    if (length + obj.size() > NetBuffer::size)
        return false;
#if _WIN32
	strncpy_s(buff<char>(), NetBuffer::size, obj.c_str(), obj.size());
#else
	strncpy(buff<char>(), obj.c_str(), obj.size());
#endif // _WIN32

    
    length += obj.size();
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
    for (size_t i = 0, max = ref.getLength(); i < max; ++i)
    {
        if (bf[i] >= ' ' && bf[i] <= '~')
            output << bf[i];
        else
            output << "\x1B[7m\\x" << static_cast<unsigned int>(bf[i]) << "\x1B[0m";
    }
    output << "\"(" << std::dec << ref.getLength() << ")";
    return output;
}