#ifdef _WIN32

#include "Common/DllLoader.hpp"

DllLoader::DllLoader(): m_inst(nullptr)
{
}


DllLoader::~DllLoader()
{
}

HMODULE DllLoader::Load(std::string const& path)
{
	return m_inst = LoadLibrary(path.c_str());
}

int DllLoader::Unload()
{
	return FreeLibrary(m_inst);
}

#endif