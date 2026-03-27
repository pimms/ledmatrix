#pragma once

#include "../include/Renderlib.h"
#include "led-matrix.h"

class HZellerRenderer: public Renderer
{
public:
    HZellerRenderer();
    void render(const std::array<Color,64*32>&) override;

private:
    std::unique_ptr<rgb_matrix::Canvas> _canvas;
};
