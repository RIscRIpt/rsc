#include "TLVList.h"

using namespace rsc;

TLVList::TLVList(std::vector<unsigned char> const &buffer) {
    size_t i = 0;
    do {
        tlvs_.emplace_back(&buffer[i]);
        i += tlvs_.back().size();
    } while (i < buffer.size());
}
