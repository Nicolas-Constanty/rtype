#pragma once

#ifndef IPOINTERENTERHANDLER_HPP_
#define IPOINTERENTERHANDLER_HPP_

#include "SaltyEngine/GUI/IEventSystemHandler.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class LIB_EXPORT IPointerEnterHandler : public IEventSystemHandler
		{
		public:
			virtual ~IPointerEnterHandler() {};
			virtual void OnPointerEnter() = 0;
		};
	}
}

#endif // !IPOINTERENTERHANDLER_HPP_
