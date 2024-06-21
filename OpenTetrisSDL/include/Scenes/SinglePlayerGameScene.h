#pragma once

#include "Scene.h"
#include "Window.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "PhysicsEngine.h"


class Game;
class SinglePlayerGameScene : public Scene {
public:
    SinglePlayerGameScene(Window* window, Renderer* renderer, InputHandler* inputHandler, PhysicsEngine* physicsEngine, Game* game_);
    ~SinglePlayerGameScene() override = default;

    void init() override;
    void update() override;
    void render() override;
    void handleEvents() override;

private:
    Window* window_;
    Renderer* renderer_;
    InputHandler* inputHandler_;
    PhysicsEngine* physicsEngine_;
    Game* game_;
};



