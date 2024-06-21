#include "Scenes/MainMenuScene.h"
#include "Game.h"

MainMenuScene::MainMenuScene(Window* window, Renderer* renderer, InputHandler* inputHandler, Game* game)
    : window_(window), renderer_(renderer), inputHandler_(inputHandler), game_(game) {}

void MainMenuScene::init() {
    
}

void MainMenuScene::update() {

}

void MainMenuScene::render() {
    renderer_->clear();
    
    renderer_->present();
}

void MainMenuScene::handleEvents() {
    inputHandler_->update();

    if (inputHandler_->isKeyPressed(SDLK_1)) {
        onCreateServer();
    }
    if (inputHandler_->isKeyPressed(SDLK_2)) {
        onJoinServer();
    }
    if (inputHandler_->isKeyPressed(SDLK_3)) {
        game_->changeScene(std::make_unique<SinglePlayerGameScene>(window_, renderer_,  inputHandler_, game_->getPhysicsEngine(), game_));
    }
}

void MainMenuScene::onCreateServer() {
    game_->startServer(12345, 12346);
    game_->changeScene(std::make_unique<NetworkGameScene>(window_, renderer_, inputHandler_, game_->getNetworkManager(), game_->getPhysicsEngine()));
}

void MainMenuScene::onJoinServer() {
    game_->connectToServer("localhost", "12345", "12346");
    game_->changeScene(std::make_unique<NetworkGameScene>(window_, renderer_, inputHandler_, game_->getNetworkManager(), game_->getPhysicsEngine()));
}