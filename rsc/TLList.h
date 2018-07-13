#pragma once

#include "TL.h"

#include <vector>

#include <scb/bytes.h>

namespace rsc {

    class TLList {
    public:
        explicit TLList(scb::Bytes const &buffer);
        TLList(scb::Bytes::const_iterator buffer_begin, scb::Bytes::const_iterator buffer_end);

        inline size_t size() const noexcept { return tls_.size(); }
        inline TL const& operator[](size_t index) const { return tls_.at(index); }

    private:
        std::vector<TL> tls_;
    };

}
