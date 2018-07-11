#pragma once

#include "TL.h"

#include <vector>

namespace rsc {

    class TLList {
    public:
        explicit TLList(std::vector<unsigned char> const &buffer);
        TLList(std::vector<unsigned char>::const_iterator buffer_begin, std::vector<unsigned char>::const_iterator buffer_end);

        inline size_t size() const noexcept { return tls_.size(); }
        inline TL const& operator[](size_t index) const { return tls_.at(index); }

    private:
        std::vector<TL> tls_;
    };

}
