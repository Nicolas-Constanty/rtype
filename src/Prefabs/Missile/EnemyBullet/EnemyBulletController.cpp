#include "SaltyEngine/SFML.hpp"
#include "Prefabs/Missile/EnemyBullet/EnemyBulletController.hpp"

EnemyBulletController::EnemyBulletController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
    gameServer = NULL;
}

void EnemyBulletController::Start() {
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
    fire->Play();
    SaltyEngine::GameObject *t = SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player);
    if (t)
        gameObject->transform.LookAt(t->transform);

    SaltyEngine::GameObject *gameman = SaltyEngine::Engine::Instance().GetCurrentScene()->FindByName("GameServer");
    if (gameman)
        gameServer = gameman->GetComponent<Rtype::Game::Server::GameServerObject>();
}

EnemyBulletController::~EnemyBulletController()
{
}

void EnemyBulletController::FixedUpdate()
{
    if (SaltyEngine::BINARY_ROLE == SaltyEngine::NetRole::SERVER || gameServer) {
        gameObject->transform.Translate(gameObject->transform.right() * m_vel);
        this->gameServer->BroadCastPackage<MOVEPackageGame>(
                &Network::Core::BasicConnection::SendData<MOVEPackageGame>,
                gameObject->transform.position.x,
                gameObject->transform.position.y,
                this->gameServer->Server()->gameObjectContainer.GetServerObjectID(gameObject));
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