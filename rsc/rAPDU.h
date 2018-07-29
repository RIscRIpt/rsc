#pragma once

#include "TLVList.h"
#include "SW.h"

#include <vector>
#include <cstdint>

#include <scb/Bytes.h>

namespace rsc {

    class rAPDU {
    public:
        explicit rAPDU(size_t Le = 254);

        rAPDU(rAPDU const &other) = default;
        rAPDU(rAPDU &&other) = default;

        rAPDU& operator=(rAPDU const &rhs) = default;
        rAPDU& operator=(rAPDU &&rhs) = default;

        SW SW() const noexcept;
        uint8_t SW1() const noexcept;
        uint8_t SW2() const noexcept;

        void resize(size_t actual_length);
        TLVList tlv_list() const;

        inline scb::Bytes& buffer() noexcept { return buffer_; }
        inline scb::Bytes const& buffer() const noexcept { return buffer_; }

    private:
        scb::Bytes buffer_;
    };

}

std::ostream& operator<<(std::ostream &os, rsc::rAPDU const &rapdu);
