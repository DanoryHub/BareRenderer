#define SDL_MAIN_USE_CALLBACKS 1

#include <memory>
#include <iostream>

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

const char *title = "BareRenderer";
const uint16_t windowWidth = 64;
const uint16_t windowHeight = 64;

static SDL_Window *mainWindow = nullptr;
static SDL_Renderer *mainRenderer = nullptr;


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
    SDL_Texture *framebufferTexture = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, windowHeight, windowWidth);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);


//
//    SDL_LockTexture(framebufferTexture, nullptr)
//
//    SDL_RenderClear(mainRenderer);
    SDL_RenderPresent(mainRenderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){

}