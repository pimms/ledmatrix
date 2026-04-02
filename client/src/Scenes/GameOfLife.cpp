#include "GameOfLife.h"

#include <chrono>
#include <random>

GameOfLife::GameOfLife()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);

    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            _cells[y][x] = static_cast<bool>(dist(gen));
        }
    }
}

const std::array<Color,2048>* GameOfLife::render()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::array<std::array<int, 64>, 32> neighbours{};
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (!_cells[y][x]) {
                continue;
            }

            if (y > 0) neighbours[y - 1][x]++;
            if (y < 31) neighbours[y + 1][x]++;
            if (x > 0) neighbours[y][x - 1]++;
            if (x < 63) neighbours[y][x + 1]++;

            if (y > 0 && x > 0) neighbours[y - 1][x - 1]++;
            if (y > 0 && x < 63) neighbours[y - 1][x + 1]++;
            if (y < 31 && x > 0) neighbours[y + 1][x - 1]++;
            if (y < 31 && x < 63) neighbours[y + 1][x + 1]++;
        }
    }

    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            switch (neighbours[y][x]) {
            case 2: 
                _cells[y][x] = _cells[y][x];
                break;
            case 3:
                _cells[y][x] = true;
                break;
            default:
                _cells[y][x] = false;
            }

            if (_cells[y][x]) {
                _sbuffer[y * 64 + x] = { 255, 255, 255 };
            } else {
                _sbuffer[y * 64 + x] = { 0, 0, 0 };
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = (end - start);
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
    double ms = static_cast<double>(ns.count()) / 1000000.0;
    printf("frametime: %g ms\n", ms);

    return &_sbuffer;
}

bool GameOfLife::active() const
{
    return true;
}
