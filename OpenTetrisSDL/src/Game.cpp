#include "Game.h"

Game::Game()
    : window(std::make_unique<Window>("Game Window", 800, 600)),
    renderer(std::make_unique<Renderer>(window->getSDLWindow())),
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
