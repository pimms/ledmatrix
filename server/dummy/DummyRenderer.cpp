#include "Renderer.h"
#include <memory>
#include <stdio.h>
#include <array>
#include <cassert>

class DummyRenderer: public Renderer
{
public:
    void render(const std::array<Color, 64*32>& buffer) override;
};

std::unique_ptr<Renderer> Renderer::create()
{
    return std::make_unique<DummyRenderer>();
}

void DummyRenderer::render(const std::array<Color, 64*32>& buffer)
{
    static const char *map = " .-=#%$";
    static const int maplen = strlen(map);

    printf("\033[32A\033[J");
    for (int y=0; y<32; y++) {
        for (int x=0; x<64; x++) {
            const Color* c = &buffer[y*64 + x];
            const int lum = (c->r + c->g + c->b);
            const int idx = lum / ((255*3) / (maplen-1));
            assert(idx < maplen);
            printf("%c", map[idx]);
        }
        printf("\n");
    }
}
