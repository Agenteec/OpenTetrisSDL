#include "GameState.h"

GameState::GameState() {}

GameState::~GameState() {}

void GameState::addObject(std::shared_ptr<GameObject> object) {
    objects_.push_back(object);
}

void GameState::removeObject(std::shared_ptr<GameObject> object) {
    objects_.erase(std::remove(objects_.begin(), objects_.end(), object), objects_.end());
}

std::vector<std::shared_ptr<GameObject>> GameState::getObjects() const {
    return objects_;
}

void GameState::update() {
    for (const auto& object : objects_) {
        object->update();
    }
}