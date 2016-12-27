#pragma once

#ifndef IEVENTSYSTEMHANDLER_HPP_
#define IEVENTSYSTEMHANDLER_HPP_

#include "Common/DLLexport.hpp"

namespace SaltyEngine
{
	namespace GUI
	{
		class LIB_EXPORT IEventSystemHandler
		{
		public:
			virtual ~IEventSystemHandler() {};
		};
	}
}

#endif // !IEVENTSYSTEMHANDLER_HPP_
