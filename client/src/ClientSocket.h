#pragma once

#include <string>

#ifdef _WIN32
    #include <WinSock2.h>
    typedef int socklen_t;
    typedef SOCKET socket_t;
    #ifndef __MINGW32__
        typedef int ssize_t;
    #endif
#else
    #include <netinet/in.h>
    typedef int socket_t;
#endif

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
    socket_t _socket{};
    sockaddr_in _addr{};
};
