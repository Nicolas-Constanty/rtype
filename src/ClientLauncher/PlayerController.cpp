#include "SaltyEngine/PlayerController.hpp"
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
	}

	void PlayerController::FixedUpdate()
	{
		//std::cout << "Fixed Update 60 fps" << std::endl;
		
		if (InputKey::GetKeyDown("S"))
			gameObject->transform.Translate(Vector(0.0f, 1.0f)  * speed);
		if (InputKey::GetKeyDown("Z"))
			gameObject->transform.Translate(Vector(0.0f, -1.0f) * speed);
		if (InputKey::GetKeyDown("D"))
			gameObject->transform.Translate(Vector(1.0f, 0.0f) * speed);
		if (InputKey::GetKeyDown("Q"))
			gameObject->transform.Translate(Vector(-1.0f, 0.0f) * speed);
        //std::cout << gameObject->transform.position << std::endl;
	}

	void PlayerController::DisplayCoroutine()
	{
		WaitForSecond(3);
		std::cout << "Je m'affiche apr�s 3 seconde" << std::endl;
	}
}


