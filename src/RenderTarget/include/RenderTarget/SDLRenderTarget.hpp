//
// Created by ivan_miatselski on 2026-11-21.
//

#ifndef BARERENDERER_SDLRENDERTARGET_HPP
#define BARERENDERER_SDLRENDERTARGET_HPP
#include <memory>

#include "SDL3/SDL.h"
#include "SDL3/SDL_render.h"

#include "RenderTarget/IRenderTarget.hpp"

namespace BR {

class SDLRenderTarget: public IRenderTarget{
public:
    SDLRenderTarget(int w, int h, SDL_Renderer *newRenderer, const SDL_PixelFormat &format);
    void setPixel(int x, int y, const ColorRGBA &color) override;
    void renderTarget() override;
    void setNewRenderer(SDL_Renderer *newRenderer);
protected:
    SDL_Texture *framebuffer;
    int textureWidth = -1;
    int textureHeight = -1;
    uint32_t *pixels = nullptr;
    int pitch = -1;
    SDL_Renderer *renderer;

    void unlockTexture();
    static uint32_t makeABGR(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
};

}
#endif //BARERENDERER_SDLRENDERTARGET_HPP
