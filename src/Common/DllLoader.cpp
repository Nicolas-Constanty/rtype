#include "Common/DllLoader.hpp"

DllLoader::DllLoader(): m_inst(nullptr)
{
}


DllLoader::~DllLoader()
{
}

HINSTANCE DllLoader::Load(std::string const& path)
{
	return m_inst = LoadLibrary(path.c_str());
}

int DllLoader::Unload()
{
	return FreeLibrary(m_inst);
}