#pragma once

#include <SDL2/SDL.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();
    SDL_Window* getSDLWindow() const;
    int getWidth() const;
    int getHeight() const;

private:
    SDL_Window* window_;
    int width_;
    int height_;
};

