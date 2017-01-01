//
// Created by gaspar_q on 12/12/16.
//

#ifndef RTYPE_MATECOMPONENT_HPP
#define RTYPE_MATECOMPONENT_HPP

#include <SaltyEngine/SaltyBehaviour.hpp>
#include <Prefabs/RtypePrefab.hpp>
#include <Prefabs/CommonPlayer/CommonPlayerController.hpp>

class PREF_EXPORT MateComponent : public RtypePrefab
{
public:
    explicit MateComponent(SaltyEngine::GameObject *const object);
    MateComponent(const std::string &name, SaltyEngine::GameObject* const gamObj);
    virtual ~MateComponent();

public:
    void SetColor(int color);
    void Start();
    void OnCollisionEnter(SaltyEngine::ICollider *collider);
    void SetBeamFXActive(bool active);

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);

public:
//    SaltyEngine::GameObject *m_beamSFX = nullptr;

private:
    CommonPlayerController  *common;
};


#endif //RTYPE_MATECOMPONENT_HPP
