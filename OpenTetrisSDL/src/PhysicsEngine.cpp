#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine()
    : world_(new b2World(b2Vec2(0.0f, -9.8f))) {
}

PhysicsEngine::~PhysicsEngine() {
    delete world_;
}

void PhysicsEngine::update() {
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world_->Step(timeStep, velocityIterations, positionIterations);

    for (GameObject* object : objects_) {
        object->updateFromPhysics();
    }
}

b2World* PhysicsEngine::getWorld() {
    return world_;
}

void PhysicsEngine::addObject(GameObject* object) {
    objects_.push_back(object);
}