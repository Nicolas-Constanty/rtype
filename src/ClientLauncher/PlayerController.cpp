#include "ClientLauncher/PlayerController.hpp"
#include "SaltyEngine/SFML/EventManager.hpp"
#include "SaltyEngine/Input/InputManager.hpp"

typedef SaltyEngine::Input::InputManager<SaltyEngine::SFML::EventManager>  InputKey;

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
		std::cout << "Je suis le Start, je ne suis appelé qu'une fois" << std::endl;
		StartCoroutine(&PlayerController::DisplayCoroutine);
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

        InputKey::AddAction("Hello", new Input::Action(Input::KeyCode::F, std::make_pair<unsigned int, int>(0, 1)));
	}

	void PlayerController::FixedUpdate()
	{
//		std::cout << "Fixed Update 60 fps" << std::endl;

        float h = InputKey::GetAxis("Horizontal");
        float v = InputKey::GetAxis("Vertical");
        if (h != 0 || v != 0) {
            gameObject->transform.Translate(Vector(h, v) * speed);
        }

        if (InputKey::GetAction("Hello", Input::ActionType::Pressed)) {
            std::cout << "hello" << std::endl;
        }
	}

	void PlayerController::DisplayCoroutine()
	{
		WaitForSecond(3);
		std::cout << "Je m'affiche apr�s 3 seconde" << std::endl;
	}
}


