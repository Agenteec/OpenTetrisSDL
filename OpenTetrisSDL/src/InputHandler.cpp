#include "InputHandler.h"

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            keyStates_[event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            keyStates_[event.key.keysym.sym] = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseButtonStates_[event.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseButtonStates_[event.button.button] = false;
            break;
        default:
            break;
        }
    }
}

bool InputHandler::isKeyPressed(SDL_Keycode key) {
    auto it = keyStates_.find(key);
    return it != keyStates_.end() && it->second;
}

bool InputHandler::isKeyReleased(SDL_Keycode key) {
    auto it = keyStates_.find(key);
    return it == keyStates_.end() || !it->second;
}

bool InputHandler::isMouseButtonPressed(Uint8 button) {
    auto it = mouseButtonStates_.find(button);
    return it != mouseButtonStates_.end() && it->second;
}