#include "InputHandler.h"

InputHandler::InputHandler() {
    SDL_memset(keyStates_, 0, sizeof(keyStates_));
    SDL_memset(mouseButtonStates_, 0, sizeof(mouseButtonStates_));
}

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
    return keyStates_[key];
}

bool InputHandler::isKeyReleased(SDL_Keycode key) {
    return !keyStates_[key];
}

bool InputHandler::isMouseButtonPressed(Uint8 button) {
    return mouseButtonStates_[button];
}
