//
// Created by gaspar_q on 12/26/16.
//

#include <Prefabs/Bonus/APodBonusController.hpp>
#include <Prefabs/PodHandler/PodHandler.hpp>

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

    std::cout << "Executing pod bonus: " << handler << std::endl;
    if (handler)
    {
        if (handler->HasPod())
        {
            std::cout << "Has pod" << std::endl;
            handler->getPod()->Upgrade();
            // upgrade/set missile
        }
        else
        {
            std::cout << "Instantiating pod" << std::endl;
            SaltyEngine::Object::Instantiate("Pod", SaltyEngine::Vector2(-100, handler->gameObject->transform.GetPosition().y));
            // make pod spawn
        }
    }
}
