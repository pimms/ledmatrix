#pragma once

#include <mutex>
#include <condition_variable>

class SignalHandler
{
public:
    SignalHandler& operator=(const SignalHandler&) = delete;
    SignalHandler& operator=(SignalHandler&&) = delete;
    SignalHandler(const SignalHandler&) = delete;

    static int awaitTheEndOfTheWorld();
    static void signalReceived(int sig);

private:
    SignalHandler();
    ~SignalHandler() = default;

    static SignalHandler s_instance;

    static std::mutex s_mutex;
    static std::condition_variable s_cv;
    static std::atomic_int s_signal;
};
