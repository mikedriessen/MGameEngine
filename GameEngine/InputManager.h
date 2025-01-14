#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <unordered_map>

class InputManager {
public:
    InputManager();
    ~InputManager();

    void Update(); // Call every frame to process input.

    bool IsKeyDown(SDL_Scancode key) const;      // Check if a key is currently pressed.
    bool IsKeyUp(SDL_Scancode key) const;        // Check if a key is currently released.
    bool IsKeyPressed(SDL_Scancode key) const;  // Check if a key was pressed this frame.

    int GetMouseX() const;  // Get the current mouse X position.
    int GetMouseY() const;  // Get the current mouse Y position.
    bool IsMouseButtonDown(Uint8 button) const; // Check if a mouse button is pressed.

private:
    const Uint8* currentKeyStates;
    Uint8 previousKeyStates[SDL_NUM_SCANCODES];

    int mouseX, mouseY;
    Uint32 currentMouseState;
    Uint32 previousMouseState;
};

#endif // INPUTMANAGER_H
