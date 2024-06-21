#include "Scenes/SinglePlayerGameScene.h"
#include "Game.h"
SinglePlayerGameScene::SinglePlayerGameScene(Window* window, Renderer* renderer, InputHandler* inputHandler, PhysicsEngine* physicsEngine, Game* game_)
    : window_(window), renderer_(renderer), inputHandler_(inputHandler), physicsEngine_(physicsEngine) {}

void SinglePlayerGameScene::init() {
}

void SinglePlayerGameScene::update() {
    physicsEngine_->update();
}

void SinglePlayerGameScene::render() {
    renderer_->clear();
    renderer_->present();
}

void SinglePlayerGameScene::handleEvents() {
    inputHandler_->update();
}