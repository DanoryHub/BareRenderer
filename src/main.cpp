#define SDL_MAIN_USE_CALLBACKS 1

#include <memory>
#include <iostream>

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3/SDL_render.h"

#include "RenderTarget/TGARenderTarget.hpp"
#include "RenderTarget/SDLRenderTarget.hpp"

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
    BR::TGARenderTarget tgaTarget(windowWidth, windowHeight, TGAImage::RGBA);
    BR::SDLRenderTarget sdlTarget(windowWidth, windowHeight, mainRenderer, SDL_PIXELFORMAT_ABGR8888);

    for (int y = 0; y < windowHeight; ++y){
        for (int x = 0; x < windowWidth; ++x){
            BR::ColorRGBA colorRGBA(rand(), rand(), rand(), rand());
            sdlTarget.setPixel(x, y, colorRGBA);
            tgaTarget.setPixel(x, y, colorRGBA);
        }
    }

    tgaTarget.setFilePath("framebuffer.tga");

    tgaTarget.renderTarget();
    sdlTarget.renderTarget();

    SDL_RenderPresent(mainRenderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){

}