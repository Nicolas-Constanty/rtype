#include <SaltyEngine/SFML/Animation.hpp>
//#include <Prefabs/Missile/Laser/LaserController.hpp>
#include "Prefabs/Player/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/SFML.hpp"
#include <Prefabs/Pod/PodController.hpp>
#include <Prefabs/Missile/Laser/LaserController.hpp>

namespace SaltyEngine
{
	PlayerController::PlayerController(GameObject* const gameObj) : AGenericController("PlayerController", gameObj) {
		speed = 20.0f;
        idShot = 1;
        power = 0;
        beamShot = NULL;
        playerID = 0;
        pod = NULL;
        highScore = 0;
	};

	PlayerController::PlayerController(const std::string &name, GameObject* const gameObj) : AGenericController(name, gameObj) {
		speed = 20.0f;
        idShot = 1;
        power = 0;
        beamShot = NULL;
        playerID = 0;
        pod = NULL;
        highScore = 0;
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

        InputKey::AddAction("Pod", new Input::Action(Input::KeyCode::LShift, std::make_pair<unsigned int, int>(0, 2))); //todo koi t'est-ce qui fo fer

        // Beam SFX for the player
        if (!isServerSide())
        {
            m_beamSFX = (GameObject*)Instantiate();
            m_beamSFX->AddComponent<SFML::SpriteRenderer>(SFML::AssetManager::Instance().GetSprite("Laser/loading1"), Layout::normal);
            m_beamSFX->AddComponent<SFML::SpriteCollider2D>();
            m_beamSFX->transform.position = (this->gameObject->transform.position + Vector(30, 3));
            SaltyEngine::SFML::Animation *animation = m_beamSFX->AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
            animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Laser/loading"), "Loading");
            m_beamSFX->transform.SetParent(&this->gameObject->transform);
            m_beamSFX->SetActive(false);
        }
	}

	void PlayerController::FixedUpdate()
	{
        static int i = 0;
		float h = InputKey::GetAxis("Horizontal");
		float v = InputKey::GetAxis("Vertical");
		if (h != 0 || v != 0) {
			gameObject->transform.Translate(Vector(h, v) * speed);
		}

        if (!isServerSide() && i % 3 == 0)
        {
            SendPackage<MOVEPackageGame>(
                    gameObject->transform.position.x,
                    gameObject->transform.position.y,
                    getManager()->gameObjectContainer.GetServerObjectID(gameObject));
        }
        ++i;
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
                OnBeamAction();
                std::cout << "ID DOWN==" << getManager()->gameObjectContainer.GetServerObjectID(gameObject) << std::endl;
                SendPackage<BEAMPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject), idShot);
                m_beamSFX->SetActive(true);
            }
        }
        if (InputKey::GetAction("Fire", Input::ActionType::Up)) {
            //manager->gameObjectContainer.Add(GameObjectID::NewID(), laser);

            if (!isServerSide()) {
                std::cout << "ID UP==" << getManager()->gameObjectContainer.GetServerObjectID(gameObject) << std::endl;
                SendPackage<SHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject), power, idShot++);
                m_beamSFX->SetActive(false);

                SaltyEngine::GameObject *gameObject1 = dynamic_cast<SaltyEngine::GameObject *>(::SaltyEngine::Instantiate("Laser", gameObject->transform.position));
                int power = OnShotAction();
                LaserController *laserController = gameObject1->GetComponent<LaserController>();
                if (laserController) {
                    std::cout << "SET" << std::endl;
                    laserController->Power(power);
                }
            }
        }

        if (InputKey::GetAction("Pod", Input::ActionType::Down))
        {
            if (!isServerSide())
            {
                if (pod)
                {
                    SendPackage<LAUNCHPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(pod->gameObject), playerID);
                }
                else
                {
                    PodController   *tocall = FindFirstAvailablePod();

                    SendPackage<CALLPackageGame>(
                            getManager()->gameObjectContainer.GetServerObjectID(tocall->gameObject),
                            gameObject->transform.position.x,
                            gameObject->transform.position.y);
                }
            }
        }
	}

    void PlayerController::OnBeamAction() {
//        if (isServerSide()) {
            start = clock::now();
//            std::cout << "init beam" << std::endl;
//        }
    }

    int     PlayerController::OnShotAction() {
//        if (isServerSide()) {

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

//            std::cout << "ici" << std::endl;
//            GameObject *laser = dynamic_cast<GameObject *>(::SaltyEngine::Instantiate("Laser", gameObject->transform.position));
//            std::cout << "la" << std::endl;
//            laser->GetComponent<LaserController>()->Power(power);

            return (power);
//            std::cout << "et la" << std::endl;
//            if (laser) {
//                InformationPlayerShot *informationPlayerShot = new InformationPlayerShot();
//                informationPlayerShot->power = power;
//                informationPlayerShot->laser = laser;
//                informationPlayerShot->laserString = laserString;
//                std::cout << "power => " << informationPlayerShot->power << std::endl;

//                if (beamShot && isServerSide()) {
//                    BroadcastPackage<DIEPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(beamShot));
//                    SaltyEngine::Object::Destroy(beamShot);
//                    beamShot = NULL;
//                }
//
//                std::cout << "et par ici" << std::endl;
//                return  informationPlayerShot;
//            }
//        }
//        return NULL;
//        return (1);
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

    bool PlayerController::Attach(PodController *toattach)
    {
        if (pod)
            return false;
        pod = toattach;
        return true;
    }

    bool PlayerController::Launch()
    {
        if (pod)
        {
            bool res = pod->Launch();
            if (res)
                pod = NULL;
            return res;
        }
        return false;
    }

    bool PlayerController::Call()
    {
        if (!pod)
        {
            pod = FindFirstAvailablePod();
            if (pod)
                return pod->Call(gameObject->transform.position);
        }
        return false;
    }

    bool PlayerController::HasPod() const
    {
        return pod != NULL;
    }

    PodController *PlayerController::FindFirstAvailablePod()
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

    void PlayerController::SetColor(unsigned char color) {

        std::string anim;

        anim = "SpaceShip/SpaceShip" + std::to_string(color) + "-1";
        std::cout << "PLAYER COLOR == " << anim << std::endl;
        gameObject->GetComponent<::SaltyEngine::SFML::SpriteRenderer>()->SetSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(anim));
    }

    void PlayerController::SetHighScore(int highScore) {
        this->highScore = highScore;
    }

    int PlayerController::GetHighScore() const {
        return (this->highScore);
    }

}