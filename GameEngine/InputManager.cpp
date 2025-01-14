#include "InputManager.h"

InputManager::InputManager() {
    currentKeyStates = SDL_GetKeyboardState(nullptr);
    std::fill(std::begin(previousKeyStates), std::end(previousKeyStates), 0);

    mouseX = mouseY = 0;
    currentMouseState = previousMouseState = 0;
}

InputManager::~InputManager() {}

void InputManager::Update() {
    // Update previous key states.
    std::copy(currentKeyStates, currentKeyStates + SDL_NUM_SCANCODES, previousKeyStates);

    // Update mouse state.
    previousMouseState = currentMouseState;
    currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
}

bool InputManager::IsKeyDown(SDL_Scancode key) const {
    return currentKeyStates[key];
}

bool InputManager::IsKeyUp(SDL_Scancode key) const {
    return !currentKeyStates[key];
}

bool InputManager::IsKeyPressed(SDL_Scancode key) const {
    return currentKeyStates[key] && !previousKeyStates[key];
}

int InputManager::GetMouseX() const {
    return mouseX;
}

int InputManager::GetMouseY() const {
    return mouseY;
}

bool InputManager::IsMouseButtonDown(Uint8 button) const {
    return (currentMouseState & SDL_BUTTON(button)) != 0;
}
