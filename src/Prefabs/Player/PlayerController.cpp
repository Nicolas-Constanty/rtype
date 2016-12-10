#include <SaltyEngine/Animation.hpp>
#include "Prefabs/Player/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Input/InputManager.hpp"
#include "SaltyEngine/SFML.hpp"

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
		::SaltyEngine::SFML::Texture *texture = ::SaltyEngine::SFML::AssetManager::Instance().GetTexture("SpaceShips");
		gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(34, 0, 33, 17)), ::SaltyEngine::Layout::normal);

//    AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
//    SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
//    clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(0, 0, 33, 17)));
//    clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(17, 0, 33, 17)));
//    clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(34, 0, 33, 17)));
//    clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(51, 0, 33, 17)));
//    clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(68, 0, 33, 17)));
//    clip->SetFrameRate(5);
//    GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");

		std::cout << "Je suis le Start, je ne suis appelé qu'une fois" << std::endl;
		//StartCoroutine(&PlayerController::DisplayCoroutine);
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
	}

	void PlayerController::FixedUpdate()
	{
		float h = InputKey::GetAxis("Horizontal");
		float v = InputKey::GetAxis("Vertical");
		if (h != 0 || v != 0) {
			gameObject->transform.Translate(Vector(h, v) * speed);
		}

		if (InputKey::GetAction("Fire", Input::ActionType::Once)) {
			GameObject *laser = (GameObject*)::SaltyEngine::Instantiate("Laser", gameObject->transform.position);
			*Singleton<::SaltyEngine::SaltyEngine>::Instance().GetCurrentScene() << laser;
		}
	}

	void PlayerController::DisplayCoroutine()
	{
		for (;;) {
			Debug::Print("Je suis dans la coroutine");
			WaitForMillisecond(3);
		}
		std::cout << "Je m'affiche apr�s 3 seconde" << std::endl;
	}
}

