#pragma once

#include <stdint.h>

class GPIO
{
public:
    GPIO();
    ~GPIO();

    GPIO(GPIO&&) = delete;
    GPIO(const GPIO&) = delete;
    GPIO& operator=(GPIO&&) = delete;
    GPIO& operator=(const GPIO&) = delete;

private:
    volatile uint32_t* _gpio = nullptr;
    volatile uint32_t* _gpioSet = nullptr;
    volatile uint32_t* _gpioClr = nullptr;
};
