#pragma once

#ifndef IWINDOW_HPP_
#define IWINDOW_HPP_

namespace SaltyEngine
{
	class IWindow
	{
	public:
		virtual ~IWindow() {};
		virtual bool IsOpen() const = 0;
	};
}

#endif // !IWINDOW_HPP_
