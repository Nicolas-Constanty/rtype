#include "SaltyEngine/SFML.hpp"

std::list<std::string>  getAllFilesRecurive(std::string const &folder, std::string const &parent = "") {
	std::list<std::string>  files;

#if _WIN32
	WIN32_FIND_DATA findFileData;
		    HANDLE hFind;
		    hFind = FindFirstFile(std::string(folder + "\\*").c_str(), &findFileData);
		    while (hFind != INVALID_HANDLE_VALUE)
		    {
                std::string filename = std::string(findFileData.cFileName);
                if (filename != "."  && filename != "..") {
                    files.push_back(filename);
                }
				if (FindNextFile(hFind, &findFileData) == FALSE)
				{
					Debug::PrintError("Cannnot open folder " + folder);
					break;
				}
    		}
    		FindClose(hFind);
#else
	DIR             *dir;
	struct dirent   *ent;

	if ((dir = opendir(folder.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL)
		{
			std::string filename = std::string(ent->d_name);
			if (filename == "." || filename == "..") {
				continue;
			}
			if (ent->d_type == DT_DIR) {
				files.merge(getAllFilesRecurive(folder + filename + "/", filename + "/"));
			} else {
				files.push_back(parent + filename);
			}
		}
		closedir(dir);
	} else {
		Debug::PrintError("Cannnot open folder " + folder);
	}
#endif
	return files;
}

int main()
{
    SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1920, 1080), "R-Type Launcher");
	SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
	// Set Renderer and EventManager
	Singleton<SaltyEngine::Engine>::Instance().SetRenderer(renderer);
	Singleton<SaltyEngine::Engine>::Instance().SetEventManager(event_manager);

	// Create Scene
	SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

	// Push scene int SaltyEngine
	Singleton<SaltyEngine::Engine>::Instance() << scene;

    // Load scene
	auto pos = SaltyEngine::BaseVector2<float>(50, 200);
	int minY = 0;

	std::list<std::string> animations = getAllFilesRecurive(SaltyEngine::Asset::ANIMS_PATH);
	for(auto const& animation : animations) {
		SaltyEngine::GameObject * gameObject = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Object::Instantiate());
		auto animClip = SaltyEngine::SFML::AssetManager::Instance().GetAnimation(animation.substr(0, animation.find_last_of(".")));
		animClip->SetWrapMode(SaltyEngine::AnimationConstants::WrapMode::LOOP);
		auto sprr = gameObject->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite((*animClip->GetFrames().begin())->GetName()), SaltyEngine::Layout::normal);
		auto anim = gameObject->AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
		anim->AddClip(animClip, "Walk");
		gameObject->transform.position = pos;
		pos.x += sprr->GetSprite()->GetBounds()->width + 100;
//		gameObject->transform.position.y += sprr->GetSprite()->GetBounds()->height / 2;
		minY = (sprr->GetSprite()->GetBounds()->height > minY) ? sprr->GetSprite()->GetBounds()->height : minY;
		if (pos.x > renderer->GetRenderWindow()->getSize().x - 100) {
			pos.x = 50;
			pos.y += minY + 50;
		}
		*scene << gameObject;
	}

	// Run the SaltyEngine with default Scene 0
	Singleton<SaltyEngine::Engine>::Instance().Run();
	return (0);
}
