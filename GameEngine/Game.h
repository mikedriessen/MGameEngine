#pragma once

#include <SDL.h>
#include <string>
#include "Sprite.h"
#include "ResourceManager.h"
#include "InputManager.h"

class Game {
public:
    Game();
    ~Game();

    bool Initialize(const std::string& title, int width, int height);
    void HandleEvents(SDL_Event& event);
    void Update(float deltaTime);
    void Render();
    bool IsRunning() const { return isRunning; }
    void Run();  // Declare the Run method
    void Shutdown();  // Declare the Shutdown method

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth, screenHeight;
    ResourceManager* resourceManager;
    Sprite* sprite;
    InputManager inputManager;
};
