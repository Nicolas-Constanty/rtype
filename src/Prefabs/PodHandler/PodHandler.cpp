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
}

bool PodHandler::Attach(PodController *toattach)
{
    if (pod)
    {
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

        if (res)
        {
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
    return ((pod && pod->Shot()) || (lastPod && lastPod->Shot()));
}

void PodHandler::UnlinkPod()
{
    lastPod = nullptr;
    pod = nullptr;
}
