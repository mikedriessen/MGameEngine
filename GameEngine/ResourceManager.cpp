#include "ResourceManager.h"
#include <SDL_image.h>
#include <iostream>

ResourceManager::ResourceManager(SDL_Renderer* renderer) : renderer(renderer) {}

ResourceManager::~ResourceManager() {
    Clear();
}

SDL_Texture* ResourceManager::LoadTexture(const std::string& filePath) {
    // Check if the texture is already loaded.
    if (textures.find(filePath) != textures.end()) {
        return textures[filePath];
    }

    // Load texture if not already loaded.
    SDL_Texture* texture = LoadTextureFromFile(filePath);
    if (texture) {
        textures[filePath] = texture;
    }

    return texture;
}

SDL_Texture* ResourceManager::LoadTextureFromFile(const std::string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << filePath << " | " << IMG_GetError() << std::endl;
    }
    return texture;
}

void ResourceManager::Clear() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}
