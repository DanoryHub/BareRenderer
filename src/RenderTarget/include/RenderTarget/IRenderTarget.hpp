//
// Created by ivan_miatselski on 2026-11-19.
//

#ifndef BARERENDERER_IRENDERTARGET_HPP
#define BARERENDERER_IRENDERTARGET_HPP

#include <cstdint>

namespace BR {

struct ColorRGBA{
    uint8_t r, g, b, a;
};

class IRenderTarget{
public:
    virtual void setPixel(int x, int y, const ColorRGBA &color) = 0;
    virtual void renderTarget() = 0;
};

}
#endif //BARERENDERER_IRENDERTARGET_HPP
