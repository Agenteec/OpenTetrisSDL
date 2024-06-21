#include "Game.h"

#include "Game.h"

Game::Game()
    : window(std::make_unique<Window>("Test", 800, 600)),
    renderer(std::make_unique<Renderer>(window.get())),
    inputHandler(std::make_unique<InputHandler>()),
    networkManager(std::make_unique<NetworkManager>()),
    physicsEngine(std::make_unique<PhysicsEngine>()),
    resourceManager(std::make_unique<ResourceManager>()),
    gameState(std::make_unique<GameState>()),
    running(true) {
    init();
}

Game::~Game() {
    if (server) {
        server->stop();
    }
}

void Game::init() {
    changeScene(std::make_unique<MainMenuScene>(window.get(), renderer.get(), inputHandler.get(), this));
}

void Game::update() {
    if (currentScene) {
        currentScene->update();
    }
    gameState->update();
}

void Game::render() {
    if (currentScene) {
        currentScene->render();
    }
}

void Game::handleEvents() {
    if (currentScene) {
        currentScene->handleEvents();
    }
}

void Game::changeScene(std::unique_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
    if (currentScene) {
        currentScene->init();
    }
}

void Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
    }
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