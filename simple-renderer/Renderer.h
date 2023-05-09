#pragma once
#include <stdint.h>

class Renderer
{
public:
    Renderer(int w, int h, bool centered);
    ~Renderer();

    bool Initialize();
    void PollEvents();
    void Draw();

    bool quit = false;
    uint32_t* pixels;

    uint32_t clearColor;
    
private:
    bool initCenter;
    int screenWidth, screenHeight;
    int width, height;
    struct SDL_Window* window;
    struct SDL_Renderer* renderer;
    struct SDL_Texture* renderTexture;
};
