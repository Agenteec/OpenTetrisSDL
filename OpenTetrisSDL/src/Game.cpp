#include "Game.h"

Game::Game()
    : settings(std::make_shared<Settings>()),
    window(std::make_unique<Window>("Game Window", 800, 600, false)),
    renderer(std::make_unique<Renderer>(window->getSDLWindow(), settings->videoSettings)),
    inputHandler(std::make_unique<InputHandler>()),
    networkManager(std::make_unique<NetworkManager>()),
    physicsEngine(std::make_unique<PhysicsEngine>()),
    resourceManager(std::make_unique<ResourceManager>()),
    gameState(std::make_unique<GameState>()),
    running(true) {
    currentScene = std::make_unique<MainMenuScene>(window.get(), renderer.get(), inputHandler.get(), this);
}

Game::Game(std::shared_ptr<Settings> settings)
    : settings(settings),
    window(std::make_unique<Window>("Game Window", settings->videoSettings.width, settings->videoSettings.height, settings->videoSettings.fullscreen)),
    renderer(std::make_unique<Renderer>(window->getSDLWindow(), settings->videoSettings)),
    inputHandler(std::make_unique<InputHandler>()),
    networkManager(std::make_unique<NetworkManager>()),
    physicsEngine(std::make_unique<PhysicsEngine>()),
    resourceManager(std::make_unique<ResourceManager>()),
    gameState(std::make_unique<GameState>()),
    running(true) {
    currentScene = std::make_unique<MainMenuScene>(window.get(), renderer.get(), inputHandler.get(), this);
}

Game::~Game() {}

void Game::init() {
    window->setFullscreen(settings->videoSettings.fullscreen);
    renderer->setVerticalSync(settings->videoSettings.verticalSyncEnabled);
    renderer->setFrameRateLimit(settings->videoSettings.framerateLimit);
    renderer->setAntiAliasingLevel(settings->videoSettings.antiAliasingLevel);
    window->resize(settings->videoSettings.width, settings->videoSettings.height);

    changeScene(std::make_unique<MainMenuScene>(window.get(), renderer.get(), inputHandler.get(), this));
}

void Game::update() {
    currentScene->update();
}

void Game::render() {
    currentScene->render();
}

void Game::handleEvents() {
    currentScene->handleEvents();
}

void Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
    if (server != nullptr)
    {
        if (server->isRunning())
        {
            server->stop();
        }
    }
}

void Game::changeScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
    currentScene->init();
}

void Game::quit() {
    running = false;
}

void Game::startServer(short tcpPort, short udpPort) {
    server = std::make_unique<Server>(tcpPort, udpPort);
    server->start();
}

bool Game::isServerRunning()
{
    if (server != nullptr)
    {
        return server->isRunning();
    }
    return false;
}

void Game::connectToServer(const std::string& host, const std::string& tcpPort, const std::string& udpPort) {
    networkManager->start(host, tcpPort, udpPort);
}

NetworkManager* Game::getNetworkManager() {
    return networkManager.get();
}

PhysicsEngine* Game::getPhysicsEngine() {
    return physicsEngine.get();
}

GameState* Game::getGameState() {
    return gameState.get();
}
