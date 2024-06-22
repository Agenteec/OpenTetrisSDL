#include "Window.h"

Window::Window(const std::string& title, int width, int height, bool fullscreen)
    : width_(width), height_(height), fullscreen_(fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        spdlog::error("SDL could not initialize! SDL Error: {}", SDL_GetError());
        return;
    }

    Uint32 flags = SDL_WINDOW_SHOWN;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width_, height_,
        flags
    );

    if (!window_) {
        spdlog::error("Window could not be created! SDL Error: {}", SDL_GetError());
    }
    else {
        spdlog::info("Window created: {} ({}x{})", title, width, height);
    }
}

Window::~Window() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
    spdlog::info("Window destroyed and SDL quit");
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

void Window::setFullscreen(bool fullscreen) {
    fullscreen_ = fullscreen;
    if (fullscreen) {
        SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
    }
    else {
        SDL_SetWindowFullscreen(window_, 0);
    }
    spdlog::info("Fullscreen mode set to {}", fullscreen);
}

void Window::resize(int width, int height) {
    width_ = width;
    height_ = height;
    SDL_SetWindowSize(window_, width, height);
    spdlog::info("Window resized to {}x{}", width, height);
}
