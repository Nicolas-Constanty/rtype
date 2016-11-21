#include "SaltyEngine/Factory.hpp"
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/GameObject.hpp"


namespace SaltyEngine {
    std::map<std::string, Object *> Factory::m_prefabs = {
    	{"DefaultMonster", new GameObject("DefaultMonster")},
		{"Mutant", new GameObject("Mutant")},
		{"Script", new SaltyBehaviour(nullptr)}
    };
    std::list<std::shared_ptr<Object> > Factory::m_objects;

    Factory::~Factory() {
    }

    std::shared_ptr<Object> Factory::Create(std::string const &name) {
		if (m_prefabs.find(name) == m_prefabs.end())
		{
			return nullptr;
		}
        m_objects.push_front(m_prefabs[name]->Clone());
        return m_objects.front();
    }
}
