# Simple Renderer

An extremely bare-bones renderer written from scratch. It uses [SDL2](https://github.com/libsdl-org/SDL) for windowing and drawing the final render, and [GLM](https://github.com/g-truc/glm) for vector/matrix math.

Currently the shapes are hard-coded, there is no lighting, and the only supported vertex attribute is color. If I come back to this project, I'd like to add some sort of 3D model support (probably OBJ) and add some simple lighting/shading.

# Building
I managed libraries using vcpkg. I'm still a C++ dependency noob, but I think as long as you use MSVC to compile and have the `x64-windows` versions of `sdl2` and `glm` installed on vcpkg, it should work. Running the program will require the [Visual C++ Redistributables](https://learn.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist?view=msvc-170) from Microsoft.

The program runs about 25x faster in release mode than debug.