#pragma once

#include <cstdint>

namespace rsc {

    class SW {
    public:
        SW(uint16_t value)
            : value(value)
        {}

        uint16_t const value;

        inline operator uint16_t() const noexcept { return value; }

        inline uint8_t SW1() const noexcept { return value >> 8; }
        inline uint8_t SW2() const noexcept { return value & 0xFF; }

        inline uint8_t response_bytes_still_available() const noexcept { if (SW1() == 0x61) return SW2(); return 0; }
        inline bool wrong_length() const noexcept { return SW1() == 0x6C; }
    };

}
