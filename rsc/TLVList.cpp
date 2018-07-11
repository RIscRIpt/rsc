#include "TLVList.h"

using namespace rsc;

TLVList::TLVList(std::vector<unsigned char> const &buffer) {
    size_t i = 0;
    do {
        tlvs_.emplace_back(&buffer[i]);
        i += tlvs_.back().size();
    } while (i < buffer.size());
    if (i != buffer.size()) {
        throw std::runtime_error("TLList was constucted from invalid buffer");
    }
}

TLVList::TLVList(std::vector<unsigned char>::const_iterator buffer_begin, std::vector<unsigned char>::const_iterator buffer_end) {
    auto i = buffer_begin;
    while (i < buffer_end) {
        tlvs_.emplace_back(&*i);
        i += tlvs_.back().size();
    }
    if (i != buffer_end) {
        throw std::runtime_error("TLList was constucted from invalid buffer");
    }
}
