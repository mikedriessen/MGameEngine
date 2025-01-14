#include "Sprite.h"
#include <SDL_image.h>
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& filePath, int x, int y, int width, int height, int velocityX, int velocityY)
    : renderer(renderer), texture(nullptr), rect{ x, y, width, height }, velocityX(velocityX), velocityY(velocityY) {
    // Load the texture using the SDL_image library
    texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << filePath << ", Error: " << IMG_GetError() << std::endl;
    }
}

Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Render() {
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);  // Render the texture to the screen at the given position
    }
}

void Sprite::Update(int screenWidth, int screenHeight) {
    // Update the position based on velocity
    rect.x += velocityX;
    rect.y += velocityY;

    // Bounce on collision with the screen edges (taking dynamic window size into account)
    if (rect.x <= 0) {  // Left edge
        velocityX = -velocityX;  // Reverse horizontal direction
        rect.x = 0;  // Keep the sprite at the boundary
    }

    if (rect.x + rect.w >= screenWidth) {  // Right edge (dynamic width)
        velocityX = -velocityX;  // Reverse horizontal direction
        rect.x = screenWidth - rect.w;  // Keep the sprite within bounds
    }

    if (rect.y <= 0) {  // Top edge
        velocityY = -velocityY;  // Reverse vertical direction
        rect.y = 0;  // Keep the sprite at the boundary
    }

    if (rect.y + rect.h >= screenHeight) {  // Bottom edge (dynamic height)
        velocityY = -velocityY;  // Reverse vertical direction
        rect.y = screenHeight - rect.h;  // Keep the sprite within bounds
    }
}

void Sprite::SetPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Sprite::SetSize(int width, int height) {
    rect.w = width;
    rect.h = height;
}

SDL_Rect Sprite::GetRect() const {
    return rect;
}
