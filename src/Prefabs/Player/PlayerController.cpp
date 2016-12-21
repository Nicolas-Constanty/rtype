#include <SaltyEngine/SFML/Animation.hpp>
//#include <Prefabs/Missile/Laser/LaserController.hpp>
#include "Prefabs/Player/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/SFML.hpp"
#include <Prefabs/Pod/PodController.hpp>
#include <Prefabs/Missile/Laser/LaserController.hpp>
#include <Rtype/Game/Client/GameGUIBeam.hpp>
#include <Prefabs/PodHandler/PodHandler.hpp>

namespace SaltyEngine
{
	PlayerController::PlayerController(GameObject* const gameObj) : AGenericController("PlayerController", gameObj) {
		speed = 8.0f; // 20
        idShot = 1;
        power = 0;
        beamShot = NULL;
        playerID = 0;
        highScore = 0;
        m_health = 1;
	};

	PlayerController::PlayerController(const std::string &name, GameObject* const gameObj) : AGenericController(name, gameObj) {
		speed = 8.0f; // 20
        idShot = 1;
        power = 0;
        beamShot = NULL;
        playerID = 0;
        highScore = 0;
        m_health = 1;
	};

	void PlayerController::Start()
	{
        LoadManager();

        objGUIBeam = SaltyEngine::Engine::Instance().GetCurrentScene()->FindByName("GUIBeam");

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

        handler = gameObject->GetComponent<PodHandler>();
        // Beam SFX for the player
        if (!isServerSide())
        {
            m_beamSFX = (GameObject*)Instantiate();
            m_beamSFX->AddComponent<SFML::SpriteRenderer>(SFML::AssetManager::Instance().GetSprite("Laser/loading1"), Layout::normal);
            m_beamSFX->transform.SetPosition(this->gameObject->transform.GetPosition() + Vector(50, 3));
            SaltyEngine::SFML::Animation *animation = m_beamSFX->AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
            animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Laser/loading"), "Loading");
            m_beamSFX->transform.SetParent(&this->gameObject->transform);
            m_beamSFX->SetActive(false);
        }
	}

	void PlayerController::FixedUpdate()
	{
//        static int i = 0;
		float h = InputKey::GetAxis("Horizontal");
		float v = InputKey::GetAxis("Vertical");
		if (h != 0 || v != 0) {
			gameObject->transform.Translate(Vector(h, v) * speed);
            if (!isServerSide()/* && i % 3 == 0*/)
            {
                SendPackage<MOVEPackageGame>(
                        gameObject->transform.GetPosition().x,
                        gameObject->transform.GetPosition().y,
                        getManager()->gameObjectContainer.GetServerObjectID(gameObject));
            }
//            ++i;
        }

        if (InputKey::GetAction("Fire", Input::ActionType::Down)) {
            if (!isServerSide()) {
                OnBeamAction();
                SendPackage<BEAMPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject), idShot);
                m_beamSFX->SetActive(true);
                if (!isServerSide() && objGUIBeam) {
                    objGUIBeam->GetComponent<GameGUIBeam>()->StartAnimation();
                }
            }
        }
        if (InputKey::GetAction("Fire", Input::ActionType::Up)) {

            if (!isServerSide()) {
                SendPackage<SHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject), power, idShot++);
                m_beamSFX->SetActive(false);

                SaltyEngine::GameObject *gameObject1 = dynamic_cast<SaltyEngine::GameObject *>(::SaltyEngine::Instantiate("Laser", gameObject->transform.GetPosition()));
                int power = OnShotAction();
                LaserController *laserController = gameObject1->GetComponent<LaserController>();
                if (laserController) {
                    laserController->Power(power);
                }

                if (!isServerSide() && objGUIBeam) {
                    objGUIBeam->GetComponent<GameGUIBeam>()->ResetAnimation();
                }
            }
        }

        if (InputKey::GetAction("Pod", Input::ActionType::Down))
        {
            std::cout << "Pod action ok" << std::endl;
            if (!isServerSide())
            {
                std::cout << "Client side" << std::endl;
                if (handler->HasPod())
                {
                    std::cout << "\e[31mSending pod\e[0m" << std::endl;
                    SendPackage<LAUNCHPackageGame>(
                            getManager()->gameObjectContainer.GetServerObjectID(handler->getPod()->gameObject),
                            getManager()->gameObjectContainer.GetServerObjectID(gameObject));
                }
                else
                {
                    PodController   *tocall = handler->FindFirstAvailablePod();

                    std::cout << "\e[31mCalling Pod\e[0m" << std::endl;
                    if (tocall)
                        SendPackage<CALLPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(tocall->gameObject));
                }
            }
        }
	}

    void PlayerController::OnBeamAction() {
        start = clock::now();
    }

    int     PlayerController::OnShotAction() {
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
        return (power);
    }

    unsigned int PlayerController::GetIDShot() const {
        return idShot;
    }

    void PlayerController::Die() {
//        std::cout << "Player Died !" << std::endl;
//        if (isServerSide())
//        {
//            SendPackage<DIEPackageGame>(
//                    getManager()->gameObjectContainer.GetServerObjectID(this->gameObject)
//            );
//        }
//        else
//        {
//            Instantiate("ExplosionBasic", this->gameObject->transform.position);
//        }
//        Destroy(this->gameObject);
    }

    void PlayerController::TakeDamage(int amount) {
        AGenericController::TakeDamage(amount);

        if (m_health <= 0)
        {
            Die();
        }
    }

    void PlayerController::Move() {
        // TODO
    }

    void PlayerController::Shot() {
        // TODO
    }

    void PlayerController::Beam() {
        std::cout << "BEAM" << std::endl;
    }

    int PlayerController::GetPlayerID() const {
        return (playerID);
    }

    void PlayerController::SetPlayerID(int id) {
        this->playerID = id;
    }

    void PlayerController::SetColor(unsigned char color) {

        std::string anim;

        anim = "SpaceShip/SpaceShip" + std::to_string(color) + "-1";
        gameObject->GetComponent<::SaltyEngine::SFML::SpriteRenderer>()->SetSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(anim));
    }

    void PlayerController::SetHighScore(int highScore) {
        if (this->highScore != highScore) {
            updateHighScore = true;
        }
        this->highScore = highScore;
    }

    int PlayerController::GetHighScore() const {
        return (this->highScore);
    }

    bool PlayerController::IsUpdateHighScore() const {
        return updateHighScore;
    }

    void PlayerController::SetUpdateHighScore(bool update) {
        updateHighScore = update;
    }

    void PlayerController::OnCollisionEnter(ICollider *collider)
    {
        SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(collider);

        if (!c)
            return;
        if (c->CompareTag(SaltyEngine::Layer::Tag::Enemy))
        {
            if (isServerSide())
            {
                BroadCastReliable<DEATHPackage>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
                Die();
            }
        }
    }

}