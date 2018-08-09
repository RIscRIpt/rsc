#include "TLVList.h"

using namespace rsc;

TLVList::TLVList(scb::Bytes const &buffer)
    : std::vector<TLV>(std::move(from_bytes(buffer)))
{}

TLVList::TLVList(scb::Bytes::const_iterator buffer_begin, scb::Bytes::const_iterator buffer_end) 
    : std::vector<TLV>(std::move(from_bytes_range(buffer_begin, buffer_end)))
{}

std::vector<TLV> rsc::TLVList::from_bytes(scb::Bytes const &buffer) {
    std::vector<TLV> tlvs;
    size_t i = 0;
    do {
        tlvs.emplace_back(&buffer[i]);
        i += tlvs.back().size();
    } while (i < buffer.size());
    if (i != buffer.size()) {
        throw std::runtime_error("TLVList was constucted from invalid buffer");
    }
    return tlvs;
}

std::vector<TLV> rsc::TLVList::from_bytes_range(scb::Bytes::const_iterator buffer_begin, std::vector<unsigned char>::const_iterator buffer_end) {
    std::vector<TLV> tlvs;
    auto i = buffer_begin;
    while (i < buffer_end) {
        tlvs.emplace_back(&*i);
        i += tlvs.back().size();
    }
    if (i != buffer_end) {
        throw std::runtime_error("TLVList was constucted from invalid buffer");
    }
    return tlvs;
}
