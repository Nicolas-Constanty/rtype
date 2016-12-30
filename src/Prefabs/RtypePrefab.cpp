//
// Created by gaspar_q on 12/15/16.
//

#include <Prefabs/RtypePrefab.hpp>

/**
 * @brief Abstract Prefab basic constructor
 * @param gameObject The gameobject related to the behaviour
 */
RtypePrefab::RtypePrefab(std::string const &name, SaltyEngine::GameObject *gameObject) :
        SaltyEngine::SaltyBehaviour(name, gameObject),
        m_manager(NULL)
{

}

/**
 * @brief Basic destructor
 */
RtypePrefab::~RtypePrefab()
{

}

void RtypePrefab::LoadManager()
{
    SaltyEngine::GameObject *obj = SaltyEngine::GameObject::Find("GameManager");

    if (obj)
        m_manager = obj->GetComponent<GameManager>();
    else
        throw std::runtime_error("Manager not found in scene");
}

bool RtypePrefab::isServerSide() const
{
    return m_manager && m_manager->isServerSide();
}

GameManager *RtypePrefab::getManager()
{
    if (!m_manager)
    {
        LoadManager();
    }
    return m_manager;
}

void RtypePrefab::PlayNewBackgroundSound(std::string const &sound) {
    if (m_manager)
        m_manager->PlaySound(sound);
}
