#include "Renderer.h"
#include "SDL2/SDL.h"
#include <iostream>


Renderer::Renderer(int w, int h, bool centered)
{
    width = w;
    height = h;
    initCenter = centered;
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Renderer::Initialize()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int xpos = 100, ypos = 100;
    if(initCenter)
    {
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0, &dm);
        xpos = (dm.w / 2) - (width / 2);
        ypos = (dm.h / 2) - (height / 2);
    }
    
    SDL_Window* win = SDL_CreateWindow("Simple Renderer", xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if(win == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}

void Renderer::PollEvents()
{
    SDL_Event e;
    // handle events
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            quit = true;
        }
    }
}

void Renderer::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, width/2, height/2);
    SDL_RenderPresent(renderer);
}


