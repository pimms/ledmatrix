#pragma once

#include <condition_variable>
#include <memory>
#include <array>

struct Color
{
    Color() { r = g = b = 0; }
    Color(uint8_t rr, uint8_t gg, uint8_t bb) :r(rr), g(gg), b(bb) {}
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Renderer
{
public:
    static std::unique_ptr<Renderer> create();

    Renderer();
    virtual ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void bufferReady(const std::array<Color,64*32>&);

protected:
    virtual void render(const std::array<Color,64*32>*) = 0;

private:
    std::condition_variable _cv;
    std::mutex _mutex;

    std::thread _renderThread;
    std::atomic_bool _runRenderLoop;

    std::atomic<uint64_t> _bufferNo = 0;
    std::atomic_bool _consumerCopying = false;

    std::array<std::array<Color,64*32>, 2> _buffers;

    void renderLoop();
};
