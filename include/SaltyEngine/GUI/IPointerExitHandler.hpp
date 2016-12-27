#pragma once

#ifndef IPOINTEREXITHANDLER_HPP_
#define IPOINTEREXITHANDLER_HPP_

#include "SaltyEngine/GUI/IEventSystemHandler.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class LIB_EXPORT IPointerExitHandler : public IEventSystemHandler
		{
		public:
			virtual ~IPointerExitHandler() {};
			virtual void OnPointerExit() = 0;
		};
	}
}

#endif // !IPOINTEREXITHANDLER_HPP_
