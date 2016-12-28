//
// Created by gaspar_q on 10/27/16.
//

#ifndef OPENSSL_ISTREAM_HPP
#define OPENSSL_ISTREAM_HPP

#include "Network/Core/NetBuffer.hpp"

namespace Network
{
	namespace Socket
	{
		class PREF_EXPORT ISockStream
		{
		public:
			virtual ~ISockStream(){}

		public:
			virtual int Receive(Core::NetBuffer &buff) = 0;
			virtual int Send(Core::NetBuffer const &buff) const = 0;

		public:
			virtual int ReceiveFrom(Core::NetBuffer &buff, ISockStream &sender) = 0;
			virtual int SendTo(Core::NetBuffer &buff, ISockStream const &receiver) = 0;
		};
	}
}

#endif //OPENSSL_ISTREAM_HPP
