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
    const float    PlayerController::timeoutDeath = 3; // 3 second
    const float    PlayerController::timeoutInvicible = 3;

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
						{Input::KeyCode::Left, -1.0f},
						{Input::KeyCode::Right, 1.0f },
						{Input::KeyCode::Q, -1.0f },
						{Input::KeyCode::D, 1.0f }
				},
				std::make_pair<unsigned int, Input::MotionController::Axis>(0, Input::MotionController::X)
		));
		InputKey::AddAxis("Vertical", new Input::Axis(
				{
						{Input::KeyCode::Up, -1.0f },
						{Input::KeyCode::Down, 1.0f },
						{Input::KeyCode::Z, -1.0f },
						{Input::KeyCode::S, 1.0f }
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
            SFML::Renderer *renderer = dynamic_cast<SFML::Renderer *>(Engine::Instance().GetRenderer());
            SFML::SpriteRenderer *sprr = gameObject->GetComponent<SFML::SpriteRenderer>();
            if (renderer)
            {
                m_min = Vector2(
                        sprr->GetSprite()->getTextureRect().width / 2,
                        sprr->GetSprite()->getTextureRect().height / 2
                );
                std::cout << m_min << std::endl;
                m_max = Vector2(
                        renderer->getSize().x / gameObject->transform.GetLocalScale().x - m_min.x,
                        renderer->getSize().y / gameObject->transform.GetLocalScale().y - m_min.y
                );
                std::cout << m_max << std::endl;
            }
        }
        common = gameObject->GetComponent<CommonPlayerController>();
        std::cout << "Common: " << common << std::endl;
	}

	void PlayerController::FixedUpdate()
	{
        if (common->isDead())
            return;

		float h = InputKey::GetAxis("Horizontal");
		float v = InputKey::GetAxis("Vertical");
        Vector2 move(gameObject->transform.GetPosition().x + h  * speed, gameObject->transform.GetPosition().y + v * speed);
		if (!isServerSide()
            && (h != 0 || v != 0)
            && move.x < m_max.x && move.x > m_min.x
            && move.y < m_max.y && move.y > m_min.y) {
			gameObject->transform.Translate(Vector(h, v) * speed);
                SendPackage<MOVEPackageGame>(
                        gameObject->transform.GetPosition().x,
                        gameObject->transform.GetPosition().y,
                        getManager()->gameObjectContainer.GetServerObjectID(gameObject));
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
            if (!isServerSide())
            {
                if (handler->HasPod())
                {
                    SendPackage<LAUNCHPackageGame>(
                            getManager()->gameObjectContainer.GetServerObjectID(handler->getPod()->gameObject),
                            getManager()->gameObjectContainer.GetServerObjectID(gameObject));
                }
                else
                {
                    PodController   *tocall = handler->FindFirstAvailablePod();

                    if (tocall)
                        SendPackage<CALLPackageGame>(
                                getManager()->gameObjectContainer.GetServerObjectID(tocall->gameObject),
                                getManager()->gameObjectContainer.GetServerObjectID(gameObject));
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
        handler->Shot();
        return (power);
    }

    unsigned int PlayerController::GetIDShot() const {
        return idShot;
    }

    void PlayerController::TakeDamage(int amount) {
        AGenericController::TakeDamage(amount);

        if (isServerSide() && m_health <= 0)
        {
            common->Die();
        }
    }

    void PlayerController::Move() {
        // TODO
    }

    void PlayerController::Shot() {

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
        m_renderer = gameObject->GetComponent<::SaltyEngine::SFML::SpriteRenderer>();
        m_renderer->SetSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(anim));

        // invincibility animation
        m_anim = this->gameObject->AddComponent<SaltyEngine::SFML::Animation>(false, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        SaltyEngine::SFML::AnimationClip *clip = new SaltyEngine::SFML::AnimationClip("Invincibility", 4, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(anim));
        clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(anim));
        clip->AddEvent([this](){ m_renderer->SetColor(SaltyEngine::Color(1, 1, 1, 0)); }, 0);
        clip->AddEvent([this](){ m_renderer->SetColor(SaltyEngine::Color(1, 1, 1, 1)); }, 1);
        m_anim->AddClip(clip, "Invincibility");
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

    void PlayerController::OnEnable() {
        if (m_anim && common->GetStatus() == CommonPlayerController::Status::INVINCIBLE)
            m_anim->Play("Invincibility");
    }

    void PlayerController::SetHealth(int health) {
        AGenericController::SetHealth(health);
        if (m_anim) {
            m_anim->Stop("Invincibility");
            m_renderer->SetColor(SaltyEngine::Color(1, 1, 1));
        }
    }

//    void PlayerController::Reborn()
//    {
//        collider2D->SetEnable(false);
//        gameObject->SetActive(true);
//        timer = timeoutInvicible;
//    }

}
