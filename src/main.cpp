#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "tgaimage.h"

const TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
const TGAColor green   = {  0, 255,   0, 255};
const TGAColor red     = {  0,   0, 255, 255};
const TGAColor blue    = {255, 128,  64, 255};
const TGAColor yellow  = {  0, 200, 255, 255};

const char *title = "BareRenderer";
const int windowWidth = 64;
const int windowHeight = 64;

static SDL_Window *mainWindow = nullptr;
static SDL_Renderer *mainRenderer = nullptr;

constexpr uint32_t makeABGR(uint8_t r, uint8_t g, uint8_t b, uint8_t a, TGAColor &outTgaColor) {
    outTgaColor = TGAColor{b, g, r, a};
    return (uint32_t(a) << 24) | (uint32_t(b) << 16) | (uint32_t(g) << 8) | r;
}

constexpr uint32_t makeABGR(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    return (uint32_t(a) << 24) | (uint32_t(b) << 16) | (uint32_t(g) << 8) | r;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){
    SDL_SetAppMetadata(title, "1.0", "com.application.bare-renderer");

    if (!SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(title, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE, &mainWindow, &mainRenderer)){
        std::cerr << "Couldn't initialize window or renderer: " << SDL_GetError() << std::endl;
        return  SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(mainRenderer, windowWidth, windowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
    if (event->type == SDL_EVENT_QUIT){
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
    TGAImage framebuffer(windowWidth, windowHeight, TGAImage::RGBA);
    SDL_Texture *framebufferTexture = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

    int *pixels = NULL;
    int pitch;
    SDL_LockTexture(framebufferTexture, NULL, (void **) &pixels, &pitch);

    for (int y = 0; y < windowHeight; ++y){
        for (int x = 0; x < windowWidth; ++x){
            if (pixels != nullptr)
            {
                int idx = windowWidth * y + x;
                TGAColor color;
                pixels[idx] = makeABGR(rand(), rand(), rand(), rand(), color);
                framebuffer.set(x, y, color);
            } else{
                std::cerr << "Pixels pointer is NULL" << std::endl;
            }
        }
    }

    SDL_UnlockTexture(framebufferTexture);

    SDL_RenderTexture(mainRenderer, framebufferTexture, NULL, NULL);
    framebuffer.write_tga_file("framebuffer.tga");
    SDL_RenderPresent(mainRenderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){

}