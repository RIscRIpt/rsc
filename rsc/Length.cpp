#include "Length.h"

using namespace rsc;

Length::Length(unsigned char const *buffer) {
    if (buffer[0] & IS_NUMBER_OF_BYTES) {
        size_t nbOfBytes = buffer[0] & MASK_NUMBER_OF_BYTES;
        value_ = 0;
        bytes_.push_back(buffer[0]);
        for (size_t i = 1; i <= nbOfBytes; i++) {
            value_ <<= 8;
            value_ |= buffer[i];
            bytes_.push_back(buffer[i]);
        }
        bytes_.shrink_to_fit();
    } else {
        bytes_ = { buffer[0] };
        value_ = buffer[0];
    }
}
