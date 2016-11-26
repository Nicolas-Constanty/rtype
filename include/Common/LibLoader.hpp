#pragma once

#ifndef LIBLOADER_HPP_
#define LIBLOADER_HPP_

#include <string>
#include <iostream>
#include <dlfcn.h>
#include "ILibraryLoader.hpp"

class LibLoader : public ILibraryLoader<void const*>
{
private:
	void *m_inst = nullptr;

public:
	LibLoader();
	virtual ~LibLoader();

public:
	virtual void const*Load(std::string const& path);
	virtual bool Unload();
	template <class ... Args>
	auto Call(std::string const& funcName, Args ... args) -> decltype(fp(args...))
	{
        if (m_inst == nullptr)
        {
            std::cerr << "Library not loaded yet." << std::endl;
            return static_cast<decltype(fp(args...))>(0);
        }
		void *fp = dlsym(m_inst, funcName.c_str());
		if (fp == nullptr)
		{
			std::cerr << funcName << " not found in .so." << std::endl;
		}
		else
		{
			return fp(args...);
		}
		return static_cast<decltype(fp(args...))>(0);
	}
};

#endif