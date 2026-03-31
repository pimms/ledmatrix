#include "ClientSocket.h"
#include <stdio.h>
#include <array>
#include <thread>

#ifdef WIN32
#include <cassert>
#include <WinSock2.h>
void startWinsock()
{
    WSADATA data;
    WORD version = MAKEWORD(2,2);
    const int wsres = WSAStartup(version, &data);
    assert(wsres == 0);
}
#else
void startWinsock() {}
#endif

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int main(int argc, const char **argv)
{
    startWinsock();

    if (argc != 2) {
        printf("Usage: %s <ipaddr>\n", argv[0]);
        return 1;
    }

    std::array<Color, 64*32> buf{};

    ClientSocket socket(argv[1]);
    while (true) {
        printf("filling\n");
        for (int i=0; i<32*64; i++) {
            buf[i] = Color { 20, 20, 20};
            socket.send(buf.data(), sizeof(buf));
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf("clearing\n");
        for (int i=0; i<32*64; i++) {
            buf[i] = Color { 0, 0, 0 };
            socket.send(buf.data(), sizeof(buf));
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
