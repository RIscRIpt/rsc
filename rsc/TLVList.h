#pragma once

#include "TLV.h"

#include <vector>

#include <scb/Bytes.h>

namespace rsc {

    class TLVList : public std::vector<TLV> {
    public:
        TLVList(scb::Bytes const &buffer);
        TLVList(scb::Bytes::const_iterator buffer_begin, std::vector<unsigned char>::const_iterator buffer_end);

    private:
        static std::vector<TLV> from_bytes(scb::Bytes const &buffer);
        static std::vector<TLV> from_bytes_range(scb::Bytes::const_iterator buffer_begin, std::vector<unsigned char>::const_iterator buffer_end);

    };

}
