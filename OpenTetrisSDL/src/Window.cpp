#include "Window.h"

Window::Window(const std::string& title, int width, int height)
    : width_(width), height_(height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        
    }

    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width_, height_,
        SDL_WINDOW_SHOWN
    );

    if (!window_) {
        
    }
}

Window::~Window() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

SDL_Window* Window::getSDLWindow() const {
    return window_;
}

int Window::getWidth() const {
    return width_;
}

int Window::getHeight() const {
    return height_;
}