#include "Scenes/NetworkGameScene.h"


NetworkGameScene::NetworkGameScene(Window* window, Renderer* renderer, InputHandler* inputHandler, NetworkManager* networkManager, PhysicsEngine* physicsEngine)
    : window_(window), renderer_(renderer), inputHandler_(inputHandler), networkManager_(networkManager), physicsEngine_(physicsEngine) {}

void NetworkGameScene::init() {
}

void NetworkGameScene::update() {
    networkManager_->receiveTCP();
    networkManager_->receiveUDP();
}

void NetworkGameScene::render() {
    renderer_->clear();
    renderer_->present();
}

void NetworkGameScene::handleEvents() {
    inputHandler_->update();
    if (inputHandler_->isKeyPressed(SDLK_ESCAPE)) {
        game_->changeScene(std::make_unique<MainMenuScene>(window_, renderer_, inputHandler_, game_));
    }
}