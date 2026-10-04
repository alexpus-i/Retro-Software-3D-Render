#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>

#include <cstdint>
#include <stdint.h>

#define Scr_Width 480
#define Scr_Height 360

#define u32 uint32_t
#define RGBA(r, g, b, a) ((u32)(r) << 24) | ((u32)(g) << 16) | ((u32)(b) << 8) | ((u32)(a))

int const TexPitch = Scr_Width * sizeof(u32);

static u32 FrameBuffer[Scr_Width * Scr_Height];

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern SDL_Event event;


void DrawPixel(u32 x, u32 y, u32 color);
void ClearPixels(u32 color);
bool Engine_Init();
void Engine_Update();
void Engine_Quit();
bool ProcessEvents();
