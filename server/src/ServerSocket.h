#pragma once

#include <thread>
#include <atomic>
#include <functional>

class ServerSocket 
{
public:
    ServerSocket(std::function<void(const uint8_t*,size_t)> dataCallback);
    ~ServerSocket();

    ServerSocket(const ServerSocket&) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;
    ServerSocket& operator=(ServerSocket&&) = delete;

private:
    std::thread _thread;
    std::atomic_bool _active;
    int _socket;
    std::function<void(const uint8_t*,size_t)> _dataCallback;

    void receiveLoop();
};
