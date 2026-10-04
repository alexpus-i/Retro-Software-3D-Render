#include "engine.hpp"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <cstddef>
#include <iostream>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *texture = nullptr;
SDL_Event event;


void DrawPixel(u32 x, u32 y, u32 color)
{
    if(x < 0 || x >= Scr_Width || y < 0 || y >= Scr_Height)
    {
        std::cout << "out of range\n";
        return;
    }
    FrameBuffer[y * Scr_Width + x] = color;
}


void ClearPixels(u32 color)
{
    int const Scr_Size = Scr_Width * Scr_Height;
    for(uint32_t i=0; i < Scr_Size; i++)
    {
        FrameBuffer[i] = color;
    }
}


bool Engine_Init()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL: can't init: " << SDL_GetError();
        return false;
    }
    window = SDL_CreateWindow("3D_engine", Scr_Width, Scr_Height, 0);
      if(window == NULL)
      {
        std::cout << "SDL: can't create window: " << SDL_GetError();
        SDL_Quit();
        return false;
      }

    renderer = SDL_CreateRenderer(window, NULL);
        SDL_SetRenderVSync(renderer, 1); // Lock  fps

      if(renderer == NULL)
      {
        std::cout << "SDL: can't create renderer: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
      }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_STREAMING, Scr_Width, Scr_Height);

      SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
      if(texture == NULL)
      {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
      }

      return true;
}


void Engine_Update()
{
    SDL_UpdateTexture(texture, NULL, FrameBuffer, TexPitch);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


void Engine_Quit()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool ProcessEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
    }
    return true;
}
