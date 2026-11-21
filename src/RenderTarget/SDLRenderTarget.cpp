//
// Created by ivan_miatselski on 2026-11-21.
//

#include "RenderTarget/SDLRenderTarget.hpp"

#include "iostream"

namespace BR {

SDLRenderTarget::SDLRenderTarget(int w, int h, SDL_Renderer *newRenderer, const SDL_PixelFormat &format):
textureWidth(w),
textureHeight(h),
renderer(newRenderer)
{
    framebuffer = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, w, h);
    SDL_LockTexture(framebuffer, nullptr, (void**) &pixels, &pitch);
}

void SDLRenderTarget::setPixel(int x, int y, const ColorRGBA &color) {
    if (textureWidth < 0 || pixels == nullptr || pitch < 0){
        std::cout << "Check parameters after sdl texture lock" << std::endl;
        return;
    }

    int idx = textureWidth * y + x;
    pixels[idx] = SDLRenderTarget::makeABGR(color.r, color.g, color.b, color.a);
}

uint32_t SDLRenderTarget::makeABGR(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (uint32_t(a) << 24) | (uint32_t(b) << 16) | (uint32_t(g) << 8) | r;
}

void SDLRenderTarget::renderTarget() {
    unlockTexture();
    SDL_RenderTexture(renderer, framebuffer, nullptr, nullptr);
}

void SDLRenderTarget::unlockTexture() {
    SDL_UnlockTexture(framebuffer);
    pixels = nullptr;
    pitch = -1;
}

void SDLRenderTarget::setNewRenderer(SDL_Renderer *newRenderer) {
    renderer = newRenderer;
}

}