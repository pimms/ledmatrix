#include "SignalHandler.h"

#include <csignal>
#include <functional>

SignalHandler SignalHandler::s_instance;
std::mutex SignalHandler::s_mutex;
std::condition_variable SignalHandler::s_cv;
std::atomic_int SignalHandler::s_signal = 0;

static void signalHandler(int signal)
{
    SignalHandler::signalReceived(signal);
}

SignalHandler::SignalHandler()
{
    std::signal(SIGINT, &signalHandler);
    std::signal(SIGTERM, &signalHandler);
    std::signal(SIGABRT, &signalHandler);
    std::signal(SIGSEGV, &signalHandler);
}

int SignalHandler::awaitTheEndOfTheWorld()
{
    std::unique_lock<std::mutex> lock(s_mutex);
    s_cv.wait(lock, [&]() { return s_signal.load() != 0; });
    return s_signal.load();
}

void SignalHandler::signalReceived(int sig)
{
    s_signal = sig;
    s_cv.notify_all();
}
