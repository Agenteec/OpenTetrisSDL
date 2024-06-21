#pragma once
#include <vector>
#include <memory>
#include "GameObjects/GameObject.h"

class GameState {
public:
    GameState();
    ~GameState();

    void addObject(std::shared_ptr<GameObject> object);
    void removeObject(std::shared_ptr<GameObject> object);
    std::vector<std::shared_ptr<GameObject>> getObjects() const;
    void update();

private:
    std::vector<std::shared_ptr<GameObject>> objects_;
};