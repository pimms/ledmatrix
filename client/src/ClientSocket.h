#pragma once

#include <string>
#include <netinet/in.h>

class ClientSocket
{
public:
    ClientSocket(const std::string& ipaddr);
    ~ClientSocket();

    ClientSocket(const ClientSocket&) = delete;
    ClientSocket& operator=(const ClientSocket&) = delete;
    ClientSocket& operator=(const ClientSocket&&) = delete;

    void send(const void* buf, size_t len);

private:
    int _socket{};
    sockaddr_in _addr{};
};
