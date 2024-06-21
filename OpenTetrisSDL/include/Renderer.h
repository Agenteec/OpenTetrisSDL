#pragma once

#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();
    void clear();
    void present();
    void drawTexture(SDL_Texture* texture, int x, int y, int width, int height);
    SDL_Texture* loadTexture(const std::string& file);

private:
    SDL_Renderer* sdlRenderer_;
    SDL_Window* window_;
};