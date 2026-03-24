#include "GPIO.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <stdexcept>

namespace {
const uint64_t MEM_PERIPHERAL   = 0x3F000000;
const uint64_t GPIO_REG_OFFSET  = 0x00200000; 

const size_t MAP_SIZE           = 4096;

const uint32_t PIN_OE   = 4;
const uint32_t PIN_CLK  = 17;
const uint32_t PIN_STRB = 21;
const uint32_t PIN_A    = 22;
const uint32_t PIN_B    = 26;
const uint32_t PIN_C    = 27;
const uint32_t PIN_D    = 20;
const uint32_t PIN_R1   = 5;
const uint32_t PIN_G1   = 13;
const uint32_t PIN_B1   = 6;
const uint32_t PIN_R2   = 12;
const uint32_t PIN_G2   = 16;
const uint32_t PIN_B2   = 23;

}

GPIO::GPIO()
{
    const int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (!fd) {
        throw std::runtime_error("Failed to open /dev/mem");
    }

    uint32_t* res = (uint32_t*)mmap(
        NULL,
        MAP_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        MEM_PERIPHERAL + GPIO_REG_OFFSET
    );

    close(fd);

    if (res == MAP_FAILED) {
        throw std::runtime_error("Failed to memory-map peripheral memory");
    }

    _gpio = res;
    _gpioSet = _gpio + (0x1C / sizeof(uint32_t));
    _gpioClr = _gpio + (0x28 / sizeof(uint32_t));
}

GPIO::~GPIO()
{
    if (_gpio) {
        munmap((void*)_gpio, MAP_SIZE);
    }
}
