#include "Prefabs/Missile/MissileMedusa/MissileMedusa.hpp"
#include "Prefabs/Missile/MissileController.hpp"
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/Animation.hpp"

MissileMedusa::MissileMedusa() : GameObject("MissileMedusa")
{
	SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("explosion");
	if (texture != nullptr)
	{
		AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326, 100, 65, 65)), SaltyEngine::Layout::normal);
		AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
		SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326, 100, 65, 65)));
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326+65, 100, 65, 65)));
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326+65+65, 100, 65, 65)));
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326+65+65+65, 100, 65, 65)));
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326+65+65+65+65, 100, 65, 65)));
		clip->SetFrameRate(5);
		GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Shoot");
	}
	else
	{
		SaltyEngine::Debug::PrintWarning("MissileMedusa: could not load texture");
	}
	AddComponent<MissileController>();
}


MissileMedusa::~MissileMedusa()
{
}

MISSILEMEDUSA_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new MissileMedusa();
}
