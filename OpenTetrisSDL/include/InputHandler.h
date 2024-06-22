#pragma once

#include <SDL2/SDL.h>
#include <imgui_impl_sdl2.h>
#include <unordered_map>
#include <spdlog/spdlog.h>

class InputHandler {
public:
    InputHandler();
    ~InputHandler();
    void update();
    bool isKeyPressed(SDL_Keycode key);
    bool isKeyReleased(SDL_Keycode key);
    bool isMouseButtonPressed(Uint8 button);

private:
    std::unordered_map<SDL_Keycode, bool> keyStates_;
    std::unordered_map<Uint8, bool> mouseButtonStates_;
};