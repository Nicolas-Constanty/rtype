#include "SaltyEngine\Factory.hpp"

SaltyEngine::Factory::~Factory()
{
}

template <class ... Args>
std::shared_ptr<SaltyEngine::Object> SaltyEngine::Factory::Create(std::string const& name, Args... args)
{
	return m_prefabs[name]->Clone();
}

std::map<std::string, SaltyEngine::GameObject*> SaltyEngine::Factory::m_prefabs = {{"DefaultMonster", new Object("DefaultMonster(Clone)")}};