#include "Scenes/NetworkGameScene.h"
#include "Game.h"

NetworkGameScene::NetworkGameScene(Window* window, Renderer* renderer, InputHandler* inputHandler, NetworkManager* networkManager, PhysicsEngine* physicsEngine, Game* game)
    : window_(window), renderer_(renderer), inputHandler_(inputHandler), networkManager_(networkManager), physicsEngine_(physicsEngine), game_(game) {}

void NetworkGameScene::init() {
}

void NetworkGameScene::update() {

    networkManager_->receiveTCP();
    networkManager_->receiveUDP();

}

void NetworkGameScene::render() {
    renderer_->clear();
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();


    ImGui::Begin("Network game Menu");
    if (ImGui::Button("Start Game")) {

    }
    if (ImGui::Button("Exit")) {
        game_->changeScene(std::make_unique<MainMenuScene>(window_, renderer_, inputHandler_, game_));
    
    }
    ImGui::End();
    ImGui::Render();

    renderer_->renderImGui();

    renderer_->present();
}

void NetworkGameScene::handleEvents() {
    inputHandler_->update();
    if (inputHandler_->isKeyPressed(SDLK_ESCAPE)) {
        game_->changeScene(std::make_unique<MainMenuScene>(window_, renderer_, inputHandler_, game_));
    }
}