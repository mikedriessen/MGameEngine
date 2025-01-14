#pragma once

#include <SDL.h>
#include <string>

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const std::string& filePath, int x, int y, int width, int height, int velocityX = 1, int velocityY = 1);
    ~Sprite();

    void Render();
    void Update(int screenWidth, int screenHeight);  // Updated to accept screen dimensions
    void SetPosition(int x, int y);
    void SetSize(int width, int height);
    SDL_Rect GetRect() const;

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    int velocityX, velocityY;
};
