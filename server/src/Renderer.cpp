#include "Renderer.h"

#include <cassert>

Renderer::Renderer()
{
    _runRenderLoop = true;
    _renderThread = std::thread([&]() {
        this->renderLoop();
    });
}

Renderer::~Renderer()
{
    if (_renderThread.joinable()) {
        _runRenderLoop = false;
        _cv.notify_all();
        _renderThread.join();
    }
}

void Renderer::bufferReady(const std::array<Color, 64 * 32> &buffer)
{
    std::lock_guard lock(_mutex);
    const uint64_t nextBuf = _bufferNo.load() + 1;
    _buffers[nextBuf % 2] = buffer;
    _bufferNo++;
    _cv.notify_one();
}

void Renderer::renderLoop()
{
    uint64_t currentBufferNo = 0;
    while (_runRenderLoop.load()) {
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cv.wait(lock, [&]{ return !_runRenderLoop.load() || _bufferNo.load() > currentBufferNo; });

            if (!_runRenderLoop.load()) {
                return;
            }

            currentBufferNo = _bufferNo.load();
        }
        const auto buffer = &_buffers[currentBufferNo % 2];
        render(buffer);
    }
}
