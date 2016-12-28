//
// Created by gouet_v on 12/26/16.
//

#include <SaltyEngine/SFML/Animation.hpp>
#include "Prefabs/Block/BlockSimple.hpp"
#include "Prefabs/Block/BlockSimpleController.hpp"
#include "SaltyEngine/SFML.hpp"

BlockSimple::BlockSimple() : GameObject("BlockSimple", SaltyEngine::Layer::Tag::Wall) {
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/WalkL1"), ::SaltyEngine::Layout::normal);
    AddComponent<BlockSimpleController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
//    AddComponent<SaltyEngine::SFML::Animation>();
}

BlockSimple::~BlockSimple() {
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new BlockSimple();
}
