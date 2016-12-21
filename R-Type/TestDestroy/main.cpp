#include <SaltyEngine/SFML.hpp>

void my_handler(int s){
    (void)s;
    SaltyEngine::SaltyEngine::Instance().Stop();
}

int main() {

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
    //SaltyEngine::SFML::EventManager *event_manager = new SaltyEngine::SFML::EventManager(renderer->GetRenderWindow());
    // Set Renderer and EventManager
    SaltyEngine::SaltyEngine::Instance().SetRenderer(renderer);
    //SaltyEngine::SaltyEngine::Instance().SetEventManager(event_manager);

    // Create Scene
    SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

    // Push scene int SaltyEngine
    SaltyEngine::SaltyEngine::Instance() << scene;

    SaltyEngine::SaltyEngine::Instance().Run();
    return 0;
}