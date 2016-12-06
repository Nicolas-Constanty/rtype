#include <SaltyEngine/Debug.hpp>
#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/Factory.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/Object.hpp"

namespace SaltyEngine {

	std::map<std::string, Object *> Factory::m_prefabs;
    std::list<std::unique_ptr<Object> > Factory::m_objects;

    Factory::~Factory() {
    }

	Object *Factory::Create()
    {
		m_objects.push_front(Make_unique<GameObject>("GameObject"));
		if (m_objects.front().get() == nullptr)
			Debug::PrintWarning("Factory : could not create game object");
		return m_objects.front().get();
    }

    Object  *Factory::Create(std::string const &name, Vector const& pos, float rot) {
		if (m_prefabs.find(name) == m_prefabs.end()) {
            Debug::PrintWarning("Cannot find prefab [" + name + "]");
			return nullptr;
		} else {
            m_objects.push_front(m_prefabs[name]->CloneMemberwise());
        }
		if (m_objects.front().get() != nullptr)
		{
			GameObject *go = static_cast<GameObject*>(m_objects.front().get());
			go->transform.position = pos;
			go->transform.rotation = rot;
		}
        return m_objects.front().get();
    }

	bool Factory::LoadAsset(std::string const& path)
	{
        static Asset::ASSET_LOADER loader;

        if (loader.Load(path) == nullptr)
        {
            std::cerr << "Factory: failed to load asset at path [" << path << "]. Error was: ";
            perror("");
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
