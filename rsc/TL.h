#pragma once

#include "Tag.h"
#include "Length.h"

#include <vector>

#include <scb/Bytes.h>

namespace rsc {

    class TL {
    public:
        explicit TL(unsigned char const *buffer);

        inline size_t size() const noexcept { return tag_.size() + length_.size(); }
        inline Tag const& tag() const noexcept { return tag_; }
        inline Length const& length() const noexcept { return length_; }

    protected:
        Tag tag_;
        ::rsc::Length length_;
    };

}
