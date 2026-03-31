#pragma once

#include "Scene.h"

class GameOfLife: public Scene
{
public:
    GameOfLife();

    GameOfLife(const GameOfLife&) = delete;
    GameOfLife& operator=(const GameOfLife&) = delete;
    GameOfLife& operator=(GameOfLife&&) = delete;

    const std::array<Color, 2048>* render() override;

private:
    std::array<Color, 2048> _sbuffer;
    std::array<std::array<bool, 64>, 32> _cells;
};