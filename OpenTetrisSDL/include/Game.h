#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Settings.h"
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
    Game(std::shared_ptr<Settings> settings);
    Game();
    ~Game();
    void run();
    void changeScene(std::unique_ptr<Scene> newScene);
    void quit();
    void startServer(short tcpPort, short udpPort);
    bool isServerRunning();
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
    std::shared_ptr<Settings> settings;
    std::unique_ptr<Scene> currentScene;
    std::unique_ptr<Server> server;
    bool running;


};