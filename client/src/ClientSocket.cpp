#include "ClientSocket.h"

#include <cassert>

#ifdef _WIN32
#include <WS2tcpip.h>
#define close(_S) closesocket(_S)
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

ClientSocket::ClientSocket(const std::string& ipaddr)
{
    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    assert(_socket > 0);

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(6969);

#ifdef _WIN32
    inet_pton(AF_INET, ipaddr.c_str(), &_addr.sin_addr);
#else
    _addr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
#endif
}

ClientSocket::~ClientSocket()
{
    if (_socket > 0) {
        close(_socket);
    }
}

void ClientSocket::send(const void* buf, size_t len)
{
    assert(_socket > 0);
    assert(buf);
    assert(len > 0 && len <= 8096);

#ifdef _WIN32
    const char* castedBuf = (const char*)buf;
#else
    const void* castedBuf = buf;
#endif

    const int res = sendto(_socket, castedBuf, len, 0, (const sockaddr*)&_addr, sizeof(_addr));
    assert(res == len);
}
