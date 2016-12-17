
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include "SaltyEngine/GameObject.hpp"
#include "Prefabs/Missile/MissileController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

MissileController::MissileController(SaltyEngine::GameObject *go) : RtypePrefab("MissileController", go)//: SaltyEngine::SaltyBehaviour(go)
{
//    gameServer = NULL;
}


MissileController::~MissileController()
{
}

void MissileController::Start() {
    LoadManager();
    if (!isServerSide()) {
        SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
        fire->Play();
    }

//    if (missileController != nullptr) {
        this->SetTarget(SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player));

    if (isServerSide()) {
        BroadCastReliable<CREATEPackageGame>(
                gameObject->transform.position.x,
                gameObject->transform.position.y,
                RtypeNetworkFactory::GetIDFromName("MissileMedusa"),
                getManager()->gameObjectContainer.GetServerObjectID(gameObject),
                gameObject->transform.rotation);
    }

//    SaltyEngine::GameObject *gameman = SaltyEngine::Engine::Instance().GetCurrentScene()->FindByName("GameServer");
//    if (gameman)
//        gameServer = gameman->GetComponent<Rtype::Game::Server::GameServerObject>();
}

void MissileController::FixedUpdate()
{
    Move();
}

void MissileController::SetTarget(SaltyEngine::GameObject const* target)
{
    if (target != nullptr)
    {
        gameObject->transform.LookAt(target->transform);
    }
}

void MissileController::Move() {
//    if (isServerSide()) {
        gameObject->transform.Translate(
                gameObject->transform.right() * m_vel * SaltyEngine::Engine::Instance().GetFixedDeltaTime());
//        BroadcastPackage<MOVEPackageGame>(
//                gameObject->transform.position.x,
//                gameObject->transform.position.y,
//                getManager()->gameObjectContainer.GetServerObjectID(gameObject));
//    }
}
