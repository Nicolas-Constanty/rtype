#pragma once

#ifndef IPOINTERDOWNHANDLER_HPP_
#define IPOINTERDOWNHANDLER_HPP_

#include "SaltyEngine/GUI/IEventSystemHandler.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class LIB_EXPORT IPointerDownHandler : public IEventSystemHandler
		{
		public:
			virtual ~IPointerDownHandler() {};
			virtual void OnPointerDown() = 0;
		};
	}
}

#endif // !IPOINTERDOWNHANDLER_HPP_
