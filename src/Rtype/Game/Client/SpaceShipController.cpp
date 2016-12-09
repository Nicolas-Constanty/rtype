#include "Rtype/Game/Client/SpaceShipController.hpp"
#include "SaltyEngine/Input.hpp"
#include "SaltyEngine/SFML.hpp"

SaltyEngine::SpaceShipController::SpaceShipController(GameObject * const gamObj) :
        SaltyBehaviour("SpaceShipController", gamObj),
        speed(10),
        manager(NULL)
{
	::SaltyEngine::SFML::Texture *texture = ::SaltyEngine::SFML::AssetManager::Instance().GetTexture("SpaceShips");
	if (texture != nullptr)
	{
		gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(0, 0, 34, 34)), ::SaltyEngine::Layout::normal);
	}
}

SaltyEngine::SpaceShipController::SpaceShipController(const std::string & name, GameObject * const gamObj) : SaltyBehaviour(name, gamObj)
{
}

void SaltyEngine::SpaceShipController::Start()
{
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
    GameObject *gameman = SaltyEngine::Instance().GetCurrentScene()->FindByName("GameManager");

    if (gameman)
        manager = gameman->GetComponent<GameManager>();
}

void SaltyEngine::SpaceShipController::FixedUpdate()
{
    float h = InputKey::GetAxis("Horizontal");
    float v = InputKey::GetAxis("Vertical");
    if (h != 0 || v != 0) {
        gameObject->transform.Translate(Vector(h, v) * speed);
        if (manager)
        {
            manager->SendInput("Horizontal", h);
            manager->SendInput("Vertical", v);
        }
    }
}

void SaltyEngine::SpaceShipController::DisplayCoroutine()
{
}
