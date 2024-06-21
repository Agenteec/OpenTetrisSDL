#include "Renderer.h"

Renderer::Renderer(SDL_Window* window) : window_(window) {
    sdlRenderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdlRenderer_) {
        //Нужно будет логирование добавить
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
    SDL_Rect dstRect = { x, y, width, height };
    SDL_RenderCopy(sdlRenderer_, texture, nullptr, &dstRect);
}

SDL_Texture* Renderer::loadTexture(const std::string& file) {
    SDL_Texture* texture = IMG_LoadTexture(sdlRenderer_, file.c_str());
    if (!texture) {
        //Нужно будет логирование добавить
    }
    return texture;
}