#pragma once

#include "TLV.h"

#include <vector>

#include <scb/bytes.h>

namespace rsc {

    class TLVList {
    public:
        explicit TLVList(scb::Bytes const &buffer);
        TLVList(scb::Bytes::const_iterator buffer_begin, std::vector<unsigned char>::const_iterator buffer_end);

        inline size_t size() const noexcept { return tlvs_.size(); }
        inline TLV const& operator[](size_t index) const { return tlvs_.at(index); }

    private:
        std::vector<TLV> tlvs_;
    };

}
