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

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();


    ImGui::Begin("Main Menu");
    if (ImGui::Button("Start Game")) {

    }
    if (ImGui::Button("Exit")) {

    }
    ImGui::End();
    ImGui::Render();

    renderer_->renderImGui();


    renderer_->present();
    //spdlog::info("Renderer presented");

}

void MainMenuScene::handleEvents() {
    inputHandler_->update();

    bool sceneChanged = false;

    if (inputHandler_->isKeyPressed(SDLK_1)) {
        if (!game_->isServerRunning()) {
            onCreateServer();
            sceneChanged = true;
        }
    }
    if (!sceneChanged && inputHandler_->isKeyPressed(SDLK_2)) {
        onJoinServer();
        sceneChanged = true;
    }
    if (!sceneChanged && inputHandler_->isKeyPressed(SDLK_3)) {
        game_->changeScene(std::make_unique<SinglePlayerGameScene>(window_, renderer_, inputHandler_, game_->getPhysicsEngine(), game_));
        sceneChanged = true;
    }

    
    if (sceneChanged) {
        return;
    }
}

void MainMenuScene::onCreateServer() {
    game_->startServer(12345, 12346);
    game_->changeScene(std::make_unique<NetworkGameScene>(window_, renderer_, inputHandler_, game_->getNetworkManager(), game_->getPhysicsEngine(), game_));
}

void MainMenuScene::onJoinServer() {
    game_->connectToServer("127.0.0.1", "12345", "12346");
    game_->changeScene(std::make_unique<NetworkGameScene>(window_, renderer_, inputHandler_, game_->getNetworkManager(), game_->getPhysicsEngine(), game_));
}