#include "ClientSocket.h"
#include <stdio.h>
#include <thread>

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int main(int argc, const char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <ipaddr>\n", argv[0]);
        return 1;
    }

    std::array<Color, 64*32> buf{};

    ClientSocket socket(argv[1]);
    for (int i=0; i<32*64; i++) {
        buf[i] = Color { 255, 255, 255 };
        socket.send(buf.data(), sizeof(buf));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
