#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <string>

class Engine {
public:
    Engine();
    virtual ~Engine();

    virtual bool Initialize(const std::string& title, int width, int height);
    void Run();
    void Shutdown();

protected:
    virtual void HandleEvents(SDL_Event& event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

private:
    void GameLoop();
};

#endif // ENGINE_H
