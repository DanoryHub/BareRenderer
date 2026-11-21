//
// Created by ivan_miatselski on 2026-11-19.
//

#include "RenderTarget/TGARenderTarget.hpp"

namespace BR{

TGARenderTarget::TGARenderTarget(int w, int h, const TGAImage::Format &colorMode) {
    framebuffer = TGAImage(w, h, colorMode);
}

void TGARenderTarget::setFilePath(const std::string &path) {
    fileOutPath = path;
}

void TGARenderTarget::setPixel(int x, int y, const ColorRGBA &color) {
    framebuffer.set(x, y,TGAColor{ color.b, color.g, color.r, color.a });
}

void TGARenderTarget::renderTarget() {
    framebuffer.write_tga_file(fileOutPath);
}

}