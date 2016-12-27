#pragma once

#ifndef IWINDOW_HPP_
#define IWINDOW_HPP_

#include "Common/DLLexport.hpp"

namespace SaltyEngine
{
	class LIB_EXPORT IWindow
	{
	public:
		virtual ~IWindow() {};
		virtual bool IsOpen() const = 0;
	};
}

#endif // !IWINDOW_HPP_
