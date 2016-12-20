//
// Created by nicolas-constanty on 18/12/16.
//

#include <SaltyEngine/GameObject.hpp>
#include "TestCollision.hpp"
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/Input.hpp"
#include "Common/Debug.hpp"

TestCollision::TestCollision(SaltyEngine::GameObject *gameObj) : SaltyBehaviour(gameObj) {}

TestCollision::TestCollision(const string &name, SaltyEngine::GameObject *gameObj) : SaltyBehaviour(name, gameObj) {}

void TestCollision::Start() {
    InputKey::AddAxis("Horizontal", new SaltyEngine::Input::Axis(
            {
                    {SaltyEngine::Input::KeyCode::Left, -1},
                    {SaltyEngine::Input::KeyCode::Right, 1},
                    {SaltyEngine::Input::KeyCode::Q, -1},
                    {SaltyEngine::Input::KeyCode::D, 1}
            },
            std::make_pair<unsigned int, SaltyEngine::Input::MotionController::Axis>(0, SaltyEngine::Input::MotionController::X)
    ));
    InputKey::AddAxis("Vertical", new SaltyEngine::Input::Axis(
            {
                    {SaltyEngine::Input::KeyCode::Up, -1},
                    {SaltyEngine::Input::KeyCode::Down, 1},
                    {SaltyEngine::Input::KeyCode::Z, -1},
                    {SaltyEngine::Input::KeyCode::S, 1}
            },
            std::make_pair<unsigned int, SaltyEngine::Input::MotionController::Axis>(0, SaltyEngine::Input::MotionController::Y)
    ));
}

void TestCollision::OnCollisionEnter(SaltyEngine::ICollider *collider) {
    Debug::PrintInfo("Enter");
}

void TestCollision::OnCollisionStay(SaltyEngine::ICollider *collider) {
    Debug::PrintSuccess("Stay");
}

void TestCollision::FixedUpdate() {
    float h = InputKey::GetAxis("Horizontal");
    float v = InputKey::GetAxis("Vertical");
    if (h != 0 || v != 0) {
        gameObject->transform.Translate(SaltyEngine::Vector(h, v) * 8);
    }
}

void TestCollision::OnCollisionExit(SaltyEngine::ICollider *collider) {
    Debug::PrintInfo("Exit");
}
