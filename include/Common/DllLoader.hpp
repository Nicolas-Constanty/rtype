#pragma once

#ifndef DLLLOADER_HPP_
#define DLLLOADER_HPP_

#ifdef _WIN32
#include <Windows.h>
#include <string>
#include <iostream>
#include "ILibraryLoader.hpp"
#include "Common/DLLexport.hpp"

class LIB_EXPORT DllLoader : public ILibraryLoader<HINSTANCE>
{
private:
	HINSTANCE m_inst;

public:
	DllLoader();
	virtual ~DllLoader();

public:
	virtual HINSTANCE Load(std::string const& path);
	virtual int Unload();
	template <class ... Args>
	auto Call(std::string const& funcName, Args ... args)
	{
		FARPROC fp = GetProcAddress(m_inst, funcName.c_str());
		if (fp == nullptr)
		{
			std::cerr << funcName << " not found in dll." << std::endl;
		}
		else
		{
			return fp(args...);
		}
		return static_cast<decltype(fp(args...))>(0);
	}
};
#endif

#endif