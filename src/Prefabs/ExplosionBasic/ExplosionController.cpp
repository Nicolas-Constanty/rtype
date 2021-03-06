#include "Prefabs/ExplosionBasic/ExplosionController.hpp"
#include "SaltyEngine/SFML.hpp"

ExplosionController::ExplosionController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
}

void ExplosionController::Start() {
    SaltyEngine::SFML::Animation *animation = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
    if (animation)
    {
        SaltyEngine::SFML::AnimationClip *clip = animation->GetClip(0);
        if (clip)
        {
            clip->AddEvent([&](){ SaltyEngine::Object::Destroy(gameObject); });
        }
    }
}

ExplosionController::~ExplosionController()
{
}