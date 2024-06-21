#include "GameObjects/GameObject.h"

GameObject::GameObject(b2World* world) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    body_ = world->CreateBody(&bodyDef);
}

GameObject::GameObject():body_(nullptr)
{
}

GameObject::~GameObject() {
    if (body_ != nullptr)
    {
        body_->GetWorld()->DestroyBody(body_);
    }
    
}

void GameObject::updateFromPhysics() {
    
}