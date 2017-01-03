#include <SaltyEngine/AAssetManager.hpp>
#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/Factory.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/Object.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "Common/Debug.hpp"

namespace SaltyEngine {

    Factory::Factory() {

    }

    Factory::~Factory() {
        Clear();
        while (!m_loaders.empty())
        {
            m_loaders.top()->Unload();
            m_loaders.pop();
        }
    }

	Object *Factory::Create()
    {
		m_objects.push_front(Make_unique<GameObject>("GameObject"));
		if (m_objects.front().get() == nullptr)
			Debug::PrintWarning("Factory : could not create game object");
		std::cout << &Engine::Instance() << std::endl;
        *Engine::Instance().GetCurrentScene() << static_cast<GameObject*>(m_objects.front().get());
		return m_objects.front().get();
    }

    Object  *Factory::Create(std::string const &name, Vector const& pos, float rot) {

        if (m_prefabs.find(name) == m_prefabs.end()) {
            Debug::PrintWarning("Cannot find prefab [" + name + "]");
            m_objects.push_front(std::unique_ptr<Object>(new GameObject("EmptyGameObject(Clone)")));
            GameObject *go = static_cast<GameObject*>(m_objects.front().get());
            go->transform.SetPosition(pos);
            go->transform.SetRotation(rot);
            *Engine::Instance().GetCurrentScene() << static_cast<GameObject*>(m_objects.front().get());
			return m_objects.front().get();
		}
        m_objects.push_front(m_prefabs[name]->CloneMemberwise());
		if (m_objects.front().get() != nullptr)
		{
			GameObject *go = static_cast<GameObject*>(m_objects.front().get());
            go->transform.SetPosition(pos);
            go->transform.SetRotation(rot);
        }
        *Engine::Instance().GetCurrentScene() << static_cast<GameObject*>(m_objects.front().get());
        return m_objects.front().get();
    }

	Asset::ASSET_LOADER *Factory::LoadAsset(std::string const& path)
	{
        Asset::ASSET_LOADER *loader = new Asset::ASSET_LOADER();

        if (loader->Load(path) == nullptr)
        {
            std::string error;
#ifndef _WIN32
            error = dlerror();
#endif
            Debug::PrintError("Factory: failed to load asset at path [" + path + "]. Error was: " + error);
			perror("");
            delete(loader);
            return nullptr;
        }
        Object *obj = (GameObject*)(loader->Call("GetObjectPrefab"));
        if (obj == nullptr)
        {
            Debug::PrintError("Factory: failed to get asset.");
            loader->Unload();
            delete(loader);
            return nullptr;
        }
        if (m_prefabs.find(obj->GetName()) != m_prefabs.end())
        {
            Debug::PrintInfo("Prefab [" + obj->GetName() + "] already in prefab list.");
            loader->Unload();
            delete(loader);
            return nullptr;
        }
        m_prefabs[obj->GetName()] = std::unique_ptr<Object>(obj);
        Debug::PrintSuccess("Factory: loaded [" + obj->GetName() + "]");
        m_loaders.emplace(loader);
		return loader;
	}
}

SaltyEngine::GameObject *SaltyEngine::Factory::Find(std::string const &name)
{
    std::list<std::unique_ptr<Object>>::iterator it = std::find_if(m_objects.begin(), m_objects.end(),
                                                                   [&](const std::unique_ptr<Object> &obj)
                                                                   {
                                                                       std::cout << obj.get()->GetName() << std::endl;
                                                                       return obj.get()->GetName() == name &&
                                                                               dynamic_cast<GameObject*>(obj.get())->GetActiveSelf();
                                                                   });

    if (it == m_objects.end())
        return nullptr;
    return dynamic_cast<GameObject*>((*it).get());
}

SaltyEngine::GameObject *SaltyEngine::Factory::FindHide(std::string const &name)
{
    std::list<std::unique_ptr<Object>>::iterator it = std::find_if(m_objects.begin(), m_objects.end(),
                                                                   [&](const std::unique_ptr<Object> &obj)
                                                                   {
                                                                       return obj.get()->GetName() == name;
                                                                   });

    if (it == m_objects.end())
        return nullptr;
    return dynamic_cast<GameObject*>((*it).get());
}

SaltyEngine::GameObject *SaltyEngine::Factory::FindByTag(Layer::Tag tag)
{
    std::list<std::unique_ptr<Object>>::iterator it = std::find_if(m_objects.begin(), m_objects.end(),
                                                                   [&](const std::unique_ptr<Object> &obj)
                                                                   {
                                                                       GameObject *go = dynamic_cast<GameObject*>(obj.get());
                                                                       if (go != nullptr)
                                                                       {
                                                                           return go->GetTag() == tag &&
                                                                                  go->GetActiveSelf();
                                                                       }
                                                                       return false;
                                                                   });
    if (it == m_objects.end())
        return nullptr;
    return dynamic_cast<GameObject*>((*it).get());
}

std::vector<SaltyEngine::GameObject *> SaltyEngine::Factory::FindAllByTag(Layer::Tag tag)
{
    std::vector<GameObject *> objs;
    GameObject *go = nullptr;

    for (std::list<std::unique_ptr<Object>>::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        if ((go = dynamic_cast<GameObject*>(it->get())) != nullptr)
        {
            if (go->CompareTag(tag) && go->GetActiveSelf())
                objs.push_back(go);
        }
    }
    return objs;
}

void SaltyEngine::Factory::Clear()
{
    m_prefabs.clear();
    m_objects.clear();
}