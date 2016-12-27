#pragma once

#ifndef IMOVEHANDLER_HPP_
#define IMOVEHANDLER_HPP_

#include "SaltyEngine/GUI/IEventSystemHandler.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class LIB_EXPORT IMoveHandler : public IEventSystemHandler
		{
		public:
			virtual ~IMoveHandler() {};
			virtual void OnMove() = 0;
		};
	}
}

#endif // !IMOVEHANDLER_HPP_
