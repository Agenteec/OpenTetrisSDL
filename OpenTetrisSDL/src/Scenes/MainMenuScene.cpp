#include "Scenes/MainMenuScene.h"


MainMenuScene::MainMenuScene(Window* window, Renderer* renderer, InputHandler* inputHandler, Game* game)
    : window_(window), renderer_(renderer), inputHandler_(inputHandler), game_(game) {}

void MainMenuScene::init() {
    // Initialize main menu
}

void MainMenuScene::update() {
    // Update main menu logic
}

void MainMenuScene::render() {
    renderer_->clear();
    // Render main menu
    renderer_->present();
}

void MainMenuScene::handleEvents() {
    inputHandler_->update();
    // Handle menu input events

    // Example: Handle menu options
    if (inputHandler_->isKeyPressed(SDLK_1)) {
        onCreateServer();
    }
    if (inputHandler_->isKeyPressed(SDLK_2)) {
        onJoinServer();
    }
    if (inputHandler_->isKeyPressed(SDLK_3)) {
        game_->changeScene(std::make_unique<SinglePlayerGameScene>(window_, renderer_, inputHandler_, game_));
    }
}

void MainMenuScene::onCreateServer() {
    // Create and start server
    game_->startServer(12345, 12346);
    game_->changeScene(std::make_unique<NetworkGameScene>(window_, renderer_, inputHandler_, game_->getNetworkManager(), game_->getPhysicsEngine()));
}

void MainMenuScene::onJoinServer() {
   
    game_->connectToServer("localhost", "12345", "12346");
    game_->changeScene(std::make_unique<NetworkGameScene>(window_, renderer_, inputHandler_, game_->getNetworkManager(), game_->getPhysicsEngine()));
}