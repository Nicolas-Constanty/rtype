#include "Common/DllLoader.hpp"

DllLoader::DllLoader()
{
}


DllLoader::~DllLoader()
{
}

HINSTANCE DllLoader::Load(std::string const& path)
{
	return m_inst = LoadLibrary(path.c_str());
}

BOOL DllLoader::Unload()
{
	return FreeLibrary(m_inst);
}