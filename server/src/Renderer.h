#pragma once

#include <memory>

struct Color
{
    Color() { r = g = b = 0; }
    Color(uint8_t rr, uint8_t gg, uint8_t bb) :r(rr), g(gg), b(bb) {}
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Renderer
{
public:
    static std::unique_ptr<Renderer> create();

    Renderer() {}
    virtual ~Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    virtual void render(const std::array<Color,64*32>&) = 0;
};
