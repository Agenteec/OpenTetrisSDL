#include "InputHandler.h"


InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}


void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (event.type) {
        case SDL_KEYDOWN:
            keyStates_[event.key.keysym.sym] = true;
            spdlog::debug("Key down: {}", event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            keyStates_[event.key.keysym.sym] = false;
            spdlog::debug("Key up: {}", event.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseButtonStates_[event.button.button] = true;
            spdlog::debug("Mouse button down: {}", event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            mouseButtonStates_[event.button.button] = false;
            spdlog::debug("Mouse button up: {}", event.button.button);
            break;
        default:
            break;
        }
    }
}

bool InputHandler::isKeyPressed(SDL_Keycode key) {
    auto it = keyStates_.find(key);
    bool isPressed = it != keyStates_.end() && it->second;
    spdlog::debug("isKeyPressed check: key={}, isPressed={}", key, isPressed);
    return isPressed;
}

bool InputHandler::isKeyReleased(SDL_Keycode key) {
    auto it = keyStates_.find(key);
    bool isReleased = it == keyStates_.end() || !it->second;
    spdlog::debug("isKeyReleased check: key={}, isReleased={}", key, isReleased);
    return isReleased;
}

bool InputHandler::isMouseButtonPressed(Uint8 button) {
    auto it = mouseButtonStates_.find(button);
    bool isPressed = it != mouseButtonStates_.end() && it->second;
    spdlog::debug("isMouseButtonPressed check: button={}, isPressed={}", button, isPressed);
    return isPressed;
}