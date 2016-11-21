#include "SaltyEngine/Factory.hpp"
#include "SaltyEngine/Object.hpp"


namespace SaltyEngine {
    std::map<std::string, Object *> Factory::m_prefabs = {{"DefaultMonster", new Object("DefaultMonster(Clone)")}};

    Factory::~Factory() {
    }

    std::shared_ptr<Object> Factory::Create(std::string const &name) {
        return m_prefabs[name]->Clone();
    }
}
