//
// Created by ivan_miatselski on 2026-11-19.
//

#ifndef BARERENDERER_TGARENDERTARGET_HPP
#define BARERENDERER_TGARENDERTARGET_HPP

#include <iostream>

#include "IRenderTarget.hpp"
#include "tgaimage/tgaimage.h"

namespace BR {

class TGARenderTarget : public BR::IRenderTarget {
public:
    TGARenderTarget(int w, int h, const TGAImage::Format &colorMode);
    void setFilePath(const std::string &path);
    void setPixel(int x, int y, const ColorRGBA &color) override;
    void renderTarget() override;

private:
    TGAImage framebuffer;
    std::string fileOutPath;
};

}
#endif //BARERENDERER_TGARENDERTARGET_HPP
