//
// Created by gaspar_q on 12/26/16.
//

#include <Prefabs/Bonus/APodBonusController.hpp>
#include <Prefabs/PodHandler/PodHandler.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>

APodBonusController::APodBonusController(std::string const &name, SaltyEngine::GameObject *object) :
        ABonusController(name, object)
{

}

APodBonusController::~APodBonusController()
{

}

void APodBonusController::ExecuteBonus(SaltyEngine::GameObject *object)
{
    PodHandler  *handler = object->GetComponent<PodHandler>();

    if (handler)
    {
        if (handler->HasPod())
        {
            handler->getPod()->Upgrade(getMissile());
        }
        else
        {
            SaltyEngine::GameObject *obj = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Object::Instantiate("Pod", SaltyEngine::Vector2(-100, handler->gameObject->transform.GetPosition().y)));

			if (obj)
			{
				getManager()->gameObjectContainer.Add(GameObjectID::NewID(), obj);
			}
        }
    }
}
