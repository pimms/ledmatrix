#pragma once

#include <thread>
#include <atomic>
#include <functional>

#ifdef _WIN32
#include <WinSock2.h>
typedef int socklen_t;
typedef int ssize_t;
typedef SOCKET socket_t;
#else
typedef int socket_t;
#endif

class ServerSocket 
{
public:
    explicit ServerSocket(std::function<void(const uint8_t*,size_t)> dataCallback);
    ~ServerSocket();

    ServerSocket(const ServerSocket&) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;
    ServerSocket& operator=(ServerSocket&&) = delete;

private:
    std::thread _thread;
    std::atomic_bool _active;
    socket_t _socket;
    std::function<void(const uint8_t*,size_t)> _dataCallback;

    void receiveLoop();
};
