#include "SaltyEngine\Factory.hpp"

SaltyEngine::Factory::Factory()
{
}

SaltyEngine::Factory::~Factory()
{
}

template <class ... Args>
auto SaltyEngine::Factory::Create(std::string const& name, Args... args) -> decltype(m_prefabs[name]->CloneMemberwise())
{
	return m_prefabs[name]->CloneMemberwise();
}

std::map<std::string, SaltyEngine::GameObject*> SaltyEngine::Factory::m_prefabs = {{"DefaultMonster", new GameObject("DefaultMonster(Clone)")}};