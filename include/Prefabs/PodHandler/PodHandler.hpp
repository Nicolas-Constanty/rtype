//
// Created by gaspar_q on 12/20/16.
//

#ifndef RTYPE_PODHANDLER_HPP
#define RTYPE_PODHANDLER_HPP

#include <Prefabs/RtypePrefab.hpp>
#include <Prefabs/Pod/PodController.hpp>

class PREF_EXPORT PodHandler : public RtypePrefab
{
public:
    PodHandler(SaltyEngine::GameObject *object);
    virtual ~PodHandler();

public:
    virtual void Start();

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);

public:
    bool Attach(PodController *toattach);
    bool Launch();
    bool Call();
    bool Call(PodController *tocall);
    bool HasPod() const;
    bool Shot();
    void UnlinkPod();

public:
    PodController   *getPod() const;

public:
    PodController	*FindFirstAvailablePod();

private:
    PodController	*pod = nullptr;
    PodController   *lastPod = nullptr;
};

#endif //RTYPE_PODHANDLER_HPP
