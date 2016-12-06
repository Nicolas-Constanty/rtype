#include "Missile/MissileMedusa/MissileMedusa.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/Debug.hpp"

MissileMedusa::MissileMedusa() : GameObject("MissileMedusa")
{
	//SaltyEngine::SFML::Texture *texture = new SaltyEngine::SFML::Texture();
	//if (!texture->loadFromFile("../../Assets/Textures/Image.png"))
	//{
	//	SaltyEngine::Debug::PrintError("Failed to load texture");
	//}
	//else
	//{
	//	SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(texture);
	//	this->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);
	//	SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>("WalkAnim", 60);
	//	for (int i = 10; i < 100; ++i)
	//	{
	//		*clip << new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(10 * i, 10 * i, 100, 100));
	//	}
	//	this->AddComponent < SaltyEngine::Animation<sf::Vector2i> >(true, SaltyEngine::AnimationConstants::WrapMode::PING_PONG);
	//	this->GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");
	//}
	//AddComponent<MissileController>();
}


MissileMedusa::~MissileMedusa()
{
}

MISSILEMEDUSA_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new MissileMedusa();
}
