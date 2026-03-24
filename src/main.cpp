#include <stdio.h>
#include <array>
#include <unistd.h>

#include <Renderlib.h>

int main(int argc, const char **argv)
{
    auto renderer = Renderer::create();

    std::array<Color, 64*32> buf;

    for (int i = 1; i<64*32; i++) {
        buf[i-1] = {0, 0, 0};
        buf[i] = {255, 255, 255};
        renderer->render(buf);
        usleep(50000);
    }

    printf("hi mom\n");
    return 0;
}
