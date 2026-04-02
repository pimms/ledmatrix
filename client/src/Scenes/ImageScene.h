#pragma once

#include "Scene.h"

class ImageScene: public Scene {
public:
    const std::array<Color, 2048>* render() override;
    bool active() const override;

private:
    std::array<Color, 2048> _buffer;
    bool _active = true;
};
