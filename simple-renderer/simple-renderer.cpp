#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "Renderer.h"
#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
    SDL_SetMainReady();

    Renderer* renderer = new Renderer(640, 480, true);

    bool init = renderer->Initialize();
    if(!init)
    {
        std::cout << "SDL error during initialization." << std::endl;
        return 1;    
    }

    std::chrono::microseconds deltaTime;
    
    while(!renderer->quit)
    {
        std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
        if(deltaTime.count() != 0)
        {
            std::cout << 1000000 / deltaTime.count() << "fps / " << deltaTime.count() / (double)1000 << "ms" << std::endl;
        }

        renderer->PollEvents();
        renderer->Render();

        std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }

    delete renderer;
    return 0;
}
