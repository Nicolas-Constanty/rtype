#include "SaltyEngine/Factory.hpp"
#include "SaltyEngine/Object.hpp"


namespace SaltyEngine {
    std::map<std::string, Object *> Factory::m_prefabs = {{"DefaultMonster", new Object("DefaultMonster")}};
    std::list<std::shared_ptr<Object> > Factory::m_objects;

    Factory::~Factory() {
    }

    std::shared_ptr<Object> Factory::Create(std::string const &name) {
        m_objects.push_front(m_prefabs[name]->Clone());
        return m_objects.front();
    }
}
