#pragma once

#include "Scene.h"
#include "Window.h"
#include "InputHandler.h"
#include "Renderer.h"
#include <memory>

class Game;

class MainMenuScene : public Scene {
public:
    MainMenuScene(Window* window, Renderer* renderer, InputHandler* inputHandler, Game* game);
    void init() override;
    void update() override;
    void render() override;
    void handleEvents() override;

private:
    void onCreateServer();
    void onJoinServer();

    Window* window_;
    Renderer* renderer_;
    InputHandler* inputHandler_;
    Game* game_;
};