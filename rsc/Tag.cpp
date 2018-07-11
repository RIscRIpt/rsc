#include "Tag.h"

using namespace rsc;

Tag::Tag(unsigned char const *buffer) {
    tag_.push_back(*buffer);
    if ((*buffer & MASK_TAG_NUMBER_0) == MULTI_BYTE_TAG) {
        do {
            buffer++;
            tag_.push_back(*buffer);
        } while (tag_.back() & MASK_TAG_NEXT_BYTE);
    }
    tag_.shrink_to_fit();
}

uintptr_t Tag::number() const noexcept {
    if ((tag_[0] & MASK_TAG_NUMBER_0) != MULTI_BYTE_TAG) {
        return tag_[0] & MASK_TAG_NUMBER_0;
    }
    // Multi byte tag
    uintptr_t number = tag_[1] & MASK_TAG_NUMBER_N;
    for (size_t i = 1; tag_[i] & MASK_TAG_NEXT_BYTE; ) {
        i++;
        number <<= NUMBER_BITS;
        number |= tag_[i] & MASK_TAG_NUMBER_N;
    }
    return number;
}

uintptr_t Tag::value() const noexcept {
    uintptr_t result = 0;
    for (auto b : tag_) {
        result <<= 8;
        result |= b;
    }
    return result;
}
