//
// Created by gouet_v on 12/15/16.
//

#ifndef RTYPE_BEAMCONTROLLER_HPP
#define RTYPE_BEAMCONTROLLER_HPP

#include <SaltyEngine/SaltyBehaviour.hpp>
#include <SaltyEngine/ISound.hpp>

class PREF_EXPORT BeamController : public SaltyEngine::SaltyBehaviour
{
public:
    BeamController(SaltyEngine::GameObject *const object);
    virtual ~BeamController();

public:
    void Start();

private:
    SaltyEngine::Sound::ISound *soundLoad;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new BeamController(obj);
    }
};


#endif //RTYPE_BEAMCONTROLLER_HPP
