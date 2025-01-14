#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL.h>
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    ResourceManager(SDL_Renderer* renderer);
    ~ResourceManager();

    SDL_Texture* LoadTexture(const std::string& filePath);
    void Clear(); // Clear all loaded resources.

private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> textures;

    SDL_Texture* LoadTextureFromFile(const std::string& filePath);
};

#endif // RESOURCEMANAGER_H
