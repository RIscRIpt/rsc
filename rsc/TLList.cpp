#include "TLList.h"

using namespace rsc;

TLList::TLList(std::vector<unsigned char> const &buffer) {
    size_t i = 0;
    do {
        tls_.emplace_back(&buffer[i]);
        i += tls_.back().size();
    } while (i < buffer.size());
    if (i != buffer.size()) {
        throw std::runtime_error("TLList was constucted from invalid buffer");
    }
}

TLList::TLList(std::vector<unsigned char>::const_iterator buffer_begin, std::vector<unsigned char>::const_iterator buffer_end) {
    auto i = buffer_begin;
    while (i < buffer_end) {
        tls_.emplace_back(&*i);
        i += tls_.back().size();
    }
    if (i != buffer_end) {
        throw std::runtime_error("TLList was constucted from invalid buffer");
    }
}
