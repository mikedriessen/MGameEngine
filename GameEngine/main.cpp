#define SDL_MAIN_HANDLED  // Add this line before including SDL.h

#include <iostream>
#include "Game.h"

int SDL_main(int argc, char* argv[]) {  // Use SDL_main instead of main
    Game game;

    if (!game.Initialize("My SDL Game", 800, 600)) {
        std::cerr << "Failed to initialize the game!" << std::endl;
        return -1;
    }

    game.Run();  // Start the game loop

    return 0;
}
