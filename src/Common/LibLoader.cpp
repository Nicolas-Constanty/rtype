#include <unistd.h>
#include "Common/LibLoader.hpp"

LibLoader::LibLoader()
{
}


LibLoader::~LibLoader()
{
}

void const *LibLoader::Load(std::string const& path)
{
	return m_inst = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
}

int LibLoader::Unload()
{
    if (m_inst == nullptr)
        return false;
    dlclose(m_inst);
    return true;
}