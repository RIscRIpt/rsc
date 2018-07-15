#pragma once

#include "TL.h"

#include <vector>

#include <scb/Bytes.h>

namespace rsc {

    class TLVList;

    class TLV : TL {
    public:
        explicit TLV(unsigned char const *buffer);

        inline size_t size() const noexcept { return tag_.size() + length_.size() + value_.size(); }
        inline scb::Bytes value() const noexcept { return value_; }
        TLVList value_as_tlv_list() const;

    private:
        scb::Bytes value_;
    };

}
