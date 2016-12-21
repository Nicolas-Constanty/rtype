//
// Created by gaspar_q on 12/20/16.
//

#include <SaltyEngine/GameObject.hpp>
#include <Prefabs/RtypePrefab.hpp>
#include <Prefabs/PodHandler/PodHandler.hpp>

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
    pod = gameObject->GetComponent<PodController>();
}

bool PodHandler::Attach(PodController *toattach)
{
    if (pod)
    {
        std::cout << "I alreay have a pod" << std::endl;
        return false;
    }
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
            pod = NULL;
        }
        return res;
    }
    return false;
}

bool PodHandler::Call()
{
    if (!pod)
    {
        pod = FindFirstAvailablePod();
        if (pod)
            return pod->Call(this);
    }
    return false;
}

bool PodHandler::HasPod() const
{
    std::cout << "Pod: " << pod << std::endl;
    return pod != NULL;
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
