#pragma once

#include "Scene.h"
#include "Network/NetworkManager.h"
#include "Window.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "PhysicsEngine.h"


class NetworkGameScene : public Scene {
public:
    NetworkGameScene(Window* window, Renderer* renderer, InputHandler* inputHandler, NetworkManager* networkManager, PhysicsEngine* physicsEngine);
    void init() override;
    void update() override;
    void render() override;
    void handleEvents() override;
private:
    Window* window_;
    Renderer* renderer_;
    InputHandler* inputHandler_;
    NetworkManager* networkManager_;
    PhysicsEngine* physicsEngine_;
    Game* game_;
};