#include "Game.h"
#include "Sprite.h"
#include <iostream>  // Include this header for std::cerr and std::endl

Game::Game() : resourceManager(nullptr), sprite(nullptr), window(nullptr), renderer(nullptr), screenWidth(800), screenHeight(600), isRunning(true) {}

Game::~Game() {
    Shutdown();  // Make sure resources are cleaned up when the game is destroyed
}

bool Game::Initialize(const std::string& title, int width, int height) {
    // Set screen dimensions
    screenWidth = width;
    screenHeight = height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Initialization failed! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create a resizable window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Window creation failed! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer creation failed! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    resourceManager = new ResourceManager(renderer);

    // Load the texture for sprite
    std::string texturePath = "assets/example.png";
    sprite = new Sprite(renderer, texturePath, 100, 100, 100, 100);  // Initial position (100, 100), size (100, 100)

    if (!sprite) {
        std::cerr << "Failed to load sprite!" << std::endl;
        return false;
    }

    return true;
}

void Game::HandleEvents(SDL_Event& event) {
    inputManager.Update();

    // Check for SDL_QUIT event (window close)
    if (event.type == SDL_QUIT) {
        isRunning = false;
    }

    // Check for key events (like ESC)
    if (inputManager.IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
        isRunning = false;
    }

    // Handle window resize
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    }
}

void Game::Update(float deltaTime) {
    // Update the sprite's position
    if (sprite) {
        sprite->Update(screenWidth, screenHeight);  // Pass updated window size to sprite
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    // Render the sprite
    if (sprite) {
        sprite->Render();
    }

    SDL_RenderPresent(renderer);
}

void Game::Run() {
    // Game loop
    Uint32 lastTime = SDL_GetTicks();
    while (isRunning) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;  // Time difference in seconds
        lastTime = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            HandleEvents(event);
        }

        Update(deltaTime);  // Update game logic
        Render();           // Render the scene
    }
}

void Game::Shutdown() {
    // Cleanup resources
    delete resourceManager;
    delete sprite;  // Delete sprite to avoid memory leaks
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();  // Quit SDL subsystems
}
