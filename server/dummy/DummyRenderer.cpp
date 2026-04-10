#include "Renderer.h"
#include <memory>
#include <stdio.h>
#include <string.h>
#include <array>
#include <cassert>

class DummyRenderer: public Renderer
{
public:
    void render(const std::array<Color, 64*32>& buffer) override;

private:
    inline void printGrayscale(const Color* color) const;
    inline void printRgb(const Color* color) const;
};

std::unique_ptr<Renderer> Renderer::create()
{
    return std::make_unique<DummyRenderer>();
}

void DummyRenderer::render(const std::array<Color, 64*32>& buffer)
{
    printf("\033[32A\033[J");
    for (int y=0; y<32; y++) {
        for (int x=0; x<64; x++) {
            const Color* c = &buffer[y*64 + x];
            printRgb(c);
        }
        printf("\n");
    }
}

inline void DummyRenderer::printGrayscale(const Color* c) const
{
    static const char *map = " .-=#%$";
    static const int maplen = strlen(map);
    const int lum = (c->r + c->g + c->b);
    const int idx = lum / ((255*3) / (maplen-1));
    assert(idx < maplen);
    printf("%c%c", map[idx], map[idx]);
}

inline void DummyRenderer::printRgb(const Color* c) const
{
    printf("\e[38;2;%d;%d;%dm██", c->r, c->g, c->b);
}
