#pragma once

#ifndef ISELECTHANDLER_HPP_
#define ISELECTHANDLER_HPP_

#include "SaltyEngine/GUI/IEventSystemHandler.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class ISelectHandler : public IEventSystemHandler
		{
		public:
			virtual ~ISelectHandler() {};
			virtual void OnSelect() = 0;
		};
	}
}

#endif // !ISELECTHANDLER_HPP_
