#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "Renderer.h"

int main(int argc, char** argv)
{
    SDL_SetMainReady();

    Renderer* renderer = new Renderer(640, 480, true);

    renderer->Initialize();
    
    while(!renderer->quit)
    {
        renderer->PollEvents();
        renderer->Render();
    }

    delete renderer;
    return 0;
}
