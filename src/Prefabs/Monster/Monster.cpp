#include "Prefabs/Monster/Monster.hpp"
#include "Prefabs/Monster/MonsterController.hpp"

/**
 * \brief You can add your properties here
 */
Monster::Monster() : GameObject("Monster")
{
    AddComponent<MonsterController>();
}

Monster::~Monster()
{
}

MONSTER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Monster();
}
