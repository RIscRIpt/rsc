#pragma once

#include "Tag.h"
#include "Length.h"

#include <vector>

namespace rsc {

    class TLV
    {
    public:
        TLV(unsigned char const *buffer);

        inline size_t size() const noexcept { return tag_.size() + length_.size() + value_.size(); }
        inline Tag const& tag() const noexcept { return tag_; }
        inline size_t length() const noexcept { return length_.value(); }
        inline Length const& Length() const noexcept { return length_; }
        inline std::vector<unsigned char> value() const noexcept { return value_; }
        TLV value_as_tlv() const;

    private:
        Tag tag_;
        ::rsc::Length length_;
        std::vector<unsigned char> value_;
    };

}
