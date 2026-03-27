#include "HZellerRenderer.h"
#include <stdexcept>
#include <array>

std::unique_ptr<Renderer> Renderer::create()
{
    return std::make_unique<HZellerRenderer>();
}


HZellerRenderer::HZellerRenderer()
{
    rgb_matrix::RGBMatrix::Options opts;
    opts.hardware_mapping = "adafruit-hat";
    opts.rows = 32;
    opts.cols = 64;
    opts.chain_length= 1;
    opts.parallel = 1;
    opts.show_refresh_rate = false;
    rgb_matrix::RuntimeOptions runtimeOpts{};
    _canvas = std::unique_ptr<rgb_matrix::RGBMatrix>{ rgb_matrix::RGBMatrix::CreateFromOptions(opts, {}) };
    if (!_canvas) {
        throw std::runtime_error("Failed to create canvas");
    }
}

void HZellerRenderer::render(const std::array<Color,64*32> &buffer)
{
    for (int y=0; y<32; y++) {
        for (int x=0; x<64; x++) {
            const Color* c = &buffer[y*64 + x];
            _canvas->SetPixel(x, y, c->r, c->g, c->b);
        }
    }
}


