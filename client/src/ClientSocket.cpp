#include "ClientSocket.h"

#include <cassert>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

ClientSocket::ClientSocket(const std::string& ipaddr)
{
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    assert(_socket > 0);

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(6969);
    _addr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
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
    sendto(_socket, (const void*)buf, len, 0, (const sockaddr*)&_addr, sizeof(_addr));
}
