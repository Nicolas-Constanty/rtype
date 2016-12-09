#include "SaltyEngine/SFML.hpp"

SaltyEngine::GameObject *CreateBackground()
{
	SaltyEngine::GameObject *background = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());

	SaltyEngine::SFML::Texture *text = SaltyEngine::SFML::AssetManager::Instance().GetTexture("Background");
	if (text)
	{
		SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(text);
		std::cout << "Sprite" << spr << std::endl;
		background->AddComponent<SaltyEngine::SFML::Image>(spr);

		SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(text->GetSize().x, text->GetSize().y), "R-Type Launcher");
		Singleton<SaltyEngine::SaltyEngine>::Instance().SetRenderer(renderer);

		SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
		Singleton<SaltyEngine::SaltyEngine>::Instance().SetEventManager(event_manager);
		background->transform.position = SaltyEngine::Vector(text->GetSize().x / 2, text->GetSize().y / 2);
		return background;
	}
	else
		SaltyEngine::Debug::PrintError("Cannot load file");
	return nullptr;
}

SaltyEngine::GameObject *CreatePanel()
{
	SaltyEngine::GameObject *panel = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());
	SaltyEngine::SFML::Texture *text = SaltyEngine::SFML::AssetManager::Instance().GetTexture("PanelLogin");
	if (text)
	{
		SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(text);
		panel->AddComponent<SaltyEngine::SFML::Image>(spr);
		SaltyEngine::SFML::Renderer *renderer = dynamic_cast<SaltyEngine::SFML::Renderer *>(SaltyEngine::SaltyEngine::Instance().GetRenderer());
		panel->transform.position = SaltyEngine::Vector(renderer->GetRenderWindow()->getSize().x / 2, renderer->GetRenderWindow()->getSize().y / 2);
		return panel;
	}
	else
		SaltyEngine::Debug::PrintError("Cannot load file");
	return nullptr;
}

void initLoginScene(SaltyEngine::SFML::Scene *scene)
{
	//Background
	SaltyEngine::GameObject *background = CreateBackground();
	*scene << background;
	//Panel
	SaltyEngine::GameObject *panel = CreatePanel();
	*scene << panel;
}

int main(int argc, char* argv[])
{
	SaltyEngine::SFML::AssetManager::Instance().LoadAssets();

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	initLoginScene(scene);
	// Push scene int SaltyEngine
	SaltyEngine::SaltyEngine::Instance() << scene;

	// Run the SaltyEngine with default Scene 0
	SaltyEngine::SaltyEngine::Instance().Run();
	return 0;
}
