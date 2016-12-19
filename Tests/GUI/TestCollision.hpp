//
// Created by nicolas-constanty on 18/12/16.
//

#ifndef RTYPE_TESTCOLLISION_HPP
#define RTYPE_TESTCOLLISION_HPP

#include "SaltyEngine/SaltyBehaviour.hpp"

class TestCollision : public SaltyEngine::SaltyBehaviour {
public:
    TestCollision(SaltyEngine::GameObject *gameObj);

    TestCollision(const string &name, SaltyEngine::GameObject *gameObj);

    void OnCollisionEnter(SaltyEngine::ICollider *collider) override;

    void OnCollisionStay(SaltyEngine::ICollider *collider) override;

    void OnCollisionExit(SaltyEngine::ICollider *collider) override;

    void FixedUpdate() override;

    void Start() override;

};


#endif //RTYPE_TESTCOLLISION_HPP
