#include "Renderer.h"



Renderer::Renderer(SDL_Window* window, const VideoSettings& videoSettings)
    : window_(window), frameRateLimit_(videoSettings.framerateLimit), verticalSyncEnabled_(videoSettings.verticalSyncEnabled) {
    Uint32 flags = SDL_RENDERER_ACCELERATED;
    if (verticalSyncEnabled_) {
        flags |= SDL_RENDERER_PRESENTVSYNC;
    }

    sdlRenderer_ = SDL_CreateRenderer(window, -1, flags);
    if (!sdlRenderer_) {
        spdlog::error("Renderer could not be created! SDL Error: {}", SDL_GetError());
    }
    else {
        spdlog::info("Renderer created with vsync: {}", verticalSyncEnabled_);
    }

    setFrameRateLimit(videoSettings.framerateLimit);
    setAntiAliasingLevel(videoSettings.antiAliasingLevel);
    initImGui();
}
void Renderer::renderImGui() {
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), sdlRenderer_);

    
}
Renderer::~Renderer() {
    SDL_DestroyRenderer(sdlRenderer_);
    cleanupImGui();
    spdlog::info("Renderer destroyed");
}

void Renderer::clear() {
    SDL_RenderClear(sdlRenderer_);
    spdlog::debug("Renderer cleared");
}

void Renderer::present() {


    SDL_RenderPresent(sdlRenderer_);
    spdlog::debug("Renderer presented");
}

void Renderer::drawTexture(SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect dstRect = { x, y, width, height };
    SDL_RenderCopy(sdlRenderer_, texture, nullptr, &dstRect);
    spdlog::debug("Texture drawn at ({}, {}) with size ({}x{})", x, y, width, height);
}

SDL_Texture* Renderer::loadTexture(const std::string& file) {
    SDL_Texture* texture = IMG_LoadTexture(sdlRenderer_, file.c_str());
    if (!texture) {
        spdlog::error("Unable to load texture from {}: {}", file, IMG_GetError());
    }
    else {
        spdlog::info("Texture loaded from {}", file);
    }
    return texture;
}

void Renderer::setVerticalSync(bool enabled) {
    verticalSyncEnabled_ = enabled;
    
    Uint32 flags = SDL_RENDERER_ACCELERATED | (enabled ? SDL_RENDERER_PRESENTVSYNC : 0);
    SDL_DestroyRenderer(sdlRenderer_);
    sdlRenderer_ = SDL_CreateRenderer(window_, -1, flags);
    if (!sdlRenderer_) {
        spdlog::error("Renderer could not be recreated! SDL Error: {}", SDL_GetError());
    }
    else {
        spdlog::info("Renderer recreated with vsync: {}", enabled);
    }
}

void Renderer::setFrameRateLimit(int limit) {
    frameRateLimit_ = limit;
    
    spdlog::info("Frame rate limit set to {}", limit);
}

void Renderer::setAntiAliasingLevel(int level) {
    //Пока не знаю как выставить
    spdlog::info("Anti-aliasing level set to {}", level);
}

void Renderer::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/arial.ttf", 18, nullptr, io.Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplSDL2_InitForSDLRenderer(window_, sdlRenderer_);
    ImGui_ImplSDLRenderer2_Init(sdlRenderer_);
}

void Renderer::cleanupImGui()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    spdlog::debug("Cleanup ImGui");
}
