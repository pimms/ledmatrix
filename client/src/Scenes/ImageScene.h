#pragma once

#include "Scene.h"
#include <string>

class ImageScene: public Scene {
public:
    ImageScene(const std::string_view filepath);

    const std::array<Color, 2048>* render() override;
    bool active() const override;

private:
    std::string _filepath;
    std::array<Color, 2048> _buffer;
    bool _active = true;
};
