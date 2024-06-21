#include "Renderer.h"

Renderer::Renderer(Window* window)
    : window_(window) {
    sdlRenderer_ = SDL_CreateRenderer(window_->getSDLWindow(), -1, SDL_RENDERER_ACCELERATED);
    if (!sdlRenderer_) {

    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(sdlRenderer_);
}

void Renderer::clear() {
    SDL_RenderClear(sdlRenderer_);
}

void Renderer::present() {
    SDL_RenderPresent(sdlRenderer_);
}

void Renderer::drawTexture(SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(sdlRenderer_, texture, nullptr, &destRect);
}

SDL_Texture* Renderer::loadTexture(const std::string& file) {
    SDL_Texture* texture = IMG_LoadTexture(sdlRenderer_, file.c_str());
    if (!texture) {
    }
    return texture;
}