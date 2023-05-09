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
    delete[] pixels;
    SDL_DestroyTexture(renderTexture);
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
    
    window = SDL_CreateWindow("Simple Renderer", xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
        SDL_DestroyWindow(window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // create render texture and array of pixel color values
    renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
    pixels = new uint32_t[width*height];
    // initialize screen color to black
    memset(pixels, 0, width * height * sizeof(uint32_t));

    return true;
}

void Renderer::PollEvents()
{
    SDL_Event e;
    // handle events
    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}

void Renderer::Draw()
{
    SDL_UpdateTexture(renderTexture, nullptr, pixels, width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
