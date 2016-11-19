#include "AA.hpp"

namespace SaltyEngine
{
	AA::AA() : SaltyBehavior("AA") {
		speed = 3.5f;
	};

	AA::AA(const std::string &name) : SaltyBehavior(name) {
		speed = 3.5f;
	};

	void AA::Start()
	{
		std::cout << "Je suis le Start, je ne suis appelé qu'une fois" << std::endl;
		StartCoroutine(&AA::DisplayCoroutine);
	}

	void AA::FixedUpdate()
	{
		std::cout << "Fixed Update 60 fps" << std::endl;
		transform->Translate(Vector3(0.0f, 1.0f, 0.0f) * Singleton<SaltyGame>::Instance().FixedDeltaTime() * speed);
		std::cout << transform->position << std::endl;
	}

	void AA::DisplayCoroutine()
	{
		WaitForSecond(3);
		std::cout << "Je m'affiche après 3 seconde" << std::endl;
	}
}


