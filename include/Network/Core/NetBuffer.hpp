//
// Created by gaspar_q on 11/21/16.
//

#ifndef NETWORK_NETBUFFER_HPP
#define NETWORK_NETBUFFER_HPP

#include <sys/types.h>
#include <cstring>
#include <string>

#define MAX_MTU 1024

namespace Network
{
    namespace Core
    {
        /**
         * \brief Class used to abstract the network buffer in which packets will be stored. You can either serialize or deserialize objects
         */
        class NetBuffer
        {
        public:
            static const size_t size;

        public:
            NetBuffer();
            NetBuffer(NetBuffer const &ref);
            ~NetBuffer();

            NetBuffer(std::string const &txt);

            NetBuffer &operator=(NetBuffer const &ref);

        public:
            /**
             * \brief Serialiaze a type into the buffer
             * \param obj The object to serialize
             * \return True if the object has been serialiazed into buffer false either
             */
            template <typename T>
            bool serialize(T const &obj)
            {
                if (index + sizeof(T) > size || index + sizeof(T) > currlen)
                    return false;
                union swp
                {
                    T dat;
                    unsigned char cvrt[sizeof(T)];
                } dest;
                dest.dat = obj;
#if __BYTE_ORDER == __BIG_ENDIAN
                for (size_t i = sizeof(T) - 1; i >= 0; ++i)
                    data[index + i] = dest.cvrt[i];
#elif __BYTE_ORDER == __LITTLE_ENDIAN
                memcpy(&data[index], dest.cvrt, sizeof(T));
#endif
                index += sizeof(T);
                return true;
            }

            /**
             * \brief Deserialize a type into the buffer
             * \param obj The object in which deserialize
             * \return True if the object has been deserialized into <obj>
             */
            template <typename T>
            bool deserialize(T &obj)
            {
                if (index < sizeof(T))
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
                index -= sizeof(T);
                return true;
            }

        public:
            /**
             * \brief Reset the buffer internally to position 0
             */
            void reset()
            {
                index = 0;
                currlen = 0;
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

            /**
             * Converts the buffer into a std::string
             * @return The string that corresponds to the buffer
             */
            std::string toString()
            {
                return std::string(buff<char>(), currlen);
            }

            /**
             * @brief Set a text message into the current buffer
             * @param msg The text message to set
             */
            void setTextMessage(std::string const &msg)
            {
                currlen = msg.size();
                strncpy(buff<char>(), msg.c_str(), currlen);
            }

            /**
             * @brief Setter for currlen
             * @param len The length to set
             */
            void    setCurrlen(size_t len)
            {
                currlen = len;
            }

            /**
             * @brief Returns the current length of the buffer
             * @return The current length of the buffer
             */
            size_t getCurrlen() const
            {
                return currlen;
            }

        private:
            unsigned char   data[MAX_MTU];
            size_t          index;
            size_t          currlen; //todo use it
        };
    }
}

#endif //NETWORK_NETBUFFER_HPP
