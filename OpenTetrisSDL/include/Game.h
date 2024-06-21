#pragma once
#include "Window.h"
#include "Renderer.h"
#include "InputHandler.h"

#include "Network/NetworkManager.h"
#include "Network/Server.h"

#include "PhysicsEngine.h"
#include "ResourceManager.h"

#include "Scenes/Scene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/NetworkGameScene.h"
#include "Scenes/SinglePlayerGameScene.h"

#include <memory>
#include <vector>

class Game {
public:
    Game();
    ~Game();
    void run();
    void changeScene(std::unique_ptr<Scene> newScene);
    void quit();
    void startServer(short tcpPort, short udpPort);
    void connectToServer(const std::string& host, const std::string& tcpPort, const std::string& udpPort);
    NetworkManager* getNetworkManager();
    PhysicsEngine* getPhysicsEngine();
    GameState* getGameState();

private:
    void init();
    void update();
    void render();
    void handleEvents();

    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputHandler> inputHandler;
    std::unique_ptr<NetworkManager> networkManager;
    std::unique_ptr<PhysicsEngine> physicsEngine;
    std::unique_ptr<ResourceManager> resourceManager;
    std::unique_ptr<GameState> gameState;
    std::vector<std::unique_ptr<Scene>> scenes;
    std::unique_ptr<Scene> currentScene;
    bool running;
};