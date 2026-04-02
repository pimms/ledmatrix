#pragma once

#include <array>
#include "../Color.h"

class Scene
{
public:
    virtual ~Scene() = default;
    virtual const std::array<Color, 2048>* render() = 0;
    virtual bool active() const = 0;
};
