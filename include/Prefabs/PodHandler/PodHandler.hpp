//
// Created by gaspar_q on 12/20/16.
//

#ifndef RTYPE_PODHANDLER_HPP
#define RTYPE_PODHANDLER_HPP

#include <Prefabs/RtypePrefab.hpp>
#include <Prefabs/Pod/PodController.hpp>

class PodHandler : public RtypePrefab
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
    bool HasPod() const;

public:
    PodController   *getPod() const;

public:
    PodController	*FindFirstAvailablePod();

private:
    PodController	*pod;
};

#endif //RTYPE_PODHANDLER_HPP
