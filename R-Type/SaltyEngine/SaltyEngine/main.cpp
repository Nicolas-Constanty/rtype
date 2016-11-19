#include "SaltyReflection.hpp"
#include "SaltyGame.hpp"
#include "Singleton.hpp"

using namespace SaltyEngine;


class BB : public SaltyBehavior {
public:
    void Start() {
        std::cout << "BB::Start() called" << std::endl;
    }

	void OnCollisionEnter()
	{
		std::cout << "BB::OnCollisionEnter() called" << std::endl;
	}

	void OnCollisionExit()
	{
		std::cout << "BB::OnCollisionExist() called" << std::endl;
	}

	void OnCollisionStay()
	{
		std::cout << "BB::OnCollisionStay() called" << std::endl;
	}

	void OnTriggerEnter()
	{
		std::cout << "BB::OnTriggerEnter() called" << std::endl;
	}

	void OnTriggerExit()
	{
		std::cout << "BB::OnTriggerExist() called" << std::endl;
	}

	void OnTriggerStay()
	{
		std::cout << "BB::OnTriggerStay() called" << std::endl;
	}

	void OnMouseEnter()
	{
		std::cout << "BB::OnMouseEnter() called" << std::endl;
	}

	void OnMouseExit()
	{
		std::cout << "BB::OnMouseExist() called" << std::endl;
	}

	void OnMouseOver()
	{
		std::cout << "BB::OnMouseOver() called" << std::endl;
	}

	void OnMouseClic()
	{
		std::cout << "BB::OnMouseClic() called" << std::endl;
	}

	void Update() {
		std::cout << "BB::Update() called" << std::endl;
	}

	void OnGui()
	{
		std::cout << "BB::OnGui() called" << std::endl;
	}
};


class CC : public SaltyBehavior {
public:
    int Start() const {
        std::cout << "CC::Start() called" << std::endl;
        return 0;
    }

	void Update() {
		std::cout << "CC::Update() called" << std::endl;
	}
};

int main()
{
	AA *aa = new AA();
	Scene *scene(new Scene());

	// Add SaltyBehavior Object to scene
	*scene << aa;

	// Add Scene Object to SaltyGame
	Singleton<SaltyGame>::Instance() << scene;

	// Run the SaltyGame with default Scene 0
	Singleton<SaltyGame>::Instance().Run();
	return 0;
}