#pragma once

#include <unordered_map>
#include <memory>
#include "GameObjects/GameObject.h"

class GameState {
public:
    GameState();
    ~GameState();

    void addObject(std::shared_ptr<GameObject> object);
    void removeObject(int id);
    std::shared_ptr<GameObject> getObject(int id);
    const std::unordered_map<int, std::shared_ptr<GameObject>>& getObjects() const;

    void update();

private:
    std::unordered_map<int, std::shared_ptr<GameObject>> objects_;
    int nextId_;
};