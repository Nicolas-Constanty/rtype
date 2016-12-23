//
// Created by gaspar_q on 12/20/16.
//

#include <SaltyEngine/GameObject.hpp>
#include <Prefabs/RtypePrefab.hpp>
#include <Prefabs/PodHandler/PodHandler.hpp>
#include <Prefabs/Missile/Laser/LaserController.hpp>

PodHandler::PodHandler(SaltyEngine::GameObject *object) :
        RtypePrefab("PodHandler", object),
        pod(nullptr)
{

}

PodHandler::~PodHandler()
{

}

void PodHandler::Start()
{
    LoadManager();
//    pod = gameObject->GetComponent<PodController>();
}

bool PodHandler::Attach(PodController *toattach)
{
    std::cout << "Call attach: " << pod << std::endl;
    if (pod)
    {
        std::cout << "I alreay have a pod" << std::endl;
        return false;
    }
    lastPod = nullptr;
    pod = toattach;
    return true;
}

bool PodHandler::Launch()
{
    if (pod)
    {
        bool res = pod->Launch();

        std::cout << std::boolalpha << "Res: " << res << std::endl;
        if (res)
        {
            std::cout << "Resetting pod" << std::endl;
            lastPod = pod;
            pod = NULL;
        }
        return res;
    }
    return false;
}

bool PodHandler::Call()
{
    return Call(FindFirstAvailablePod());
}

bool PodHandler::Call(PodController *tocall)
{
    if (!pod && tocall)
    {
        return tocall->Call(this);
    }
    return false;
}

bool PodHandler::HasPod() const
{
    return pod != nullptr;
}

PodController *PodHandler::FindFirstAvailablePod()
{
    for (SaltyEngine::GameObject *curr : getManager()->getPods())
    {
        PodController   *podController = curr->GetComponent<PodController>();

        if (podController && !podController->isAttached())
        {
            return podController;
        }
    }
    return nullptr;
}

PodController *PodHandler::getPod() const
{
    return pod;
}

SaltyEngine::Component *PodHandler::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new PodHandler(obj);
}

bool PodHandler::Shot()
{
    if (lastPod)
    {
        if (isServerSide())
        {
            SendPackage<SHOTPackageGame>(
                    getManager()->gameObjectContainer.GetServerObjectID(lastPod->gameObject), 1, 0,
                    lastPod->gameObject->transform.GetPosition().x, lastPod->gameObject->transform.GetPosition().y
            );
        }
        SaltyEngine::Instantiate("Laser", lastPod->gameObject->transform.GetPosition());
    }
    return false;
}

void PodHandler::UnlinkPod()
{
    lastPod = nullptr;
    pod = nullptr;
}
