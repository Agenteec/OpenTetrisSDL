#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include <GameObjects/GameObject.h>

class PhysicsEngine {
public:
    PhysicsEngine();
    ~PhysicsEngine();
    void update();
    b2World* getWorld();
    void addObject(GameObject* object);

private:
    b2World* world_;
    std::vector<GameObject*> objects_;
};

