#include "Rtype/Game/Client/SpaceShipController.hpp"
#include "SaltyEngine/Input.hpp"
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/Input/VirtualInutManager.hpp"

SaltyEngine::SpaceShipController::SpaceShipController(GameObject * const gamObj, bool playable) :
        SaltyBehaviour("SpaceShipController", gamObj),
        speed(5),
        manager(NULL),
        playable(playable)
{
	::SaltyEngine::SFML::Texture *texture = ::SaltyEngine::SFML::AssetManager::Instance().GetTexture("SpaceShips");
	if (texture != nullptr)
	{
		gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(0, 0, 34, 34)), ::SaltyEngine::Layout::normal);
	}
}

SaltyEngine::SpaceShipController::SpaceShipController(const std::string & name, GameObject * const gamObj, bool playable) :
        SaltyBehaviour(name, gamObj),
        speed(5),
        manager(NULL),
        playable(playable)
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

    if (gameman && playable)
        manager = gameman->GetComponent<GameManager>();
}

void SaltyEngine::SpaceShipController::FixedUpdate()
{
    float h, v;
    if (playable)
    {
        h = InputKey::GetAxis("Horizontal");
        v = InputKey::GetAxis("Vertical");
        if (h != 0 || v != 0) {
            gameObject->transform.Translate(Vector(h, v) * speed/* * SaltyEngine::Instance().GetDeltaTime()*/);
            if (manager)
            {
                //todo fix object id parce que la flemme depuis le début du projet. #victorQuiRage
                manager->SendPackage<MOVEPackageGame>(
                        &Network::Core::BasicConnection::SendData<MOVEPackageGame>,
                        gameObject->transform.position.x,
                        gameObject->transform.position.y,
                        manager->gameObjectContainer.GetServerObjectID(gameObject));
//                manager->SendInput("Horizontal", h);
//                manager->SendInput("Vertical", v);
            }
        }
    }
//    else
//    {
//        h = Input::VirtualInputManager::GetAxis("Horizontal");
//        v = Input::VirtualInputManager::GetAxis("Vertical");
//    }
}



void SaltyEngine::SpaceShipController::DisplayCoroutine()
{
}
