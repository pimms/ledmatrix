#include "ImageScene.h"

#define cimg_use_jpeg
#include <CImg.h>

const std::array<Color, 2048>* ImageScene::render()
{
    cimg_library::cimg::exception_mode(0);

    const char* filepath = "C:/Users/Joakim Stien/Desktop/dogg.jpg";

    auto img = cimg_library::CImg<uint8_t>(filepath); 

    const int pxf = img.width() / 64;
    const double imgar = static_cast<double>(img.width()) / static_cast<double>(img.height());

    int offx = 0;
    int offy = 0;

    if (imgar > 2) {
        const int windowWidth = img.height() * 2;
        offx = (img.width() - windowWidth) / 2;
        offy = 0;
    } else {
        const int windowHeight = img.width() / 2;
        offx = 0;
        offy = (img.height() - windowHeight) / 2;
    }

    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            const int sx = offx + (x * pxf);
            const int sy = offy + (y * pxf);

            uint32_t r = 0;
            uint32_t g = 0;
            uint32_t b = 0;

            for (int iy = 0; iy < pxf; iy++) {
                for (int ix = 0; ix < pxf; ix++) {
                    r += img.atXY(sx + ix, sy + iy, 0, 0);
                    g += img.atXY(sx + ix, sy + iy, 0, 1);
                    b += img.atXY(sx + ix, sy + iy, 0, 2);
                }
            }

            r /= (pxf * pxf);
            g /= (pxf * pxf);
            b /= (pxf * pxf);
            _buffer[((31 - y) * 64) + x] = { 
                static_cast<uint8_t>(r), 
                static_cast<uint8_t>(g), 
                static_cast<uint8_t>(b), 
            };
        }
    }

    _active = false;
    return &_buffer;
}

bool ImageScene::active() const
{
    return _active;
}

