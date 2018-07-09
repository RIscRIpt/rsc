#pragma once

#include "TLVList.h"

#include <vector>
#include <cstdint>

namespace rsc {

    class rAPDU {
    public:
        explicit rAPDU(size_t Le = 256);

        uint16_t SW() const noexcept;
        uint8_t SW1() const noexcept;
        uint8_t SW2() const noexcept;

        void resize(size_t actual_length);
        TLVList tlv_list() const;

        inline std::vector<unsigned char>& buffer() noexcept { return buffer_; }

    private:
        std::vector<unsigned char> buffer_;
    };

}
