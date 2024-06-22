#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <spdlog/spdlog.h>
#include "Settings.h"

class Renderer {
public:
    Renderer(SDL_Window* window, const VideoSettings& videoSettings);
    ~Renderer();
    void clear();
    void present();
    void drawTexture(SDL_Texture* texture, int x, int y, int width, int height);
    SDL_Texture* loadTexture(const std::string& file);
    void setVerticalSync(bool enabled);
    void setFrameRateLimit(int limit);
    void setAntiAliasingLevel(int level);

private:
    SDL_Renderer* sdlRenderer_;
    SDL_Window* window_;
    int frameRateLimit_;
    bool verticalSyncEnabled_;
};