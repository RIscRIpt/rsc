#pragma once

#include <vector>
#include <cstdint>

#include <scb/Bytes.h>

namespace rsc {

    class Tag {
    public:
        enum {
            MASK_CLASS         = 0b11000000,
            MASK_CONSTRUCTED   = 0b00100000,
            MASK_TAG_NUMBER_0  = 0b00011111,
            MASK_TAG_NUMBER_N  = 0b01111111,
            MASK_TAG_NEXT_BYTE = 0b10000000,
            MULTI_BYTE_TAG     = 31,
            NUMBER_BITS        = 7,
        };

        enum class Class : unsigned char {
            Universal       = 0b00 << 6,
            Application     = 0b01 << 6,
            ContextSpecific = 0b10 << 6,
            Private         = 0b11 << 6,
        };

        explicit Tag(unsigned char const *buffer);
        Tag(uint16_t tag);

        inline Class cls() const noexcept { return static_cast<Class>(tag_[0] & MASK_CLASS); }
        inline bool is_constructed() const noexcept { return tag_[0] & MASK_CONSTRUCTED; }
        inline bool is_primitive() const noexcept { return !is_constructed(); }
        inline size_t size() const noexcept { return tag_.size(); }

        inline bool operator==(Tag const &rhs) { return tag_ == rhs.tag_; }
        inline bool operator!=(Tag const &rhs) { return tag_ != rhs.tag_; }

        inline scb::Bytes const& bytes() const noexcept { return tag_; }

        uintptr_t number() const noexcept;

        uintptr_t value() const noexcept;
        inline operator uintptr_t() const noexcept { return value(); }

    private:
        scb::Bytes tag_;
    };

}
