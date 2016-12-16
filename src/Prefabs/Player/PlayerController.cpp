#include <SaltyEngine/SFML/Animation.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include <Prefabs/Missile/Laser/LaserController.hpp>
#include "Prefabs/Player/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Input/InputManager.hpp"
#include "SaltyEngine/Constants.hpp"
#include "SaltyEngine/SFML.hpp"
#include "Rtype/Game/Client/GameManager.hpp"

namespace SaltyEngine
{
	PlayerController::PlayerController(GameObject* const gameObj) : AGenericController("PlayerController", gameObj) {
		speed = 20.0f;
        idShot = 1;
        power = 0;
        beamShot = NULL;
        playerID = 0;
	};

	PlayerController::PlayerController(const std::string &name, GameObject* const gameObj) : AGenericController(name, gameObj) {
		speed = 20.0f;
        idShot = 1;
        power = 0;
        beamShot = NULL;
        playerID = 0;
	};

	void PlayerController::Start()
	{
        LoadManager();
        beamShot = NULL;
        start = clock::now();
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

//        GameObject *gameman = Engine::Instance().GetCurrentScene()->FindByName("GameManager");
//
//        manager = NULL;
//        if (gameman)
//            manager = gameman->GetComponent<GameManager>();
	}

	void PlayerController::FixedUpdate()
	{
		float h = InputKey::GetAxis("Horizontal");
		float v = InputKey::GetAxis("Vertical");
		if (h != 0 || v != 0) {
			gameObject->transform.Translate(Vector(h, v) * speed);
            if (!isServerSide())
            {
                SendPackage<MOVEPackageGame>(
                        gameObject->transform.position.x,
                        gameObject->transform.position.y,
                        getManager()->gameObjectContainer.GetServerObjectID(gameObject));
            }
		}
        if (isServerSide()) {
            if (beamShot) {
                beamShot->transform.position = gameObject->transform.position;
                beamShot->transform.position.x += 30;
                BroadcastPackage<MOVEPackageGame>(
                        beamShot->transform.position.x,
                        beamShot->transform.position.y,
                        getManager()->gameObjectContainer.GetServerObjectID(beamShot));
            }
        }

        if (InputKey::GetAction("Fire", Input::ActionType::Down)) {
            if (!isServerSide()) {
                SendPackage<BEAMPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject), idShot);
            }
        }
        if (InputKey::GetAction("Fire", Input::ActionType::Up)) {
            //GameObject *laser = (GameObject*)::SaltyEngine::Instantiate("Laser", gameObject->transform.position);

            //manager->gameObjectContainer.Add(GameObjectID::NewID(), laser);
            if (!isServerSide()) {
                SendPackage<SHOTPackageGame>(
                        getManager()->gameObjectContainer.GetServerObjectID(gameObject), power, idShot++);
            }
        }
	}

    void PlayerController::OnBeamAction() {
        if (isServerSide()) {
            start = clock::now();
            std::cout << "init beam" << std::endl;
        }
    }

    InformationPlayerShot *PlayerController::OnShotAction() {
        if (isServerSide()) {

            int power = 1;

            std::string laserString;
            double tick = mticks();

            tick = tick > 1000 ? 1000 : tick;

            if (tick == 1000) {
                power = 5;
            } else if (tick >= 750) {
                power = 4;
            } else if (tick >= 500) {
                power = 3;
            } else if (tick >= 250) {
                power = 2;
            }

            GameObject *laser = dynamic_cast<GameObject *>(::SaltyEngine::Instantiate("Laser", gameObject->transform.position));
            laser->GetComponent<LaserController>()->Power(power);

            if (laser) {
                InformationPlayerShot *informationPlayerShot = new InformationPlayerShot();
                informationPlayerShot->power = power;
                informationPlayerShot->laser = laser;
                informationPlayerShot->laserString = laserString;
//                std::cout << "power => " << informationPlayerShot->power << std::endl;

                if (beamShot && isServerSide()) {
                    BroadcastPackage<DIEPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(beamShot));
                    SaltyEngine::Object::Destroy(beamShot);
                    beamShot = NULL;
                }

                return  informationPlayerShot;
            }
        }
        return NULL;
    }

    unsigned int PlayerController::GetIDShot() const {
        return idShot;
    }

    void PlayerController::Die() const {
        std::cout << "Player Died !" << std::endl;
    }

    void PlayerController::Move() {
        // TODO
    }

    void PlayerController::Shot() {
        // TODO
    }

    void PlayerController::Beam() {
//        Vector pos = Vector(gameObject->transform.position.x + 30, gameObject->transform.position.y);
//        beamShot = dynamic_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate("Beam", pos));
        std::cout << "BEAM" << std::endl;
    }

    int PlayerController::GetPlayerID() const {
        return (playerID);
    }

    void PlayerController::SetPlayerID(int id) {
        this->playerID = id;
        std::cout << "setting playerID == " << id << std::endl;
    }
}