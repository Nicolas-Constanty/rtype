#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/Factory.hpp"
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/GameObject.hpp"

namespace SaltyEngine {

	std::map<std::string, Object *> Factory::m_prefabs;
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

	bool Factory::LoadAsset(std::string const& path)
	{
        static Asset::ASSET_LOADER loader;

        if (loader.Load(path) == nullptr)
        {
            std::cerr << "Factory: failed to load asset at path [" << path << "]" << std::endl;
            return false;
        }
        Object *obj = (GameObject*)(loader.Call("GetObjectPrefab"));
        if (obj == nullptr)
        {
            std::cerr << "Factory: failed to get asset." << std::endl;
            return false;
        }
        if (m_prefabs.find(obj->GetName()) != m_prefabs.end())
        {
            std::cerr << "Prefab [" << obj->GetName() << "] already in prefab list." << std::endl;
            return false;
        }
        m_prefabs[obj->GetName()] = obj;
        //loader.Unload();
		return true;
	}
}
