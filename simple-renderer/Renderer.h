#pragma once

class Renderer
{
public:
    Renderer(int w, int h, bool centered);
    ~Renderer();

    bool Initialize();
    void PollEvents();
    void Render();

    bool quit = false;
    
private:
    bool initCenter;
    int screenWidth, screenHeight;
    int width, height;
    struct SDL_Window* window;
    struct SDL_Renderer* renderer;
};
