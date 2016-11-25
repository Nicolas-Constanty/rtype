#pragma once

#ifndef IPOINTERUPHANDLER_HPP_
#define IPOINTERUPHANDLER_HPP_

#include "SaltyEngine/GUI/IEventSystemHandler.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class IPointerUpHandler : public IEventSystemHandler
		{
		public:
			virtual ~IPointerUpHandler() {};
			virtual void OnPointerUp() = 0;
		};
	}
}

#endif // !IPOINTERUPHANDLER_HPP_
