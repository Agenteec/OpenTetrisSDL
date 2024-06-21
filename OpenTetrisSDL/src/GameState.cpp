#include "GameState.h"

GameState::GameState() : nextId_(0) {}

GameState::~GameState() {}

void GameState::addObject(std::shared_ptr<GameObject> object) {
    objects_[nextId_++] = object;
}

void GameState::removeObject(int id) {
    objects_.erase(id);
}

std::shared_ptr<GameObject> GameState::getObject(int id) {
    auto it = objects_.find(id);
    if (it != objects_.end()) {
        return it->second;
    }
    return nullptr;
}

const std::unordered_map<int, std::shared_ptr<GameObject>>& GameState::getObjects() const {
    return objects_;
}

void GameState::update() {
    for (auto& pair : objects_) {
        pair.second->update();
    }
}
