#pragma once

#ifndef IDESELECTHANDLER_HPP_
#define IDESELECTHANDLER_HPP_

#include "SaltyEngine/GUI/IEventSystemHandler.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class LIB_EXPORT IDeselectHandler : public IEventSystemHandler
		{
		public:
			virtual ~IDeselectHandler() {};
			virtual void OnDeselect() = 0;
		};
	}
}

#endif // !IDESELECTHANDLER_HPP_
