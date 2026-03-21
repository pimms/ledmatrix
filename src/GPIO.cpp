#include "GPIO.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <stdexcept>

namespace {
const uint64_t MEM_PERIPHERAL   = 0x3F000000;
const uint64_t GPIO_REG_OFFSET  = 0x00200000; 

const size_t MAP_SIZE           = 4096;
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
    _gpioSetBits = _gpio + (0x1C / sizeof(uint32_t));
    _gpioClearBits = _gpio + (0x28 / sizeof(uint32_t));
}

GPIO::~GPIO()
{
    if (_gpio) {
        munmap((void*)_gpio, MAP_SIZE);
    }
}
