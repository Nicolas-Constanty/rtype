#pragma once

#ifndef LIBLOADER_HPP_
#define LIBLOADER_HPP_

#include <string>
#include <iostream>
#ifndef _WIN32
#include <dlfcn.h>
#endif
#include "ILibraryLoader.hpp"

class LibLoader : public ILibraryLoader<void const*>
{
    typedef void *(*func)();
private:
	void *m_inst = nullptr;

public:
	LibLoader();
	virtual ~LibLoader();

public:
	virtual void const *Load(std::string const& path);
	virtual int Unload();
	template <class ... Args>
	void* Call(std::string const& funcName, Args ... args)
	{
        if (m_inst == nullptr)
        {
            std::cerr << "Library not loaded yet." << std::endl;
            return static_cast<void*>(0);
        }
        func fp = (func)dlsym(m_inst, funcName.c_str());
		if (fp == nullptr)
		{
			std::cerr << funcName << " not found in .so." << std::endl;
		}
		else
		{
			return fp(args...);
		}
		return static_cast<void*>(0);
	}
};

#endif