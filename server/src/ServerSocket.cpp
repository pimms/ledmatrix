#include "ServerSocket.h"

#include <cassert>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

ServerSocket::ServerSocket(std::function<void(const uint8_t*,size_t)> dataCallback)
    : _active(true)
    , _socket(0)
    , _dataCallback(dataCallback)
{
    sockaddr_in serverAddr;

    const int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sockfd > 0);

    memset(&serverAddr, 0, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(6969);

    const int res = bind(sockfd, (const sockaddr*)&serverAddr, sizeof(serverAddr));
    assert(res == 0);

    _socket = sockfd;
    _thread = std::thread([&](){ this->receiveLoop(); });
}

ServerSocket::~ServerSocket()
{
    _active = false;
    if (_thread.joinable()) {
        _thread.join();
    }
}

void ServerSocket::receiveLoop()
{
    constexpr size_t BUFLEN = 8096;
    uint8_t buffer[BUFLEN];
    while (_active) {
        sockaddr_in clientAddr;
        socklen_t clientLen = 0;
        const ssize_t len = recvfrom(_socket, (void*)&buffer, BUFLEN, 0, (sockaddr*)&clientAddr, &clientLen);
        if (len < 0) {
            printf("failed to receive data\n");
            continue;
        }
        printf("received %ld bytes\n", len);
        _dataCallback(buffer, len);
    }
}
