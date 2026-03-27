#include <stdio.h>
#include "Renderer.h"
#include "ServerSocket.h"

int main()
{
    auto renderer = Renderer::create();
    std::array<Color, 64*32> screenbuffer;

    ServerSocket socket(
        [&](auto buf, auto len) {
            if (len != 64*32*3) {
                printf("discard\n");
                return;
            }
            for (int i=0; i<64*32; i++) {
                screenbuffer[i] = *((Color*)&buf[i*3]);
            }
            renderer->render(screenbuffer);
        }
    );
    printf("serverboi\n");

    while (true) {};
    return 0;
}
