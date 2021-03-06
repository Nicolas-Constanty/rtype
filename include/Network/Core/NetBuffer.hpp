//
// Created by gaspar_q on 11/21/16.
//

#ifndef NETWORK_NETBUFFER_HPP
#define NETWORK_NETBUFFER_HPP

#include <sys/types.h>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>

#define MAX_MTU 1024

#include <typeinfo>
#include "Common/DLLexport.hpp"

namespace Network
{
    namespace Core
    {
        /**
         * \brief Class used to abstract the network buffer in which packets will be stored. You can either serialize or deserialize objects
         */
        class PREF_EXPORT NetBuffer
        {
        public:
//            static const size_t size;

        public:
            NetBuffer();
            NetBuffer(NetBuffer const &ref);
            ~NetBuffer();
			static size_t Size();

            /**
             * @brief Template constructor used to directly serialize an object at construction
             * @tparam T The type of the object to serialize
             * @param rf The object to serialize
             */
            template <typename T>
            NetBuffer(T const &rf) :
                    NetBuffer()
            {
                serialize(rf);
            }

            NetBuffer &operator=(NetBuffer const &ref);
            NetBuffer &operator+=(NetBuffer const &ref);
            NetBuffer operator+(NetBuffer const &ref);

        public:
            bool    ConcatTo(NetBuffer const &ref);

        public:
            /**
             * \brief Serialiaze a type into the buffer
             * \param obj The object to serialize
             * \return True if the object has been serialiazed into buffer false either
             */
            template <typename T>
            bool serialize(T const &obj)
            {
                if (length + sizeof(T) > Size())
                {
                    return false;
                }
                memset(buff(), 0, getAvailableSpace());
                union swp
                {
                    T dat;
                    unsigned char cvrt[sizeof(T)];

                    swp() { memset(this, 0, sizeof(swp)); }
                    ~swp() {  }
                } dest;
                dest.dat = obj;
                #if __BYTE_ORDER == __BIG_ENDIAN
                    for (int i = sizeof(T) - 1; i >= 0; --i)
                    data[index + i] = dest.cvrt[i];
                #elif __BYTE_ORDER == __LITTLE_ENDIAN
                    memcpy(&data[length], dest.cvrt, sizeof(T));
                #endif
                length += sizeof(T);

//                std::cout << "\e[32mData serialized\e[0m" << std::endl;
//                std::cout << "Serializing => " << typeid(T).name() << " of size => " << sizeof(T) << std::endl;
                return true;
            }

            /**
             * @brief Serialize template polymorphism in order to catch char arrays serialization
             * @tparam n The size of the array
             * @param msg The message to serialize
             * @return If the serialization was done
             */
            template <size_t n>
            bool serialize(char const (&msg)[n])
            {
                return serialize<const char *>(&msg[0]);
            }

            void operator+=(unsigned int s) {
                if (static_cast<long>(length) - s < 0) {
                    return ;
                }
                index += s;
                length -= s;
            }

            /**
             * \brief Deserialize a type into the buffer
             * \param obj The object in which deserialize
             * \return True if the object has been deserialized into <obj>
             */
            template <typename T>
            bool deserialize(T &obj)
            {
                if (index + sizeof(T) < sizeof(T))
                    return false;
                union swp
                {
                    T dat;
                    unsigned char cvrt[sizeof(T)];
                } dest;
                #if __BYTE_ORDER == __BIG_ENDIAN
                    for (size_t i = sizeof(T) - 1; i >= 0; ++i)
                    dest.cvrt[i] = data[index + i];
                #elif __BYTE_ORDER == __LITTLE_ENDIAN
                    memcpy(dest.cvrt, &data[index], sizeof(T));
                #endif
                obj = dest.dat;
                index += sizeof(T);
                length -= sizeof(T);
                return true;
            }

            /**
             * \brief Getter for internal buffer
             * \return A pointer on the <index> case of the internal buffer
             */
            template <typename RetType = unsigned char>
            RetType *buff() const
            {
                return (RetType *)&data[index];
            }

        public:
            void reset();
            std::string toString() const;
            void consume();

        public:
            void setLength(size_t len);
            size_t getLength() const;
            void addLength(size_t len);
            bool isFull();
            size_t getAvailableSpace() const;

        private:
            unsigned char   data[MAX_MTU];
            size_t          index;
            size_t          length; //todo use it
        };

        template <>
		PREF_EXPORT bool NetBuffer::serialize<std::string>(std::string const &);
        template <>
		PREF_EXPORT bool NetBuffer::serialize<const char *>(const char * const &);
        template <>
		PREF_EXPORT bool NetBuffer::serialize<NetBuffer>(NetBuffer const &);

		PREF_EXPORT std::ostream    &operator<<(std::ostream &output, NetBuffer const &ref);
    }
}

#endif //NETWORK_NETBUFFER_HPP
