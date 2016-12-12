#include <SaltyEngine/Animation.hpp>
#include "Prefabs/Player/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Input/InputManager.hpp"
#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/SFML.hpp"
#include "Rtype/Game/Client/GameManager.hpp"

namespace SaltyEngine
{
	PlayerController::PlayerController(GameObject* const gameObj) : SaltyBehaviour("PlayerController", gameObj) {
		speed = 20.0f;
	};

	PlayerController::PlayerController(const std::string &name, GameObject* const gameObj) : SaltyBehaviour(name, gameObj) {
		speed = 20.0f;
	};

	void PlayerController::Start()
	{
		InputKey::AddAxis("Horizontal", new Input::Axis(
				{
						{Input::KeyCode::Left, -1},
						{Input::KeyCode::Right, 1},
						{Input::KeyCode::Q, -1},
						{Input::KeyCode::D, 1}
				},
				std::make_pair<unsigned int, Input::MotionController::Axis>(0, Input::MotionController::X)
		));
		InputKey::AddAxis("Vertical", new Input::Axis(
				{
						{Input::KeyCode::Up, -1},
						{Input::KeyCode::Down, 1},
						{Input::KeyCode::Z, -1},
						{Input::KeyCode::S, 1}
				},
				std::make_pair<unsigned int, Input::MotionController::Axis>(0, Input::MotionController::Y)
		));

		InputKey::AddAction("Fire", new Input::Action(Input::KeyCode::Space, std::make_pair<unsigned int, int>(0, 1)));

        GameObject *gameman = SaltyEngine::Instance().GetCurrentScene()->FindByName("GameManager");

        if (gameman)
            manager = gameman->GetComponent<GameManager>();
	}

	void PlayerController::FixedUpdate()
	{
		float h = InputKey::GetAxis("Horizontal");
		float v = InputKey::GetAxis("Vertical");
		if (h != 0 || v != 0) {
			gameObject->transform.Translate(Vector(h, v) * speed);
            if (manager && BINARY_ROLE == NetRole::CLIENT)
            {
                //todo fix object id parce que la flemme depuis le début du projet. #victorQuiRage
                manager->SendPackage<MOVEPackageGame>(
                        &Network::Core::BasicConnection::SendData<MOVEPackageGame>,
                        gameObject->transform.position.x,
                        gameObject->transform.position.y,
                        manager->gameObjectContainer.GetServerObjectID(gameObject));
                //                manager->SendInput("Horizontal", h);
                //                manager->SendInput("Vertical", v);
            }
		}

		if (InputKey::GetAction("Fire", Input::ActionType::Once)) {
			GameObject *laser = (GameObject*)::SaltyEngine::Instantiate("Laser", gameObject->transform.position);
			//*Singleton<::SaltyEngine::SaltyEngine>::Instance().GetCurrentScene() << laser;
		}
	}
}


