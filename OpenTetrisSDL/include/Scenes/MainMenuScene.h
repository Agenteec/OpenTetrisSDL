#pragma once

#include "Scenes/Scene.h"
#include "Scenes/NetworkGameScene.h"
#include "Scenes/SinglePlayerGameScene.h"
#include "Window.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "Game.h"
#include <memory>

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

