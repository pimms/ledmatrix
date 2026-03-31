#include "ClientSocket.h"
#include <stdio.h>
#include <array>
#include <thread>

#include "Color.h"
#include "Scenes/Scene.h"
#include "Scenes/GameOfLife.h"

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

int main(int argc, const char **argv)
{
    startWinsock();

    if (argc != 2) {
        printf("Usage: %s <ipaddr>\n", argv[0]);
        return 1;
    }

    ClientSocket socket(argv[1]);
    GameOfLife scene;

    while (true) {
        auto buffer = scene.render();
        socket.send(buffer, sizeof(*buffer));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}
