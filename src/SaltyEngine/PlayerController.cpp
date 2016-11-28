#include "SaltyEngine/PlayerController.hpp"

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
		std::cout << "Fixed Update 60 fps" << std::endl;
		gameObject->transform.Translate(Vector(0.5f, 1.0f) * Singleton<SaltyEngine>::Instance().GetFixedDeltaTime() * speed);
        std::cout << gameObject->transform.position << std::endl;
	}

	void PlayerController::DisplayCoroutine()
	{
		WaitForSecond(3);
		std::cout << "Je m'affiche apr�s 3 seconde" << std::endl;
	}
}


