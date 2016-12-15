#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/Factory.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/SaltyEngine.hpp"

namespace SaltyEngine {

    Factory::Factory() {

    }

    Factory::~Factory() {
    }

	Object *Factory::Create()
    {
		m_objects.push_front(Make_unique<GameObject>("GameObject"));
		if (m_objects.front().get() == nullptr)
			Debug::PrintWarning("Factory : could not create game object");
        *Singleton<::SaltyEngine::Engine>::Instance().GetCurrentScene() << static_cast<GameObject*>(m_objects.front().get());
		return m_objects.front().get();
    }

    Object  *Factory::Create(std::string const &name, Vector const& pos, float rot) {
		if (m_prefabs.find(name) == m_prefabs.end()) {
            Debug::PrintWarning("Cannot find prefab [" + name + "]");
            m_objects.push_front(std::unique_ptr<Object>(new GameObject("EmptyGameObject(Clone)")));
            GameObject *go = static_cast<GameObject*>(m_objects.front().get());
            go->transform.position = pos;
            go->transform.rotation = rot;
            //*Singleton<::SaltyEngine::Engine>::Instance().GetCurrentScene() << static_cast<GameObject*>(m_objects.front().get());
			return m_objects.front().get();
		}
        m_objects.push_front(m_prefabs[name]->CloneMemberwise());
		if (m_objects.front().get() != nullptr)
		{
			GameObject *go = static_cast<GameObject*>(m_objects.front().get());
			go->transform.position = pos;
			go->transform.rotation = rot;
		}
        *Singleton<::SaltyEngine::Engine>::Instance().GetCurrentScene() << static_cast<GameObject*>(m_objects.front().get());
        return m_objects.front().get();
    }

	bool Factory::LoadAsset(std::string const& path)
	{
        static Asset::ASSET_LOADER loader;

        if (loader.Load(path) == nullptr)
        {
            std::string error;
#ifndef _WIN32
            error = dlerror();
#endif
            Debug::PrintError("Factory: failed to load asset at path [" + path + "]. Error was: " + error);
			perror("");
            return false;
        }
        Object *obj = (GameObject*)(loader.Call("GetObjectPrefab"));
        if (obj == nullptr)
        {
            Debug::PrintError("Factory: failed to get asset.");
            return false;
        }
        if (m_prefabs.find(obj->GetName()) != m_prefabs.end())
        {
            Debug::PrintWarning("Prefab [" + obj->GetName() + "] already in prefab list.");
            return false;
        }
        m_prefabs[obj->GetName()] = std::unique_ptr<Object>(obj);
        Debug::PrintSuccess("Factory: loaded [" + obj->GetName() + "]");
        //loader.Unload();
		return true;
	}
}

SaltyEngine::GameObject *SaltyEngine::Factory::Find(std::string const &name)
{
    std::list<std::unique_ptr<Object>>::iterator it = std::find_if(m_objects.begin(), m_objects.end(),
                                                                   [&](const std::unique_ptr<Object> &obj)
                                                                   {
                                                                       return obj.get()->GetName() == name;
                                                                   });
    return dynamic_cast<GameObject*>((*it).get());
}

SaltyEngine::GameObject *SaltyEngine::Factory::FindByTag(Layer::Tag tag)
{
    std::list<std::unique_ptr<Object>>::iterator it = std::find_if(m_objects.begin(), m_objects.end(),
                                                                   [&](const std::unique_ptr<Object> &obj)
                                                                   {
                                                                       GameObject *go = dynamic_cast<GameObject*>(obj.get());
                                                                       if (go != nullptr)
                                                                           return go->GetTag() == tag;
                                                                       return false;
                                                                   });
    return dynamic_cast<GameObject*>((*it).get());
}