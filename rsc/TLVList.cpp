#include "TLVList.h"

using namespace rsc;

TLVList::TLVList(std::vector<unsigned char> const &buffer) {
    size_t i = 0;
    do {
        tlvs_.emplace_back(&buffer[i]);
        i += tlvs_.back().size();
    } while (i < buffer.size());
}

TLVList::TLVList(std::vector<unsigned char>::const_iterator buffer_begin, std::vector<unsigned char>::const_iterator buffer_end) {
    size_t i = 0;
    for (auto i = buffer_begin; i < buffer_end; ) {
        tlvs_.emplace_back(&*i);
        i += tlvs_.back().size();
    }
}
