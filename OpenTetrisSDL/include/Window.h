#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <spdlog/spdlog.h>
#include "Settings.h"

class Window {
public:
    Window(const std::string& title, int width, int height, bool fullscreen);
    ~Window();
    SDL_Window* getSDLWindow() const;
    int getWidth() const;
    int getHeight() const;
    void setFullscreen(bool fullscreen);
    void resize(int width, int height);

private:
    SDL_Window* window_;
    int width_;
    int height_;
    bool fullscreen_;
};
