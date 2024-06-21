#pragma once

#include <Box2D/Box2D.h>
#include <SDL.h>

class GameObject {
public:
    GameObject(b2World* world);
    GameObject();
    virtual ~GameObject();
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    void updateFromPhysics();

protected:
    b2Body* body_;
};