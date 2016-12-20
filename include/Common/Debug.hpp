#pragma once

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <iostream>
#include <string>
#if _WIN32
	#include <windows.h>
#endif

class Debug
{
public:
	enum COLOR
	{
		DEFAULT,
		RED,
		GREEN,
		YELLOW,
		BLUE
	};
	static void PrintError(const std::string &msg);
	static void PrintWarning(const std::string &msg);
	static void PrintSuccess(const std::string & msg);
	static void PrintInfo(const std::string & msg);
	static void Print(const std::string &msg);
	static void PrintColor(const std::string &msg, int index);
#if _WIN32
	static const WORD colors[];
#else
	static const char* const colors[];
#endif
};

#endif // !DEBUG_HPP_

