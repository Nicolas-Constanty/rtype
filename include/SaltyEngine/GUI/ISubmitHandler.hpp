#pragma once

#ifndef ISUBMITHANDLER_HPP_
#define ISUBMITHANDLER_HPP_

#include "SaltyEngine/GUI/IEventSystemHandler.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class ISubmitHandler : public IEventSystemHandler
		{
		public:
			virtual ~ISubmitHandler() {};
			virtual void OnSubmit() = 0;
		};
	}
}

#endif // !ISUBMITHANDLER_HPP_
