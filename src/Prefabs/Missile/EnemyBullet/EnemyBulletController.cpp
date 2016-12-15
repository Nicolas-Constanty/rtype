#include "SaltyEngine/SFML.hpp"
#include "Prefabs/Missile/EnemyBullet/EnemyBulletController.hpp"

EnemyBulletController::EnemyBulletController(SaltyEngine::GameObject *go) :
        RtypePrefab("EnnemyBulletController", go)
{
//    gameServer = NULL;
}

void EnemyBulletController::Start() {
    LoadManager();
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
    fire->Play();
    SaltyEngine::GameObject *t = SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player);
    if (t)
        gameObject->transform.LookAt(t->transform);

//    SaltyEngine::GameObject *gameman = SaltyEngine::Engine::Instance().GetCurrentScene()->FindByName("GameServer");
//    if (gameman)
//        gameServer = gameman->GetComponent<Rtype::Game::Server::GameServerObject>();
}

EnemyBulletController::~EnemyBulletController()
{
}

void EnemyBulletController::FixedUpdate()
{
    if (isServerSide()) {
        gameObject->transform.Translate(gameObject->transform.right() * m_vel);
        BroadcastPackage<MOVEPackageGame>(
//                &Network::Core::BasicConnection::SendData<MOVEPackageGame>,
                gameObject->transform.position.x,
                gameObject->transform.position.y,
                getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
}

void EnemyBulletController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col);
    if (c && c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Destroy)
    {
        SaltyEngine::Object::Destroy(this->gameObject);
    }
}