#include "ImageScene.h"

#include <CImg.h>

using namespace cimg_library;

const std::array<Color, 2048>* ImageScene::render()
{
    auto img = cimg_library::CImg<uint8_t>("%USERPROFILE%/Desktop/owl.jfif");

    // TODO: Fill the buffer with the image

    _hasRendered = true;
    return &_buffer;
}

bool ImageScene::active() const
{
    return !_hasRendered;
}

