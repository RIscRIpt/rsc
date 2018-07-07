#pragma once

#include "TLV.h"

#include <vector>

namespace rsc {

    class TLVList
    {
    public:
        TLVList(std::vector<unsigned char> const &buffer);

        inline size_t size() const noexcept { return tlvs_.size(); }
        inline TLV const& operator[](size_t index) const { return tlvs_.at(index); }

    private:
        std::vector<TLV> tlvs_;
    };

}
