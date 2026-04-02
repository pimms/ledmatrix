#include <stdio.h>
#include "Renderer.h"
#include "ServerSocket.h"
#include <array>


#ifdef _WIN32
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

int main()
{
    startWinsock();

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
