#pragma once

#ifndef DLLLOADER_HPP_
#define DLLLOADER_HPP_

#include <Windows.h>
#include <string>
#include "ILibraryLoader.hpp"

class DllLoader : public ILibraryLoader<HINSTANCE>
{
public:
	DllLoader();
	virtual ~DllLoader();

public:
	virtual HINSTANCE Load(std::string const& path);
	virtual bool Unload();

private:
	HINSTANCE m_inst;
};

#endif