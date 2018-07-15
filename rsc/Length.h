#pragma once

#include <vector>

#include <scb/Bytes.h>

namespace rsc {

    class Length {
    public:
        enum {
            IS_NUMBER_OF_BYTES = 0x80,
            MASK_NUMBER_OF_BYTES = 0x7F,
        };

        Length(unsigned char const *buffer);

        inline scb::Bytes const& bytes() const noexcept { return bytes_; }
        inline size_t size() const noexcept { return bytes_.size(); }
        inline size_t value() const noexcept { return value_; }
        inline operator size_t() const noexcept { return value_; }

    private:
        scb::Bytes bytes_;
        size_t value_;
    };

}
